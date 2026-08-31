#include "FrameInfo.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

// --- Implementação de EffectFrame ---
// Esta parte está correta e não precisa de alterações.
EffectFrame::EffectFrame(QDataStream& stream)
{
    stream >> spriteId;
    stream >> x;
    stream >> y;

    quint8 lightAndBg;
    stream >> lightAndBg;

    if ((lightAndBg & 0x80) != 0) {
        isBackground = true;
        light = lightAndBg & 0x7F;
    } else {
        isBackground = false;
        light = lightAndBg;
    }
}

// --- Implementação de EffectFramePack ---
EffectFramePack::EffectFramePack() {}

// CORREÇÃO: Lógica de leitura ajustada para ler o frameCount por direção.
bool EffectFramePack::load(const QString& filePath)
{
    m_effects.clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open .efpk file:" << filePath;
        return false;
    }

    QDataStream in(&file);
    in.setByteOrder(QDataStream::LittleEndian);

    quint16 effectCount;
    in >> effectCount;

    if (in.status() != QDataStream::Ok) return false;

    m_effects.reserve(effectCount);
    for (int i = 0; i < effectCount; ++i)
    {
        Effect effect;
        quint8 directionCount;
        in >> directionCount;

        if (in.status() != QDataStream::Ok) {
            qWarning() << "Failed to read directionCount for effect" << i;
            return false;
        }

        effect.directions.reserve(directionCount);
        for (int d = 0; d < directionCount; ++d)
        {
            // A estrutura correta, baseada no segundo construtor C#,
            // é ler o frameCount para CADA direção.
            quint16 frameCount;
            in >> frameCount;

            if (in.status() != QDataStream::Ok) {
                qWarning() << "Failed to read frameCount for direction" << d;
                return false;
            }

            EffectDirection direction;
            direction.frames.reserve(frameCount);
            for (int f = 0; f < frameCount; ++f)
            {
                if (in.atEnd()) {
                    qWarning() << "File ended prematurely while reading frames.";
                    return false;
                }
                direction.frames.append(EffectFrame(in));
            }
            effect.directions.append(direction);
        }
        m_effects.append(effect);
    }

    return !m_effects.isEmpty();
}

// Função auxiliar para acessar um frame de forma segura
const EffectFrame* EffectFramePack::getFrame(int effectIndex, int directionIndex, int frameIndex) const
{
    if (effectIndex < 0 || effectIndex >= m_effects.size()) return nullptr;
    const Effect& effect = m_effects.at(effectIndex);

    if (directionIndex < 0 || directionIndex >= effect.directions.size()) return nullptr;
    const EffectDirection& direction = effect.directions.at(directionIndex);

    if (frameIndex < 0 || frameIndex >= direction.frames.size()) return nullptr;
    
    return &direction.frames.at(frameIndex);
}