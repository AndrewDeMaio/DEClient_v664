#pragma once

#include <QObject> // Adicionado
#include <QTreeWidget>
#include <QProgressBar> // Adicionado

class EffectFramePack;
class EffectSpritePack;
class CCreatureFramePack; // ADICIONADO

class SpriteTreeBuilder : public QObject // Alterado para herdar de QObject
{
    Q_OBJECT // Adicionado

public:
    SpriteTreeBuilder(QTreeWidget* treeWidget, QProgressBar* progressBar, QObject* parent = nullptr);
    void populate(const EffectFramePack& framePack, const EffectSpritePack& spritePack);
    void populate(const CCreatureFramePack& creaturePack, const EffectSpritePack& spritePack); // SOBRECARGA ADICIONADA

private:
    void populateFromFramePack(const EffectFramePack& framePack);
    void populateFromSpritePack(const EffectSpritePack& spritePack);
    void populateFromCreaturePack(const CCreatureFramePack& creaturePack); // NOVO

    QTreeWidget* m_tree;
    QProgressBar* m_progressBar; // Adicionado
};