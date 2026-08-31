#include "EffectManager.h"
#include "PalettePack.h"
#include "SpriteTreeBuilder.h"
#include "EffectUtils.h"
#include "ScreenSpriteDecoder.h"
#include "CCreatureFramePack.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QSplitter>
#include <QMessageBox>
#include <QSettings>
#include <QColorDialog>
#include <QGroupBox>
#include <QSizePolicy>
#include <QResizeEvent>
#include <QCoreApplication>
#include <QProgressBar>
#include <QDebug>

EffectManager::EffectManager(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->setStyleSheet("QMenu::item:disabled { color: #808080; }");

    setWindowTitle("Effect Manager");
    resize(1024, 768);

    removeToolBar(ui.mainToolBar);
    setupMenuBar();

    m_mainSplitter = new QSplitter(Qt::Horizontal, this);

    m_fileTree = new QTreeWidget(m_mainSplitter);
    m_fileTree->setHeaderLabels({ "Effect Files" });

    m_spriteTree = new QTreeWidget(m_mainSplitter);
    m_spriteTree->setHeaderLabels({ "Effects, Directions & Frames" });

    QWidget* rightPanel = new QWidget(m_mainSplitter);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(0, 0, 0, 0);

    // --- Painel de Informações e Botão Play ---
    QGroupBox* infoGroup = new QGroupBox("Frame Info", rightPanel);
    infoGroup->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    QVBoxLayout* infoLayout = new QVBoxLayout(infoGroup);
    
    m_infoLabel = new QLabel("Select a frame to see its properties.", infoGroup);
    m_infoLabel->setWordWrap(true);
    
    m_playAnimationButton = new QPushButton("Play Animation", infoGroup);
    m_playAnimationButton->setVisible(false);

    infoLayout->addWidget(m_infoLabel);
    infoLayout->addWidget(m_playAnimationButton);
    infoGroup->setLayout(infoLayout);
    // --- Fim do Painel ---
    
    m_previewLabel = new QLabel("Select a frame to preview", rightPanel);
    m_previewLabel->setAlignment(Qt::AlignCenter);
    m_previewLabel->setMinimumSize(200, 200);
    m_previewBackgroundColor = QColor("#aaaa7f");
    updatePreviewBackground();

    rightLayout->addWidget(infoGroup);
    rightLayout->addWidget(m_previewLabel);
    rightPanel->setLayout(rightLayout);

    m_mainSplitter->addWidget(m_fileTree);
    m_mainSplitter->addWidget(m_spriteTree);
    m_mainSplitter->addWidget(rightPanel);

    m_mainSplitter->setSizes({ 250, 250, 524 });

    setCentralWidget(m_mainSplitter);

    // --- Configuração da Animação ---
    m_animationTimer = new QTimer(this);
    m_animationTimer->setInterval(50);
    // --- Fim da Configuração ---

    // --- Configuração da Barra de Progresso ---
    m_loadingOverlay = new QWidget(this);
    m_loadingOverlay->setStyleSheet("background-color: rgba(0, 0, 0, 150); border-radius: 10px;");
    
    QVBoxLayout* loadingLayout = new QVBoxLayout(m_loadingOverlay);
    m_loadingLabel = new QLabel("Loading...", m_loadingOverlay);
    m_loadingLabel->setAlignment(Qt::AlignCenter);
    m_loadingLabel->setStyleSheet("color: white; background-color: transparent;");

    m_progressBar = new QProgressBar(m_loadingOverlay);
    m_progressBar->setRange(0, 100);
    m_progressBar->setValue(0);
    m_progressBar->setTextVisible(true);
    m_progressBar->setAlignment(Qt::AlignCenter);

    loadingLayout->addStretch();
    loadingLayout->addWidget(m_loadingLabel);
    loadingLayout->addWidget(m_progressBar);
    loadingLayout->addStretch();
    
    m_loadingOverlay->hide();

    m_paletteControlDialog = new PaletteControlDialog(this);
    m_paletteControlDialog->hide(); 

    setupUiConnections();
}

EffectManager::~EffectManager() {}

void EffectManager::setupMenuBar()
{
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_openAction = new QAction(tr("&Open Directory..."), this);
    m_openAction->setShortcuts(QKeySequence::Open);
    m_fileMenu->addAction(m_openAction);

    m_savePaletteAction = new QAction(tr("&Save Palette"), this);
    m_savePaletteAction->setShortcuts(QKeySequence::Save);
    m_savePaletteAction->setEnabled(false);
    m_fileMenu->addAction(m_savePaletteAction);

    // Export action
    m_exportAction = new QAction(tr("E&xport Frame..."), this);
    m_exportAction->setEnabled(false);
    m_fileMenu->addAction(m_exportAction);

    m_fileMenu->addSeparator();
    m_exitAction = new QAction(tr("E&xit"), this);
    m_exitAction->setShortcuts(QKeySequence::Quit);
    m_fileMenu->addAction(m_exitAction);

    m_viewMenu = menuBar()->addMenu(tr("&View"));
    m_changeBgColorAction = new QAction(tr("Change Background Color..."), this);
    m_viewMenu->addAction(m_changeBgColorAction);

    m_adjustPaletteAction = new QAction(tr("Adjust Palette..."), this);
    m_adjustPaletteAction->setEnabled(false);
    m_viewMenu->addAction(m_adjustPaletteAction);

    m_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_aboutAction = new QAction(tr("&About"), this);
    m_helpMenu->addAction(m_aboutAction);
}

void EffectManager::setupUiConnections()
{
    connect(m_openAction, &QAction::triggered, this, &EffectManager::onSearchDirectory);
    connect(m_savePaletteAction, &QAction::triggered, this, &EffectManager::onSavePalette);
    connect(m_exportAction, &QAction::triggered, this, &EffectManager::onExportFrame); // ADICIONADO
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
    connect(m_aboutAction, &QAction::triggered, this, &EffectManager::onAbout);
    connect(m_changeBgColorAction, &QAction::triggered, this, &EffectManager::onChangeBackgroundColor);
    connect(m_adjustPaletteAction, &QAction::triggered, this, &EffectManager::onAdjustPalette); 
    connect(m_playAnimationButton, &QPushButton::clicked, this, &EffectManager::onPlayAnimation);
    connect(m_animationTimer, &QTimer::timeout, this, &EffectManager::onAnimationStep);
    connect(m_fileTree, &QTreeWidget::currentItemChanged, this, &EffectManager::onFileSelectionChanged);
    connect(m_spriteTree, &QTreeWidget::currentItemChanged, this, &EffectManager::onSpriteSelectionChanged);

    connect(m_paletteControlDialog, &PaletteControlDialog::paletteAdjusted, this, &EffectManager::onPaletteAdjusted);
    connect(m_paletteControlDialog, &PaletteControlDialog::paletteReset, this, &EffectManager::onPaletteReset);
}

void EffectManager::updatePreviewBackground()
{
    QPalette palette = m_previewLabel->palette();
    palette.setColor(QPalette::Window, m_previewBackgroundColor);
    m_previewLabel->setAutoFillBackground(true);
    m_previewLabel->setPalette(palette);
}

void EffectManager::onChangeBackgroundColor()
{
    const QColor newColor = QColorDialog::getColor(m_previewBackgroundColor, this, "Select Background Color");
    if (newColor.isValid()) {
        m_previewBackgroundColor = newColor;
        updatePreviewBackground();
    }
}

void EffectManager::onAbout()
{
    QMessageBox::about(this, tr("About Effect Manager"),
        tr("A sprite effect management tool.\n\n"
           "This application uses the Qt Toolkit version %1, "
           "under the LGPL license. For more information, visit https://www.qt.io/")
           .arg(QT_VERSION_STR));
}

void EffectManager::onFileSelectionChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    stopAnimation();

    m_progressBar->setValue(0);
    m_loadingLabel->setText("Loading...");
    m_loadingOverlay->show();
    m_loadingOverlay->raise();
    QCoreApplication::processEvents();

    // limpa estado
    m_spriteTree->clear();
    m_previewLabel->clear();
    m_infoLabel->setText("Select a frame to see its properties.");
    m_spriteTree->setHeaderLabels({ "Effects, Directions & Frames" });
    m_currentPack = EffectSpritePack();
    m_currentFramePack = EffectFramePack();
    m_currentCreaturePack = CCreatureFramePack();
    m_currentPalettePack = PalettePack();
    m_adjustPaletteAction->setEnabled(false);
    m_savePaletteAction->setEnabled(false);
    if (m_exportAction) m_exportAction->setEnabled(false); // ADICIONAR
    m_paletteControlDialog->hide();
    m_adjustedPalettes.clear();

    m_lastSelectedSpriteId = -1;
    m_lastSelectedEffectIndex = -1;
    m_lastSelectedDirectionIndex = -1;
    m_lastSelectedCreatureIndex = -1;
    m_lastSelectedActionIndex = -1;

    if (!current || !current->data(0, FilePathRole).isValid()) {
        m_loadingOverlay->hide();
        return;
    }

    QString path = current->data(0, FilePathRole).toString();
    if (!m_currentPack.load(path)) {
        m_previewLabel->setText("Failed to load sprite pack.");
        m_loadingOverlay->hide();
        return;
    }

    QFileInfo packInfo(path);
    QDir parentDir = packInfo.dir(); 
    QString baseName = packInfo.isDir() ? packInfo.fileName() : packInfo.completeBaseName();
    
    bool HaveEFPK = false;
    bool HavePPK = false;
    bool HaveCFPK = false;
    QString hAve = packInfo.fileName();

    if (hAve.endsWith(".aspk", Qt::CaseInsensitive)
        || hAve.endsWith(".sspk", Qt::CaseInsensitive)
        || hAve.contains("effectscreen.spk", Qt::CaseInsensitive)
        || hAve.contains("effect.spk", Qt::CaseInsensitive)
        || hAve.contains("effect.sspk", Qt::CaseInsensitive))
    {
        HaveEFPK = true;
    }

    if (hAve.endsWith(".aspk", Qt::CaseInsensitive)
        || hAve.contains("effectscreen.spk", Qt::CaseInsensitive))
    {
        HavePPK = true;
    }

    if (hAve.endsWith(".ispk", Qt::CaseInsensitive)
        || hAve.endsWith(".sspk", Qt::CaseInsensitive))
    {
        HaveCFPK = true;
    }

    if (baseName.endsWith(".aspk", Qt::CaseInsensitive)
     || baseName.endsWith(".sspk", Qt::CaseInsensitive)
     || baseName.endsWith(".ispk", Qt::CaseInsensitive))
    {
        baseName.chop(5);
    }
    else if (baseName.endsWith(".spk", Qt::CaseInsensitive)) {
        baseName.chop(4);
    }

    if (HaveEFPK == true) {
        if (hAve.contains("effect.spk", Qt::CaseInsensitive))
            baseName = "normaleffect";
        else if(hAve.contains("effect.sspk", Qt::CaseInsensitive))
            baseName = "shadoweffect";

        QString efpkPath = parentDir.filePath(baseName + ".efpk");
        if (QFile::exists(efpkPath)) {
            m_currentFramePack.load(efpkPath);
        }
    }
    if (HavePPK == true) {
        QString ppkPath = parentDir.filePath(baseName + ".ppk");
        if (QFile::exists(ppkPath) && m_currentPalettePack.load(ppkPath)) {
            m_adjustPaletteAction->setEnabled(true);
        }
    }

    if (HaveCFPK) {
        QString cfpkPath = parentDir.filePath(baseName + ".cfpk");
        if (QFile::exists(cfpkPath)) {
            QFile cfFile(cfpkPath);
            if (cfFile.open(QIODevice::ReadOnly)) {
                if (m_currentCreaturePack.loadFromDevice(&cfFile)) {
                    qDebug() << "Loaded CCreatureFramePack from" << cfpkPath;
                } else {
                    qWarning() << "Failed to load CCreatureFramePack from" << cfpkPath;
                }
                cfFile.close();
            }
        }
    }

    m_progressBar->setValue(5);
    QCoreApplication::processEvents();

    SpriteTreeBuilder builder(m_spriteTree, m_progressBar, this);
    if (m_currentFramePack.isValid()) {
        builder.populate(m_currentFramePack, m_currentPack);
    } else if (m_currentCreaturePack.creatureCount() > 0) {
        builder.populate(m_currentCreaturePack, m_currentPack);
    } else {
        builder.populate(m_currentFramePack, m_currentPack);
    }
    
    m_progressBar->setValue(100);
    m_loadingOverlay->hide();
}

void EffectManager::onSpriteSelectionChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    stopAnimation();
    m_playAnimationButton->setVisible(false);

    if (!current) {
        m_previewLabel->clear();
        m_infoLabel->setText("Select a frame to see its properties.");
        m_lastSelectedSpriteId = -1; 
        m_lastSelectedEffectIndex = -1;
        return;
    }

    QString infoText;
    int spriteIdToLoad = -1;
    int effectIndexForPalette = -1;
    const Palette* palette = nullptr;

    if (m_currentFramePack.isValid()) {
        const EffectFrame* frameInfo = nullptr;
        bool isDirectionNode = current->data(0, DirectionIndexRole).isValid() && !current->data(0, FrameIndexRole).isValid();
        bool isFrameNode = current->data(0, FrameIndexRole).isValid();

        if (isDirectionNode) {
            m_playAnimationButton->setVisible(true);
            int effectIndex = current->data(0, EffectIndexRole).toInt();
            int directionIndex = current->data(0, DirectionIndexRole).toInt();
            
            effectIndexForPalette = effectIndex;
            m_lastSelectedDirectionIndex = directionIndex;

            frameInfo = m_currentFramePack.getFrame(effectIndex, directionIndex, 0);
            if (frameInfo) {
                infoText = QString("Direction: %1\n%2\nFrames: %3")
                               .arg(directionIndex)
                               .arg(getDirectionName(directionIndex))
                               .arg(current->childCount());
            } else {
                infoText = "Direction has no frames.";
            }
        } else if (isFrameNode) {
            int effectIndex = current->data(0, EffectIndexRole).toInt();
            int directionIndex = current->data(0, DirectionIndexRole).toInt();
            int frameIndex = current->data(0, FrameIndexRole).toInt();
            
            effectIndexForPalette = effectIndex;
            frameInfo = m_currentFramePack.getFrame(effectIndex, directionIndex, frameIndex);

            if (frameInfo) {
                infoText = QString("Sprite ID: %1\nCoord: (X: %2, Y: %3)\nLight: %4\nIs Background: %5")
                               .arg(frameInfo->spriteId).arg(frameInfo->x).arg(frameInfo->y)
                               .arg(frameInfo->light).arg(frameInfo->isBackground ? "Yes" : "No");
            }
        } else if (!current->parent()) {
            int effectIndex = current->data(0, EffectIndexRole).toInt();
            effectIndexForPalette = effectIndex;
            frameInfo = m_currentFramePack.getFrame(effectIndex, 0, 0);
            if (frameInfo) {
                 infoText = QString("Effect: %1\nPreviewing Sprite ID: %2").arg(effectIndex).arg(frameInfo->spriteId);
            } else {
                infoText = QString("Effect %1 has no frames.").arg(effectIndex);
            }
        }

        if (frameInfo) {
            spriteIdToLoad = frameInfo->spriteId;
        }

    } else if (m_currentCreaturePack.creatureCount() > 0) {
        int creatureIndex = current->data(0, EffectIndexRole).isValid() ? current->data(0, EffectIndexRole).toInt() : -1;
        int actionIndex = current->data(0, ActionIndexRole).isValid() ? current->data(0, ActionIndexRole).toInt() : -1;
        int directionIndex = current->data(0, DirectionIndexRole).isValid() ? current->data(0, DirectionIndexRole).toInt() : -1;
        int frameIndex = current->data(0, FrameIndexRole).isValid() ? current->data(0, FrameIndexRole).toInt() : -1;

        bool isDirectionNode = (directionIndex != -1) && (frameIndex == -1);
        bool isFrameNode = (frameIndex != -1);

        if (isDirectionNode) {
            // habilita a reprodução para cfpk
            m_playAnimationButton->setVisible(true);

            effectIndexForPalette = creatureIndex;
            m_lastSelectedCreatureIndex = creatureIndex;
            m_lastSelectedActionIndex = actionIndex;
            m_lastSelectedDirectionIndex = directionIndex;

            const auto& creatures = m_currentCreaturePack.creatures();
            if (creatureIndex >= 0 && creatureIndex < creatures.size()
                && actionIndex >= 0 && actionIndex < creatures.at(creatureIndex).Actions.size()
                && directionIndex >= 0 && directionIndex < creatures.at(creatureIndex).Actions.at(actionIndex).Directions.size()) {

                const auto& frames = creatures.at(creatureIndex).Actions.at(actionIndex).Directions.at(directionIndex).Frames;
                if (!frames.isEmpty()) {
                    const auto& f0 = frames.at(0);
                    infoText = QString("Direction: %1\n%2\nFrames: %3")
                                   .arg(directionIndex)
                                   .arg(getDirectionName(directionIndex))
                                   .arg(current->childCount());
                    spriteIdToLoad = f0.SpriteID;
                } else {
                    infoText = "Direction has no frames.";
                }
            } else {
                infoText = "Invalid creature/direction selection.";
            }
        } else if (isFrameNode) {
            effectIndexForPalette = creatureIndex;
            m_lastSelectedCreatureIndex = creatureIndex;
            m_lastSelectedActionIndex = actionIndex;
            m_lastSelectedDirectionIndex = directionIndex;

            const auto& creatures = m_currentCreaturePack.creatures();
            if (creatureIndex >= 0 && creatureIndex < creatures.size()
                && actionIndex >= 0 && actionIndex < creatures.at(creatureIndex).Actions.size()
                && directionIndex >= 0 && directionIndex < creatures.at(creatureIndex).Actions.at(actionIndex).Directions.size()
                && frameIndex >= 0 && frameIndex < creatures.at(creatureIndex).Actions.at(actionIndex).Directions.at(directionIndex).Frames.size()) {

                const auto& frame = creatures.at(creatureIndex).Actions.at(actionIndex).Directions.at(directionIndex).Frames.at(frameIndex);
                infoText = QString("Sprite ID: %1\nCoord: (X: %2, Y: %3)")
                               .arg(frame.SpriteID).arg(frame.X).arg(frame.Y);
                spriteIdToLoad = frame.SpriteID;
            } else {
                infoText = "Invalid frame selection.";
            }
        } else if (!current->parent()) {
            effectIndexForPalette = creatureIndex;
            m_lastSelectedCreatureIndex = creatureIndex;
            const auto& creatures = m_currentCreaturePack.creatures();
            if (creatureIndex >= 0 && creatureIndex < creatures.size()) {
                bool found = false;
                const auto& actions = creatures.at(creatureIndex).Actions;
                for (int a = 0; a < actions.size() && !found; ++a) {
                    const auto& dirs = actions.at(a).Directions;
                    for (int d = 0; d < dirs.size() && !found; ++d) {
                        const auto& frames = dirs.at(d).Frames;
                        if (!frames.isEmpty()) {
                            spriteIdToLoad = frames.at(0).SpriteID;
                            infoText = QString("Creature: %1\nPreviewing Sprite ID: %2").arg(creatureIndex).arg(spriteIdToLoad);
                            found = true;
                        }
                    }
                }
                if (!found) infoText = QString("Creature %1 has no frames.").arg(creatureIndex);
            }
        }

    } else {
        if (current->data(0, FrameIndexRole).isValid()) {
            spriteIdToLoad = current->data(0, FrameIndexRole).toInt();
            infoText = QString("Sprite: %1\n.efpk/.cfpk data not available.").arg(spriteIdToLoad);
            if (m_currentPalettePack.isValid()) {
                effectIndexForPalette = 0;
            }
        }
    }

    if (spriteIdToLoad == -1) {
        m_previewLabel->setText("Invalid frame data.");
        return;
    }

    m_infoLabel->setText(infoText);
    m_lastSelectedSpriteId = spriteIdToLoad;
    m_lastSelectedEffectIndex = effectIndexForPalette;

    if (effectIndexForPalette != -1) {
        if (m_adjustedPalettes.contains(effectIndexForPalette)) {
            palette = &m_adjustedPalettes[effectIndexForPalette];
        } else if (m_currentPalettePack.isValid()) {
            palette = m_currentPalettePack.getPalette(effectIndexForPalette);
        }
    }

    updateFramePreview(spriteIdToLoad, palette);

    if (m_exportAction) m_exportAction->setEnabled(spriteIdToLoad != -1);
}

void EffectManager::onPlayAnimation()
{
    if (m_animationTimer->isActive()) {
        stopAnimation();
        return;
    }

    // Prioriza .efpk (existente)
    if (m_currentFramePack.isValid()) {
        if (m_lastSelectedEffectIndex == -1 || m_lastSelectedDirectionIndex == -1) return;

        const auto& effects = m_currentFramePack.getEffects();
        if (m_lastSelectedEffectIndex >= effects.size()) return;

        const auto& effect = effects.at(m_lastSelectedEffectIndex);
        if (m_lastSelectedDirectionIndex >= effect.directions.size()) return;

        const auto& direction = effect.directions.at(m_lastSelectedDirectionIndex);
        if (direction.frames.isEmpty()) return;

        m_animationFrames.clear();
        for (const auto& frame : direction.frames) {
            m_animationFrames.append(&frame);
        }

        m_animationCreatureFrames.clear();
        m_animationFrameIndex = 0;
        m_playAnimationButton->setText("Stop");
        m_spriteTree->setEnabled(false);
        m_animationTimer->start();
        onAnimationStep();
        return;
    }

    // Suporte para .cfpk
    if (m_currentCreaturePack.creatureCount() > 0) {
        if (m_lastSelectedCreatureIndex == -1 || m_lastSelectedActionIndex == -1 || m_lastSelectedDirectionIndex == -1) return;

        const auto& creatures = m_currentCreaturePack.creatures();
        if (m_lastSelectedCreatureIndex < 0 || m_lastSelectedCreatureIndex >= creatures.size()) return;
        const auto& creature = creatures.at(m_lastSelectedCreatureIndex);

        if (m_lastSelectedActionIndex < 0 || m_lastSelectedActionIndex >= creature.Actions.size()) return;
        const auto& action = creature.Actions.at(m_lastSelectedActionIndex);

        if (m_lastSelectedDirectionIndex < 0 || m_lastSelectedDirectionIndex >= action.Directions.size()) return;
        const auto& direction = action.Directions.at(m_lastSelectedDirectionIndex);

        if (direction.Frames.isEmpty()) return;

        m_animationCreatureFrames.clear();
        for (const auto& frame : direction.Frames) {
            m_animationCreatureFrames.append(&frame);
        }

        m_animationFrames.clear();
        m_animationFrameIndex = 0;
        m_playAnimationButton->setText("Stop");
        m_spriteTree->setEnabled(false);
        m_animationTimer->start();
        onAnimationStep();
        return;
    }
}

void EffectManager::onAnimationStep()
{
    // Se estiver tocando .efpk frames
    if (!m_animationFrames.isEmpty()) {
        if (m_animationFrameIndex >= m_animationFrames.size()) {
            stopAnimation();
            return;
        }

        const EffectFrame* frameInfo = m_animationFrames.at(m_animationFrameIndex);
        if (!frameInfo) {
            stopAnimation();
            return;
        }

        QString infoText = QString("Animating...\nFrame: %1 / %2\nSprite ID: %3")
                           .arg(m_animationFrameIndex + 1)
                           .arg(m_animationFrames.size())
                           .arg(frameInfo->spriteId, 5, 10, QChar('0'));
        m_infoLabel->setText(infoText);

        const Palette* palette = nullptr;
        if (m_adjustedPalettes.contains(m_lastSelectedEffectIndex)) {
            palette = &m_adjustedPalettes[m_lastSelectedEffectIndex];
        } else {
            palette = m_currentPalettePack.getPalette(m_lastSelectedEffectIndex);
        }

        updateFramePreview(frameInfo->spriteId, palette);
        ++m_animationFrameIndex;
        return;
    }

    // Se estiver tocando .cfpk frames
    if (!m_animationCreatureFrames.isEmpty()) {
        if (m_animationFrameIndex >= m_animationCreatureFrames.size()) {
            stopAnimation();
            return;
        }

        const CCreatureFrame* cframe = m_animationCreatureFrames.at(m_animationFrameIndex);
        if (!cframe) {
            stopAnimation();
            return;
        }

        QString infoText = QString("Animating...\nFrame: %1 / %2\nSprite ID: %3\nCoord: (X: %4, Y: %5)")
                           .arg(m_animationFrameIndex + 1)
                           .arg(m_animationCreatureFrames.size())
                           .arg(cframe->SpriteID, 5, 10, QChar('0'))
                           .arg(cframe->X)
                           .arg(cframe->Y);
        m_infoLabel->setText(infoText);

        const Palette* palette = nullptr;
        if (m_adjustedPalettes.contains(m_lastSelectedEffectIndex)) {
            palette = &m_adjustedPalettes[m_lastSelectedEffectIndex];
        } else {
            palette = m_currentPalettePack.getPalette(m_lastSelectedEffectIndex);
        }

        updateFramePreview(cframe->SpriteID, palette);
        ++m_animationFrameIndex;
        return;
    }
}

void EffectManager::stopAnimation()
{
    m_animationTimer->stop();
    m_playAnimationButton->setText("Play Animation");
    m_spriteTree->setEnabled(true);
    m_animationFrames.clear();
    m_animationCreatureFrames.clear();
    m_animationFrameIndex = 0;
}

void EffectManager::onSavePalette()
{
    if (m_adjustedPalettes.isEmpty()) {
        QMessageBox::warning(this, "Save Palette", "No changes to save.");
        return;
    }

    QTreeWidgetItem* currentFileItem = m_fileTree->currentItem();
    if (!currentFileItem) return;

    QFileInfo packInfo(currentFileItem->data(0, FilePathRole).toString());
    QDir parentDir = packInfo.dir();
    QString baseName = packInfo.isDir() ? packInfo.fileName() : packInfo.completeBaseName();

    // Se veio de .aspk, remove extensão
    if (baseName.endsWith(".aspk", Qt::CaseInsensitive)) {
        baseName.chop(5);
    }

    QString originalPpkPath = parentDir.filePath(baseName + ".ppk");

    if (!QFile::exists(originalPpkPath)) {
        QMessageBox::warning(this, "Error", "Original .ppk file not found. Cannot save.");
        return;
    }

    PalettePack packToSave;
    if (!packToSave.load(originalPpkPath)) {
        QMessageBox::warning(this, "Error", "Could not load original .ppk data. Aborting save.");
        return;
    }

    for (auto it = m_adjustedPalettes.constBegin(); it != m_adjustedPalettes.constEnd(); ++it) {
        packToSave.setPalette(it.key(), it.value());
    }

    QString savePath = QFileDialog::getSaveFileName(this, "Save Palette Pack", originalPpkPath, "Palette Pack Files (*.ppk)");

    if (savePath.isEmpty()) {
        return;
    }

    if (packToSave.save(savePath)) {
        QMessageBox::information(this, "Success", "Palette saved successfully.");
        
        if (QFileInfo(savePath).absoluteFilePath() == QFileInfo(originalPpkPath).absoluteFilePath()) {
            m_currentPalettePack = packToSave;
            m_adjustedPalettes.clear();
            m_savePaletteAction->setEnabled(false);
            onSpriteSelectionChanged(m_spriteTree->currentItem(), nullptr);
        }
    } else {
        QMessageBox::warning(this, "Error", "Could not save the palette file.");
    }
}

void EffectManager::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    if (m_loadingOverlay) {
        m_loadingOverlay->setGeometry(
            this->width() / 2 - 150,
            this->height() / 2 - 50,
            300,
            100
        );
    }
}

void EffectManager::updateFramePreview(int spriteId, const Palette* palette)
{
    if (spriteId == -1) {
        m_previewLabel->setText("Invalid frame data.");
        return;
    }

    QImage image = m_currentPack.loadSpriteAtIndex(spriteId, palette);

    if (!image.isNull()) {
        m_previewLabel->setPixmap(QPixmap::fromImage(image));
    } else {
        m_previewLabel->setText(QString("Empty or invalid sprite (ID: %1)").arg(spriteId, 5, 10, QChar('0')));
    }
}

void EffectManager::onPaletteAdjusted(const Palette& newPalette)
{
    if (m_lastSelectedSpriteId == -1 || m_lastSelectedEffectIndex == -1) return;

    m_adjustedPalettes[m_lastSelectedEffectIndex] = newPalette;
    m_savePaletteAction->setEnabled(true);

    updateFramePreview(m_lastSelectedSpriteId, &m_adjustedPalettes[m_lastSelectedEffectIndex]);
}

void EffectManager::onPaletteReset()
{
    if (m_lastSelectedEffectIndex == -1) return;

    m_adjustedPalettes.remove(m_lastSelectedEffectIndex);

    if (m_adjustedPalettes.isEmpty()) {
        m_savePaletteAction->setEnabled(false);
    }

    const Palette* originalPalette = nullptr;
    if (m_currentPalettePack.isValid()) {
        originalPalette = m_currentPalettePack.getPalette(m_lastSelectedEffectIndex);
    }

    updateFramePreview(m_lastSelectedSpriteId, originalPalette);
}
void EffectManager::onAdjustPalette()
{
    if (!m_currentPalettePack.isValid() || m_lastSelectedEffectIndex == -1) {
        QMessageBox::warning(this, "Warning", "No valid palette selected for adjustment.");
        return;
    }

    const Palette* originalPalette = m_currentPalettePack.getPalette(m_lastSelectedEffectIndex);
    // Se não existia ajuste prévio, cria um entry vazio para editar
    if (!m_adjustedPalettes.contains(m_lastSelectedEffectIndex)) {
        if (originalPalette) m_adjustedPalettes[m_lastSelectedEffectIndex] = *originalPalette;
        else m_adjustedPalettes[m_lastSelectedEffectIndex] = Palette();
    }

    Palette& adjustedPalette = m_adjustedPalettes[m_lastSelectedEffectIndex];

    m_paletteControlDialog->reconfigure(*originalPalette, adjustedPalette);
    m_paletteControlDialog->show();
    m_paletteControlDialog->raise();
    m_paletteControlDialog->activateWindow();
}

void EffectManager::onSearchDirectory()
{
    QSettings settings("MyCompany", "EffectManager");
    QString lastDir = settings.value("lastDir", QDir::homePath()).toString();

    QString dirPath = QFileDialog::getExistingDirectory(this, "Select Effect Directory", lastDir, QFileDialog::ShowDirsOnly);

    if (!dirPath.isEmpty())
    {
        settings.setValue("lastDir", dirPath);

        m_fileTree->clear();
        m_spriteTree->clear();
        m_previewLabel->clear();
        processDirectory(dirPath);
    }
}
void EffectManager::processDirectory(const QString& path)
{
    m_fileTree->clear();

    QDir rootDir(path);
    if (!rootDir.exists()) {
        new QTreeWidgetItem(m_fileTree, { "Directory not found." });
        return;
    }

    QFileInfoList entries = rootDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
    bool foundPacks = false;

    for (const QFileInfo& entryInfo : entries)
    {
        QString lowerCaseFileName = entryInfo.fileName().toLower();

        // Diretório que pode ser um "split pack" (contém header.inf)
        if (entryInfo.isDir()) {
            QDir subDir(entryInfo.absoluteFilePath());
            if (subDir.exists("header.inf")) {
                QTreeWidgetItem* dirItem = new QTreeWidgetItem(m_fileTree);
                dirItem->setText(0, entryInfo.fileName() + " (Split Pack)");
                dirItem->setData(0, FilePathRole, entryInfo.absoluteFilePath());
                foundPacks = true;
                continue;
            }

            // também procura por arquivos de pack dentro do subdiretório (caso comum em estruturas aninhadas)
            QFileInfoList subFiles = subDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
            for (const QFileInfo& sf : subFiles) {
                QString sfn = sf.fileName().toLower();
                if (sfn.endsWith(".aspk") || sfn.endsWith(".spk") || sfn.endsWith(".sspk") || sfn.endsWith(".ispk")) {
                    QTreeWidgetItem* nestedItem = new QTreeWidgetItem(m_fileTree);
                    nestedItem->setText(0, entryInfo.fileName() + "/" + sf.fileName());
                    nestedItem->setData(0, FilePathRole, sf.absoluteFilePath());
                    foundPacks = true;
                }
            }
        }
        else if (entryInfo.isFile()) {
            // Arquivos de pack conhecidos
            if (lowerCaseFileName.endsWith(".aspk")
                || lowerCaseFileName.endsWith(".spk")
                || lowerCaseFileName.endsWith(".sspk")
                || lowerCaseFileName.endsWith(".ispk"))
            {
                QTreeWidgetItem* fileItem = new QTreeWidgetItem(m_fileTree);
                fileItem->setText(0, entryInfo.fileName());
                fileItem->setData(0, FilePathRole, entryInfo.absoluteFilePath());
                foundPacks = true;
            }
        }
    }

    if (!foundPacks) {
        new QTreeWidgetItem(m_fileTree, { "No packs found." });
    }
}
// Novo slot: onExportFrame implementation
void EffectManager::onExportFrame()
{
    if (m_lastSelectedSpriteId == -1) {
        QMessageBox::warning(this, "Export", "No frame selected to export.");
        return;
    }

    // escolhe paleta atual (mesma lógica de preview)
    const Palette* palette = nullptr;
    if (m_lastSelectedEffectIndex != -1) {
        if (m_adjustedPalettes.contains(m_lastSelectedEffectIndex)) {
            palette = &m_adjustedPalettes[m_lastSelectedEffectIndex];
        } else if (m_currentPalettePack.isValid()) {
            palette = m_currentPalettePack.getPalette(m_lastSelectedEffectIndex);
        }
    }

    QString defaultName = QString("%1.png").arg(m_lastSelectedSpriteId, 5, 10, QChar('0'));
    QString savePath = QFileDialog::getSaveFileName(this, "Export Frame as PNG", defaultName, "PNG Image (*.png)");
    if (savePath.isEmpty()) return;

    QImage image = m_currentPack.loadSpriteAtIndex(m_lastSelectedSpriteId, palette);
    if (image.isNull()) {
        QMessageBox::warning(this, "Export", "Failed to render sprite for export.");
        return;
    }

    if (!image.save(savePath, "PNG")) {
        QMessageBox::warning(this, "Export", "Failed to save PNG file.");
        return;
    }

    QMessageBox::information(this, "Export", QString("Frame exported to %1").arg(savePath));
}