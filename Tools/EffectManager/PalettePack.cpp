#include "PalettePack.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

PalettePack::PalettePack() : m_isValid(false) {}

bool PalettePack::load(const QString& filePath)
{
    m_palettes.clear();
    m_isValid = false;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open .ppk file:" << filePath;
        return false;
    }

    QDataStream in(&file);
    in.setByteOrder(QDataStream::LittleEndian);

    // ESTRUTURA CORRETA E FINAL: Baseado no código CTypePack2 e MPalette.
    // 1. Lê o número total de paletas (2 bytes).
    quint16 paletteCount;
    in >> paletteCount;

    if (in.status() != QDataStream::Ok || paletteCount == 0) {
        qWarning() << "Could not read a valid palette count from" << filePath;
        return false;
    }

    m_palettes.reserve(paletteCount);

    // 2. Lê cada paleta em sequência.
    for (quint16 i = 0; i < paletteCount; ++i)
    {
        if (in.atEnd()) {
            qWarning() << "Unexpected end of file. Expected" << paletteCount << "palettes, but found" << i;
            return false;
        }

        // 3. Cada paleta começa com seu contador de cores de 1 byte (quint8).
        quint8 colorCount;
        in >> colorCount;

        if (in.status() != QDataStream::Ok) {
             qWarning() << "Failed to read color count for palette" << i;
            return false;
        }

        Palette currentPalette;
        if (colorCount > 0) {
            currentPalette.reserve(colorCount);
            // 4. Lê os dados de cor (quint16) para a paleta atual.
            for (int j = 0; j < colorCount; ++j) {
                if (in.atEnd()) {
                    qWarning() << "Unexpected end of file while reading colors for palette" << i;
                    return false;
                }
                quint16 color555;
                in >> color555;

                // CORREÇÃO: Usa a máscara de bits exata do código original para a conversão.
               // quint16 color565 = ((color555 & 0x7C00) << 1) | (color555 & 0x03FF);

                currentPalette.append(color555);// color565);
            }
        }
        m_palettes.append(currentPalette);
    }

    m_isValid = true;
    return !m_palettes.isEmpty();
}

bool PalettePack::save(const QString& path) const
{
    if (!m_isValid) return false;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);

    // Escreve o número total de paletas (quint16 - 2 bytes)
    out << (quint16)m_palettes.size();

    // Itera sobre cada paleta e a escreve no arquivo
    for (const Palette& palette : m_palettes)
    {
        // CORREÇÃO: Escreve o número de cores como quint8 (1 byte)
        out << (quint8)palette.size();
        
        // Escreve cada valor de cor (quint16 - 2 bytes)
        for (quint16 colorValue : palette) {
            out << colorValue;
        }
    }

    return true;
}

const Palette* PalettePack::getPalette(int effectIndex) const
{
    if (m_isValid && effectIndex >= 0 && effectIndex < m_palettes.size()) {
        return &m_palettes.at(effectIndex);
    }
    return nullptr;
}

void PalettePack::setPalette(int effectIndex, const Palette& palette)
{
    if (m_isValid && effectIndex >= 0 && effectIndex < m_palettes.size()) {
        m_palettes[effectIndex] = palette;
    }
}