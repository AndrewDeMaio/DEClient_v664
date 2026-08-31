#pragma once

#include <QVector>
#include <QString>

// Forward declaration para evitar dependência circular
class QDataStream;

// Estrutura final que espelha CEffectFrame do C#
struct EffectFrame
{
    // Construtor que lê os dados de um stream.
    EffectFrame(QDataStream& stream);
    EffectFrame() = default; // Construtor padrão

    quint16 spriteId = 0;
    qint16  x = 0;
    qint16  y = 0;
    quint8  light = 0;
    bool    isBackground = false;
};

// Estrutura para uma direção de animação
struct EffectDirection
{
    QVector<EffectFrame> frames;
};

// Estrutura para um efeito completo
struct Effect
{
    QVector<EffectDirection> directions;
};

// Classe principal para carregar e conter os dados de um arquivo .efpk
class EffectFramePack
{
public:
    EffectFramePack();

    bool load(const QString& filePath);
    const QVector<Effect>& getEffects() const { return m_effects; }
    bool isValid() const { return !m_effects.isEmpty(); }

    // Função auxiliar para obter um frame específico (exemplo de uso)
    const EffectFrame* getFrame(int effectIndex, int directionIndex, int frameIndex) const;

private:
    QVector<Effect> m_effects;
};