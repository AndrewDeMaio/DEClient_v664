#pragma once

#include <QtWidgets/QMainWindow>
#include <QTreeWidget>
#include <QLabel>
#include <QSplitter>
#include <QColor>
#include <QMap>
#include <QVector>
#include <QPushButton>
#include <QTimer>
#include <QWidget>
#include <QProgressBar>
#include "ui_EffectManager.h"
#include "EffectSprite.h"
#include "FrameInfo.h"
#include "PalettePack.h"
#include "PaletteControlDialog.h"
#include "CCreatureFramePack.h"

class EffectManager : public QMainWindow
{
    Q_OBJECT

public:
    EffectManager(QWidget* parent = nullptr);
    ~EffectManager();

private slots:
    void onSearchDirectory();
    void onFileSelectionChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void onSpriteSelectionChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void onAbout();
    void onChangeBackgroundColor();
    void onAdjustPalette();
    void onPaletteAdjusted(const Palette& newPalette);
    void onPaletteReset();
    void onSavePalette();
    void onPlayAnimation();
    void onAnimationStep();
    void onExportFrame(); // ADICIONADO

private:
    void setupMenuBar();
    void setupUiConnections();
    void processDirectory(const QString& path);
    void updatePreviewBackground();
    void updateFramePreview(int spriteId, const Palette* palette);
    void stopAnimation();
    void resizeEvent(QResizeEvent* event) override;

    Ui::EffectManagerClass ui;

    // Menus e Ações
    QMenu* m_fileMenu;
    QMenu* m_viewMenu;
    QMenu* m_helpMenu;
    QAction* m_openAction;
    QAction* m_exitAction;
    QAction* m_aboutAction;
    QAction* m_changeBgColorAction;
    QAction* m_adjustPaletteAction;
    QAction* m_savePaletteAction;
    QAction* m_exportAction; // ADICIONADO

    // Widgets da UI
    QSplitter* m_mainSplitter;
    QTreeWidget* m_fileTree;
    QTreeWidget* m_spriteTree;
    QLabel* m_previewLabel;
    QLabel* m_infoLabel;
    QColor m_previewBackgroundColor;
    QPushButton* m_playAnimationButton;

    // Widgets de Loading
    QWidget* m_loadingOverlay;
    QLabel* m_loadingLabel;
    QProgressBar* m_progressBar;

    // Dados Atuais
    EffectSpritePack m_currentPack;
    EffectFramePack m_currentFramePack;
    CCreatureFramePack m_currentCreaturePack;
    PalettePack m_currentPalettePack;
    
    QMap<int, Palette> m_adjustedPalettes;

    // Estado da seleção atual
    int m_lastSelectedSpriteId = -1;
    int m_lastSelectedEffectIndex = -1;
    int m_lastSelectedDirectionIndex = -1;

    // Para .cfpk: guarda índices de creature/action
    int m_lastSelectedCreatureIndex = -1;
    int m_lastSelectedActionIndex = -1;

    // Estado da Animação
    QTimer* m_animationTimer;
    QVector<const EffectFrame*> m_animationFrames;               // para .efpk
    QVector<const CCreatureFrame*> m_animationCreatureFrames;    // para .cfpk
    int m_animationFrameIndex = 0;

    // Diálogo de Controle
    PaletteControlDialog* m_paletteControlDialog;
};