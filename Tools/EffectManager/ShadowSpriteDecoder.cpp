#include "ShadowSpriteDecoder.h"
#include <QDataStream>
#include <QDebug>
#include <QtEndian>
#include <QIODevice>

// Nota: shadow sprites armazenam apenas segmentos (offset + pixcount) por linha.
// Não há palavras de cor — os pixels são implicitamente sombra (preto).

QImage ShadowSpriteDecoder::decode(const QByteArray& spriteData)
{
    if (spriteData.isEmpty()) return QImage();

    QDataStream stream(spriteData);
    stream.setByteOrder(QDataStream::LittleEndian);

    quint16 width = 0, height = 0;
    if (stream.atEnd()) return QImage();
    stream >> width >> height;

    if (width == 0 || height == 0 || width > 4096 || height > 4096) {
        qWarning() << "ShadowDecoder: invalid dimensions" << width << "x" << height;
        return QImage();
    }

    QImage image(width, height, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    // Predefina cor de sombra (preto). Ajuste alpha se quiser semitransparente.
    const QRgb shadowColor = qRgba(0, 0, 0, 255);

    for (int y = 0; y < height; ++y) {
        // Verifica que há ao menos 4 bytes para len + segCount
        qint64 remaining = stream.device()->size() - stream.device()->pos();
        if (remaining < 4) {
            qWarning() << "ShadowDecoder: insuficientes bytes para linha" << y << "remaining =" << remaining;
            break;
        }

        quint16 lineLen = 0;
        quint16 segmentCount = 0;
        stream >> lineLen;
        stream >> segmentCount;

        int currentX = 0;

        // Lê cada segmento: Offset + PixCount
        for (int s = 0; s < segmentCount; ++s) {
            // Verifica existência de 4 bytes para offset+pixcount
            qint64 rem2 = stream.device()->size() - stream.device()->pos();
            if (rem2 < 4) {
                qWarning() << "ShadowDecoder: segment header truncado em linha" << y << "segment" << s;
                break;
            }

            quint16 segOffset = 0;
            quint16 pixCount = 0;
            stream >> segOffset >> pixCount;

            currentX += segOffset;

            // Preenche com sombra (não há valores de cor no arquivo)
            for (quint16 p = 0; p < pixCount; ++p) {
                if (currentX >= 0 && currentX < width) {
                    image.setPixel(currentX, y, shadowColor);
                }
                ++currentX;
            }
        }

        // Alguns arquivos podem armazenar padding/bytes extras por linha (lineLen).
        // Se for necessário pular (lineLen inclui os headers), podemos sincronizar:
        // atualmente assumimos que apenas os campos já foram lidos sequencialmente.
        Q_UNUSED(lineLen);
    }

    return image;
}