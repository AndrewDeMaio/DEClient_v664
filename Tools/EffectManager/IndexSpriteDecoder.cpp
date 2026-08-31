#include "IndexSpriteDecoder.h"
#include <QDataStream>
#include <QImage>
#include <QDebug>

// Converte 16-bit RGB565 para ARGB (alpha = 255)
static QRgb convert565ToArgb(quint16 color565)
{
    int red = (color565 & 0xF800) >> 11;
    int green = (color565 & 0x07E0) >> 5;
    int blue = (color565 & 0x001F);

    red = (red * 255) / 31;
    green = (green * 255) / 63;
    blue = (blue * 255) / 31;

    return qRgba(red, green, blue, 255);
}

QImage IndexSpriteDecoder::decode(const QByteArray& spriteData)
{
    if (spriteData.isEmpty()) return QImage();

    QDataStream in(spriteData);
    in.setByteOrder(QDataStream::LittleEndian);

    quint16 width = 0, height = 0;
    in >> width >> height;
    if (in.status() != QDataStream::Ok) {
        qWarning() << "IndexSpriteDecoder::decode: failed to read width/height";
        return QImage();
    }

    if (width == 0 || height == 0 || width > 4096 || height > 4096) {
        qWarning() << "IndexSpriteDecoder::decode: invalid dimensions" << width << "x" << height;
        return QImage();
    }

    QImage image(width, height, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    // Para cada linha
    for (int y = 0; y < height; ++y) {
        if (in.atEnd()) {
            qWarning() << "IndexSpriteDecoder::decode: unexpected end of data while reading line" << y;
            return image;
        }

        quint16 lineLength = 0, segmentCount = 0;
        in >> lineLength >> segmentCount;
        if (in.status() != QDataStream::Ok) {
            qWarning() << "IndexSpriteDecoder::decode: failed reading line header at" << y;
            return image;
        }

        int currentX = 0;

        for (int s = 0; s < segmentCount; ++s) {
            quint16 segOffset = 0, ckCount = 0;
            in >> segOffset >> ckCount;
            if (in.status() != QDataStream::Ok) {
                qWarning() << "IndexSpriteDecoder::decode: failed reading segment header y=" << y << "s=" << s;
                return image;
            }

            // Offset relativo à linha/segmento
            currentX += segOffset;

            // Lê CK pixels (chroma-key list)
            for (quint16 i = 0; i < ckCount; ++i) {
                quint16 ckPix = 0;
                in >> ckPix;
                if (in.status() != QDataStream::Ok) {
                    qWarning() << "IndexSpriteDecoder::decode: failed reading CK pixel y=" << y << "s=" << s << "i=" << i;
                    return image;
                }

                if (currentX >= 0 && currentX < width) {
                    image.setPixel(currentX, y, convert565ToArgb(ckPix));
                }
                currentX++;
            }

            // Lê quantidade de pixels reais e os coloca
            quint16 pixCount = 0;
            in >> pixCount;
            if (in.status() != QDataStream::Ok) {
                qWarning() << "IndexSpriteDecoder::decode: failed reading PixCount y=" << y << "s=" << s;
                return image;
            }

            for (quint16 p = 0; p < pixCount; ++p) {
                quint16 pix = 0;
                in >> pix;
                if (in.status() != QDataStream::Ok) {
                    qWarning() << "IndexSpriteDecoder::decode: failed reading pixel y=" << y << "s=" << s << "p=" << p;
                    return image;
                }

                if (currentX >= 0 && currentX < width) {
                    image.setPixel(currentX, y, convert565ToArgb(pix));
                }
                currentX++;
            }
        }
    }

    return image;
}

QImage IndexSpriteDecoder::decodeFromPack(const QByteArray& packData, int index)
{
    if (packData.isEmpty() || index < 0) return QImage();

    QDataStream in(packData);
    in.setByteOrder(QDataStream::LittleEndian);

    // Lê quantidade de sprites (uint32)
    quint32 spriteCount = 0;
    if (in.atEnd()) {
        qWarning() << "IndexSpriteDecoder: empty pack";
        return QImage();
    }
    in >> spriteCount;
    if (in.status() != QDataStream::Ok || spriteCount == 0) {
        qWarning() << "IndexSpriteDecoder: invalid pack header or zero sprites";
        return QImage();
    }

    // Lê tabela de offsets (spriteCount x uint32)
    QVector<quint32> offsets;
    offsets.reserve(spriteCount);
    for (quint32 i = 0; i < spriteCount; ++i) {
        quint32 off = 0;
        in >> off;
        if (in.status() != QDataStream::Ok) {
            qWarning() << "IndexSpriteDecoder: failed reading offsets at" << i;
            return QImage();
        }
        offsets.append(off);
    }

    if ((quint32)index >= offsets.size()) {
        qWarning() << "IndexSpriteDecoder: requested index out of range" << index << "of" << offsets.size();
        return QImage();
    }

    // Calcula intervalo do sprite no pacote
    quint32 start = offsets.at(index);
    quint32 end = (index + 1 < offsets.size()) ? offsets.at(index + 1) : (quint32)packData.size();

    if (start >= end || end > (quint32)packData.size()) {
        qWarning() << "IndexSpriteDecoder: invalid offsets for index" << index << "start=" << start << "end=" << end << "packSize=" << packData.size();
        return QImage();
    }

    QByteArray spriteBlob = packData.mid(start, end - start);

    // Decodifica o blob do sprite (formato ISP)
    return IndexSpriteDecoder::decode(spriteBlob);
}