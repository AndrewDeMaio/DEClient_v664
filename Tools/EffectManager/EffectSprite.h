#pragma once

#include <QImage>
#include <QString>
#include <QVector>
#include "PalettePack.h"

class EffectSpritePack
{
public:
    // Enum para identificar o formato do pacote
    enum class PackType {
        Unknown,
        ASPK, // Formato RLE original
        EffectScreenSPK,
        ISPK,      // Index pack (.ispk)
        SSPK,      // Shadow pack (.sspk)
        GenericSPK
    };

    EffectSpritePack();
    bool load(const QString& path);
    QImage loadSpriteAtIndex(int index, const Palette* palette) const;
    QByteArray getRawSpriteData(int index) const;
    int getSpriteCount() const { return m_totalFrames; }
    bool isValid() const { return m_isValid; }
    PackType getPackType() const { return m_packType; }

private:
    bool loadFromSingleFile(const QString& filePath);
    bool loadFromSplitDirectory(const QString& dirPath);

    bool m_isValid = false;
    bool m_isSplit = false;
	bool IndexArchiveLoaded = false;
    int m_totalFrames = 0;
    int m_framesPerFile = 0;
    QString m_basePath;
    QVector<quint32> m_spriteOffsets;
    PackType m_packType = PackType::Unknown; // <-- MEMBRO ADICIONADO
};