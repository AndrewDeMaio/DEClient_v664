#pragma once

#include <QString>
#include <QVector>

// Constantes para armazenar dados nos itens da árvore
// Movidas de EffectManager.cpp para serem compartilhadas
const int FilePathRole = Qt::UserRole + 1;
const int FrameIndexRole = Qt::UserRole + 2;
const int DirectionIndexRole = Qt::UserRole + 3;
const int EffectIndexRole = Qt::UserRole + 4;
const int ActionIndexRole = Qt::UserRole + 5; // ADICIONADO

// Mapeamento de Nomes de Direção
const QVector<QString> g_directionNames = {
    "Left", "Left Down", "Down", "Right Down",
    "Right", "Right Up", "Up", "Left Up"
};

// Declaração da função auxiliar
inline QString getDirectionName(int index) {
    if (index >= 0 && index < g_directionNames.size()) {
        return g_directionNames.at(index);
    }
    return "Unknown";
}