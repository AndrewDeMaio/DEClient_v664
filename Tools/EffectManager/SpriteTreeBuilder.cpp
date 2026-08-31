#include "SpriteTreeBuilder.h"
#include "FrameInfo.h"
#include "EffectSprite.h"
#include "EffectUtils.h"
#include "CCreatureFramePack.h" // ADICIONADO
#include <QCoreApplication> // Adicionado

SpriteTreeBuilder::SpriteTreeBuilder(QTreeWidget* treeWidget, QProgressBar* progressBar, QObject* parent)
    : QObject(parent), m_tree(treeWidget), m_progressBar(progressBar)
{
}

void SpriteTreeBuilder::populate(const EffectFramePack& framePack, const EffectSpritePack& spritePack)
{
    if (!m_tree || !m_progressBar) return;

    m_tree->clear();

    if (framePack.isValid()) {
        populateFromFramePack(framePack);
    } else if (spritePack.isValid()) {
        populateFromSpritePack(spritePack);
    } else {
        m_tree->setHeaderLabels({ "Effects, Directions & Frames" });
    }
}

void SpriteTreeBuilder::populate(const CCreatureFramePack& creaturePack, const EffectSpritePack& spritePack)
{
    if (!m_tree || !m_progressBar) return;

    m_tree->clear();

    if (creaturePack.creatureCount() > 0) {
        populateFromCreaturePack(creaturePack);
    } else if (spritePack.isValid()) {
        populateFromSpritePack(spritePack);
    } else {
        m_tree->setHeaderLabels({ "Creatures / Sprites" });
    }
}

void SpriteTreeBuilder::populateFromFramePack(const EffectFramePack& framePack)
{
    const auto& effects = framePack.getEffects();
    int totalEffects = effects.size();
    m_tree->setHeaderLabels({ QString("Effects (%1)").arg(totalEffects) });

    for (int e = 0; e < totalEffects; ++e) {
        QTreeWidgetItem* effectItem = new QTreeWidgetItem(m_tree);
        effectItem->setText(0, QString("%1").arg(e, 5, 10, QChar('0')));
        effectItem->setData(0, EffectIndexRole, e);

        const auto& directions = effects.at(e).directions;
        for (int d = 0; d < directions.size(); ++d) {
            QTreeWidgetItem* dirItem = new QTreeWidgetItem(effectItem);
            const auto& frames = directions.at(d).frames;
            dirItem->setText(0, QString("Direction %1 - %2").arg(d).arg(getDirectionName(d)));
            
            dirItem->setData(0, EffectIndexRole, e);
            dirItem->setData(0, DirectionIndexRole, d);

            for (int f = 0; f < frames.size(); ++f) {
                QTreeWidgetItem* frameItem = new QTreeWidgetItem(dirItem);
                const auto& frameInfo = frames.at(f);
                frameItem->setText(0, QString("%1 - %2")
                                        .arg(f, 3, 10, QChar('0'))
                                        .arg(frameInfo.spriteId, 5, 10, QChar('0')));
                frameItem->setData(0, EffectIndexRole, e);
                frameItem->setData(0, DirectionIndexRole, d);
                frameItem->setData(0, FrameIndexRole, f);
            }
        }

        // Atualiza a barra de progresso diretamente
        if (totalEffects > 0) {
            int progress = 5 + (int)((double)(e + 1) / totalEffects * 90);
            m_progressBar->setValue(progress);
            QCoreApplication::processEvents(); // Força a atualização da UI
        }
    }
}

void SpriteTreeBuilder::populateFromSpritePack(const EffectSpritePack& spritePack)
{
    int totalSprites = spritePack.getSpriteCount();
    m_tree->setHeaderLabels({ QString("Sprites (%1)").arg(totalSprites) });
    for (int i = 0; i < totalSprites; ++i) {
        QTreeWidgetItem* spriteItem = new QTreeWidgetItem(m_tree);
        spriteItem->setText(0, QString("%1").arg(i, 5, 10, QChar('0')));
        spriteItem->setData(0, FrameIndexRole, i);

        if (totalSprites > 0) {
            int progress = 5 + (int)((double)(i + 1) / totalSprites * 90);
            m_progressBar->setValue(progress);
            if (i % 20 == 0) { // Atualiza a UI a cada 20 sprites para não sobrecarregar
                QCoreApplication::processEvents();
            }
        }
    }
}

void SpriteTreeBuilder::populateFromCreaturePack(const CCreatureFramePack& creaturePack)
{
    const auto& creatures = creaturePack.creatures();
    int totalCreatures = creatures.size();
    m_tree->setHeaderLabels({ QString("Creatures (%1)").arg(totalCreatures) });

    for (int c = 0; c < totalCreatures; ++c) {
        QTreeWidgetItem* creatureItem = new QTreeWidgetItem(m_tree);
        creatureItem->setText(0, QString("Creature %1").arg(c, 3, 10, QChar('0')));
        creatureItem->setData(0, EffectIndexRole, c);

        const auto& actions = creatures.at(c).Actions;
        for (int a = 0; a < actions.size(); ++a) {
            QTreeWidgetItem* actionItem = new QTreeWidgetItem(creatureItem);
            actionItem->setText(0, QString("Action %1").arg(a));
            actionItem->setData(0, EffectIndexRole, c);
            actionItem->setData(0, ActionIndexRole, a);

            const auto& directions = actions.at(a).Directions;
            for (int d = 0; d < directions.size(); ++d) {
                QTreeWidgetItem* dirItem = new QTreeWidgetItem(actionItem);
                dirItem->setText(0, QString("Direction %1 - %2").arg(d).arg(getDirectionName(d)));
                dirItem->setData(0, EffectIndexRole, c);
                dirItem->setData(0, ActionIndexRole, a);
                dirItem->setData(0, DirectionIndexRole, d);

                const auto& frames = directions.at(d).Frames;
                for (int f = 0; f < frames.size(); ++f) {
                    QTreeWidgetItem* frameItem = new QTreeWidgetItem(dirItem);
                    const auto& frameInfo = frames.at(f);
                    frameItem->setText(0, QString("%1 - %2")
                                            .arg(f, 3, 10, QChar('0'))
                                            .arg(frameInfo.SpriteID, 5, 10, QChar('0')));
                    frameItem->setData(0, EffectIndexRole, c);
                    frameItem->setData(0, ActionIndexRole, a);
                    frameItem->setData(0, DirectionIndexRole, d);
                    frameItem->setData(0, FrameIndexRole, f);
                }
            }
        }

        // Atualiza progresso
        if (totalCreatures > 0) {
            int progress = 5 + (int)((double)(c + 1) / totalCreatures * 90);
            m_progressBar->setValue(progress);
            QCoreApplication::processEvents();
        }
    }
}