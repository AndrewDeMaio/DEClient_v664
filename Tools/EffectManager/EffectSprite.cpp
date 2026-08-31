#include "EffectSprite.h"
#include "PalettePack.h"
#include "GenericSpriteDecoder.h"
#include "ScreenSpriteDecoder.h"
#include "ShadowSpriteDecoder.h"
#include "IndexSpriteDecoder.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>

EffectSpritePack::EffectSpritePack() {}

// Sua função de conversão original. Não será mais chamada diretamente,
// mas sua lógica de alfa será usada.
QRgb convertSpriteColor(quint16 colorData)
{
    int red = (colorData & 0xF800) >> 11;
    int blue = (colorData & 0x07E0) >> 5;
    int alpha = (colorData & 0x001F);
    int green = 0;

    red   = (red * 255) / 31;
    blue  = (blue * 255) / 63;
    alpha = (alpha * 255) / 31;

    return qRgba(red, green, blue, alpha);
}

bool EffectSpritePack::load(const QString& path)
{
    QFileInfo fileInfo(path);
    QString lowerFileName = fileInfo.fileName().toLower();

    // Lógica de detecção de tipo
    if (fileInfo.isDir()) {
        if (lowerFileName.endsWith(".aspk")) m_packType = PackType::ASPK;
        else if (lowerFileName == "effectscreen.spk") m_packType = PackType::EffectScreenSPK;
        else if (lowerFileName.endsWith(".ispk")) m_packType = PackType::ISPK;
        else if (lowerFileName.endsWith(".sspk")) m_packType = PackType::SSPK;
        else if (lowerFileName.endsWith(".spk")) m_packType = PackType::GenericSPK;
        else m_packType = PackType::Unknown;
    }
    else { // É um arquivo
        if (lowerFileName == "effectscreen.spk") m_packType = PackType::EffectScreenSPK;
        else if (lowerFileName.endsWith(".ispk")) m_packType = PackType::ISPK;
        else if (lowerFileName.endsWith(".sspk")) m_packType = PackType::SSPK;
        else if (lowerFileName.endsWith(".spk")) m_packType = PackType::GenericSPK;
        else if (lowerFileName.endsWith(".aspk")) m_packType = PackType::ASPK;
        else m_packType = PackType::Unknown;
    }

    if (m_packType == PackType::Unknown) {
        m_isValid = false;
        return m_isValid;
    }

    if (fileInfo.isDir()) {
        m_isValid = loadFromSplitDirectory(path);
    }
    else if (fileInfo.isFile()) {
        m_isValid = loadFromSingleFile(path);
    }
    else {
        m_isValid = false;
    }
    return m_isValid;
}

bool EffectSpritePack::loadFromSplitDirectory(const QString& dirPath)
{
    QFile headerFile(QDir(dirPath).filePath("header.inf"));
    if (!headerFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&headerFile);
    m_totalFrames = in.readLine().toInt();
    m_framesPerFile = in.readLine().toInt();

    if (m_totalFrames <= 0 || m_framesPerFile <= 0) {
        return false;
    }

    m_isSplit = true;
    m_basePath = dirPath;
    return true;
}

bool EffectSpritePack::loadFromSingleFile(const QString& filePath)
{
    m_basePath = filePath;
    m_isSplit = false;
    m_spriteOffsets.clear();
	//bool IndexArchiveLoaded = false;
    // ASPK pode ter um arquivo de índice.
    //if (m_packType == PackType::ASPK) {
        QString indexFilePath = filePath + "i";
        QFile indexFile(indexFilePath);
        if (indexFile.open(QIODevice::ReadOnly)) {
            QDataStream in(&indexFile);
            in.setByteOrder(QDataStream::LittleEndian);
            quint16 spriteCount;
            in >> spriteCount;
            m_totalFrames = spriteCount;
            m_spriteOffsets.reserve(spriteCount);
            for (int i = 0; i < spriteCount; ++i) {
                quint32 offset;
                in >> offset;
                m_spriteOffsets.append(offset);
            }
            qDebug() << "Loaded" << m_totalFrames << "ASPK offsets from index file" << indexFilePath;
            return true;
        }
    //}

    // ISPK: header uint32 count + (count * uint32 offsets)
    /*if (m_packType == PackType::ISPK) {
        QFile dataFile(filePath);
        if (!dataFile.open(QIODevice::ReadOnly)) return false;

        QDataStream in(&dataFile);
        in.setByteOrder(QDataStream::LittleEndian);

        quint32 spriteCount = 0;
        in >> spriteCount;
        if (in.status() != QDataStream::Ok) return false;
        m_totalFrames = spriteCount;

        m_spriteOffsets.reserve(spriteCount);
        for (quint32 i = 0; i < spriteCount; ++i) {
            quint32 offset = 0;
            in >> offset;
            if (in.status() != QDataStream::Ok) return false;
            m_spriteOffsets.append(offset);
        }

        qDebug() << "Loaded" << m_totalFrames << "ISPK offsets from" << filePath;
        return true;
    }*/

    // Fallback para outros formatos: read 16-bit sprite count
    QFile dataFile(filePath);
    if (!dataFile.open(QIODevice::ReadOnly)) return false;

    QDataStream in(&dataFile);
    in.setByteOrder(QDataStream::LittleEndian);
    quint16 spriteCount16;
    in >> spriteCount16;
    m_totalFrames = spriteCount16;

    // Para formatos que usam offsets (ASPK, EffectScreenSPK), calculamos eles.
    if (m_packType == PackType::ASPK || m_packType == PackType::EffectScreenSPK) {
        quint32 currentOffset = 2; // Começa após o contador de sprites (16-bit)
        m_spriteOffsets.reserve(spriteCount16);
        for (quint16 i = 0; i < spriteCount16; ++i) {
            m_spriteOffsets.append(currentOffset);
            if (!dataFile.seek(currentOffset)) return false;
            quint32 bodyLength;
            quint16 width, height;
            in >> bodyLength >> width >> height;
            currentOffset += 8 + bodyLength + ((quint32)height * 2);
        }
        qDebug() << "Calculated" << m_spriteOffsets.size() << "offsets for ASPK/EffectScreenSPK.";
    }
    else {
        qDebug() << "Validated GenericSPK/SSPK with" << m_totalFrames << "sprites. Offsets will be on-demand.";
    }

    return true;
}

QImage EffectSpritePack::loadSpriteAtIndex(int index, const Palette* palette) const
{
    if (!m_isValid) return QImage();

    QByteArray rawData = getRawSpriteData(index);
    if (rawData.isEmpty()) {
        qWarning() << "getRawSpriteData returned empty for index" << index;
        return QImage();
    }

    if (m_packType == PackType::EffectScreenSPK)
    {
        const Palette emptyPalette;
        const Palette& paletteToUse = (palette != nullptr) ? *palette : emptyPalette;
        return ScreenSpriteDecoder::decode(rawData, paletteToUse);
    }
    else if (m_packType == PackType::ISPK)
    {
        // rawData já contém o blob do sprite extraído via offsets; decodifica ISP
        return IndexSpriteDecoder::decode(rawData);
    }
    else if (m_packType == PackType::SSPK)
    {
        // SSPK -> shadow sprites; decodificador específico
        return ShadowSpriteDecoder::decode(rawData);
    }
    else if (m_packType == PackType::ASPK)
    {
        // --- LÓGICA ORIGINAL RESTAURADA PARA DECODIFICAR ARQUIVOS ASPK ---
        if (index < 0 || (m_isSplit && index >= m_totalFrames) || (!m_isSplit && index >= m_spriteOffsets.size())) {
            return QImage();
        }

        QString filePathToOpen;
        quint32 offsetInFile = 0;

        if (m_isSplit) {
            int fileNum = (index / m_framesPerFile) * m_framesPerFile;
            int frameIndexInFile = index % m_framesPerFile;

            filePathToOpen = QString("%1/%2.aspk").arg(m_basePath).arg(fileNum, 5, 10, QChar('0'));

            QFile tempFile(filePathToOpen);
            if (!tempFile.open(QIODevice::ReadOnly)) return QImage();

            QDataStream tempIn(&tempFile);
            tempIn.setByteOrder(QDataStream::LittleEndian);

            quint16 totalInFile;
            tempIn >> totalInFile;

            quint32 currentOffset = 2;
            for(int i = 0; i < frameIndexInFile; ++i) {
                if (!tempFile.seek(currentOffset)) return QImage();
                quint32 bodyLength;
                quint16 width, height;
                tempIn >> bodyLength >> width >> height;
                currentOffset += 8 + bodyLength + ((quint32)height * 2);
            }
            offsetInFile = currentOffset;

        }
        else {
            filePathToOpen = m_basePath;
            offsetInFile = m_spriteOffsets.at(index);
        }

        QFile dataFile(filePathToOpen);
        if (!dataFile.open(QIODevice::ReadOnly)) return QImage();

        QDataStream in(&dataFile);
        in.setByteOrder(QDataStream::LittleEndian);

        if (!dataFile.seek(offsetInFile)) return QImage();

        quint32 bodyLength;
        quint16 width, height;
        in >> bodyLength >> width >> height;

        if (width == 0 || height == 0 || width > 4096 || height > 4096) return QImage();

        QImage image(width, height, QImage::Format_ARGB32);
        image.fill(Qt::transparent);

        bool usePalette = (palette != nullptr && !palette->isEmpty());

        for (int y = 0; y < height; ++y) {
            quint8 segmentCount;
            in >> segmentCount;
            int currentX = 0;
            for (int s = 0; s < segmentCount; ++s) {
                quint8 segOffset, pixCount;
                in >> segOffset >> pixCount;
                currentX += segOffset;
                for (int p = 0; p < pixCount; ++p) {
                    if (currentX >= width) {
                        in.skipRawData(2);
                        currentX++;
                        continue;
                    }

                    quint16 pixelData;
                    in >> pixelData;

                    if (usePalette) {
                        quint8 paletteIndex = (pixelData >> 8) & 0xFF;
                        int alpha5bit = pixelData & 0x001F;
                        int alpha = (alpha5bit * 255) / 31;

                        if (paletteIndex < palette->size()) {
                            quint16 color565 = palette->at(paletteIndex);

                            int red = (color565 & 0xF800) >> 11;
                            int green = (color565 & 0x07E0) >> 5;
                            int blue = (color565 & 0x001F);

                            red = (red * 255) / 31;
                            green = (green * 255) / 63;
                            blue = (blue * 255) / 31;

                            image.setPixel(currentX, y, qRgba(red, green, blue, alpha));
                        }
                    }
                    else {
                        image.setPixel(currentX, y, convertSpriteColor(pixelData));
                    }
                    currentX++;
                }
            }
        }
        return image;
    }
    else if (m_packType == PackType::GenericSPK) {
        // heurística: nome do arquivo ou caminho contém ".sspk" ou "effect.sspk"
        // (continua compatível para casos onde detection falhou)
        bool useShadowDecoder = false;
        QString lowerPath = m_basePath.toLower();
        QString fileNameOnly = QFileInfo(m_basePath).fileName().toLower();

        if (lowerPath.endsWith(".sspk") || lowerPath.contains(".sspk") ||
            fileNameOnly == QLatin1String("effect.sspk") || fileNameOnly.contains("effect.sspk")) {
            useShadowDecoder = true;
        }

        if (useShadowDecoder) {
            qDebug() << "[EffectSpritePack] Using ShadowSpriteDecoder for" << m_basePath;
            return ShadowSpriteDecoder::decode(rawData);
        }

        return GenericSpriteDecoder::decode(rawData);
    }

    return QImage(); // Retorna uma imagem vazia se o tipo for desconhecido
}

QByteArray EffectSpritePack::getRawSpriteData(int index) const
{
    if (!m_isValid || index < 0 || index >= m_totalFrames) return QByteArray();
    if (!m_spriteOffsets.isEmpty()) {
        if (index >= m_spriteOffsets.size()) return QByteArray();

        QFile dataFile(m_basePath);
        if (!dataFile.open(QIODevice::ReadOnly)) return QByteArray();

        quint32 startOffset = m_spriteOffsets.at(index);
        if (!dataFile.seek(startOffset)) return QByteArray();

        quint32 endOffset = (index + 1 < m_spriteOffsets.size()) ? m_spriteOffsets.at(index + 1) : dataFile.size();
        return dataFile.read(endOffset - startOffset);
    }

    // --- LÓGICA DE LEITURA SEQUENCIAL (GenericSPK e pacotes divididos) ---
    QString filePath = m_basePath;
    int startIndex = m_isSplit ? (index % m_framesPerFile) : index;

    if (m_isSplit) {
        if (m_framesPerFile <= 0) return QByteArray();
        int fileNum = (index / m_framesPerFile) * m_framesPerFile;
        QString extension;
        if (m_packType == PackType::EffectScreenSPK || m_packType == PackType::GenericSPK) extension = "spk";
        else if (m_packType == PackType::ASPK) extension = "aspk";
        else if (m_packType == PackType::ISPK) extension = "ispk";
        else if (m_packType == PackType::SSPK) extension = "sspk";
        else extension = "spk";

        filePath = QString("%1/%2.%3").arg(m_basePath).arg(fileNum, 5, 10, QChar('0')).arg(extension);
    }

    QFile dataFile(filePath);
    if (!dataFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open data file:" << filePath;
        return QByteArray();
    }

    QDataStream in(&dataFile);
    in.setByteOrder(QDataStream::LittleEndian);
    in.skipRawData(2);

    // Pula os sprites anteriores
    for (int i = 0; i < startIndex; ++i) {
        if (m_packType == PackType::ASPK || m_packType == PackType::EffectScreenSPK) {
            quint32 bodyLength;
            quint16 width, height;
            in >> bodyLength >> width >> height;
            in.skipRawData(bodyLength + (height * 2));
        }
        else { // GenericSPK / SSPK
            quint16 width, height;
            in >> width >> height;
            for (int y = 0; y < height; ++y) {
                quint16 lineWordCount;
                in >> lineWordCount;
                in.skipRawData(lineWordCount * 2);
            }
        }
        if (in.status() != QDataStream::Ok) return QByteArray();
    }

    // Lê e retorna os dados do sprite desejado
    qint64 startPos = dataFile.pos();
    quint32 finalSpriteSize = 0;

    if (m_packType == PackType::ASPK || m_packType == PackType::EffectScreenSPK) {
        quint32 bodyLength;
        quint16 width, height;
        in >> bodyLength >> width >> height;
        finalSpriteSize = 8 + bodyLength + ((quint32)height * 2);
    }
    else { // GenericSPK / SSPK
        quint16 width, height;
        in >> width >> height;
        finalSpriteSize = 4; // 2 bytes width + 2 bytes height

        for (int y = 0; y < height; ++y)
        {
            quint16 lineWordCount = 0;
            in >> lineWordCount;

            // cada "word" tem 2 bytes; contamos também os 2 bytes do próprio campo lineWordCount
            qint64 lineBytes = 2 + (qint64)lineWordCount * 2;
            finalSpriteSize += lineBytes;

            // Avança o stream pelos bytes do bloco da linha (já consumimos o field lineWordCount)
            if (lineWordCount > 0) {
                if (in.status() != QDataStream::Ok) {
                    qWarning() << "getRawSpriteData: QDataStream in bad status before skip at line" << y;
                    return QByteArray();
                }
                if (!in.skipRawData(lineWordCount * 2)) {
                    qWarning() << "getRawSpriteData: failed to skip line data while calculating finalSpriteSize at line" << y;
                    return QByteArray();
                }
            }
        }
    }

    if (finalSpriteSize == 0 || in.status() != QDataStream::Ok) return QByteArray();

    dataFile.seek(startPos);
    return dataFile.read(finalSpriteSize);
}

// função auxiliar: detecta heurísticamente se rawData é um ISP (Index Sprite)
static bool isIndexSpriteBlob(const QByteArray &rawData)
{
    if (rawData.size() < 8) return false; // precisa ter pelo menos width+height+something

    QDataStream ds(rawData);
    ds.setByteOrder(QDataStream::LittleEndian);

    quint16 width=0, height=0;
    ds >> width >> height;
    if (!ds.device() || width==0 || height==0) return false;

    // tenta ler a primeira linha header (Length + SegmentCount)
    if (ds.atEnd()) return false;
    quint16 lineLen=0, segmentCount=0;
    ds >> lineLen >> segmentCount;
    if (ds.status() != QDataStream::Ok) return false;
    if (segmentCount == 0) return false; // ISP geralmente tem segmentos (pode ser 0, mas rara)

    // tenta ler o primeiro segmento header (Offset + CKPixelCount)
    if (ds.atEnd()) return false;
    quint16 segOffset=0, ckCount=0;
    ds >> segOffset >> ckCount;
    if (ds.status() != QDataStream::Ok) return false;

    // valida se há espaço suficiente para ckCount CKPixels + PixCount
    qint64 remaining = ds.device()->size() - ds.device()->pos();
    qint64 needBytes = (qint64)ckCount * 2 + 2; // ck pixels + pixCount
    if (remaining < needBytes) {
        // se não há espaço, é improvável ser ISP
        return false;
    }

    // leitura adicional: se ckCount > 0 e há CKPixels plausíveis -> muito provável ISP
    if (ckCount > 0) return true;

    // se ckCount == 0, ainda pode ser ISP. tentamos ler PixCount e ver se cabem pixels.
    quint16 pixCount = 0;
    ds >> pixCount;
    if (ds.status() != QDataStream::Ok) return false;
    remaining = ds.device()->size() - ds.device()->pos();
    if (remaining >= (qint64)pixCount * 2) {
        // plausível ISP (segment has PixCount and Pixels)
        return true;
    }

    return false;
}