#include "GenericSpriteDecoder.h"
#include <QDataStream>
#include <QDebug>
#include <QIODevice>

// --- LÓGICA DE DECODIFICAÇÃO CORRIGIDA ---

// 1. Converte o pixel de RGB565 para RGB555, como na engine original.
static quint16 convert565to555(quint16 pixel565)
{
    // Isola R e G, desloca para a direita para descartar o bit menos significativo de G,
    // e então mascara para obter o formato 0RRRRRGGGGG00000.
    quint16 r_g = ((pixel565 & 0xFFE0) >> 1) & 0x7FE0;
    
    // Isola o B.
    quint16 b = pixel565 & 0x001F;
    
    // Combina para formar o pixel RGB555.
    return r_g | b;
}

// 2. Decodifica o pixel RGB555 para um QRgb de 32 bits.
static QRgb decodeRgb555(quint16 colorData555)
{
    // Formato: XRRRRRGGGGGBBBBB (o bit mais significativo é ignorado)
    int red   = (colorData555 & 0x7C00) >> 10;
    int green = (colorData555 & 0x03E0) >> 5;
    int blue  = (colorData555 & 0x001F);

    // Expande de 5 bits para 8 bits por canal
    red   = (red   * 255) / 31;
    green = (green * 255) / 31;
    blue  = (blue  * 255) / 31;

    return qRgba(red, green, blue, 255);
}

QImage GenericSpriteDecoder::decode(const QByteArray& spriteData)
{
    if (spriteData.isEmpty()) {
        return QImage();
    }

    QDataStream stream(spriteData);
    stream.setByteOrder(QDataStream::LittleEndian);

    quint16 width, height;
    stream >> width >> height;

    if (width == 0 || height == 0 || width > 4096 || height > 4096) {
        qWarning() << "Generic Decoder: Invalid sprite dimensions. Width:" << width << "Height:" << height;
        return QImage();
    }

    QImage image(width, height, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    for (int y = 0; y < height; ++y) {
        if (stream.atEnd()) break;

        quint16 rawLineSize;
        stream >> rawLineSize;

        if (rawLineSize == 0) continue;

        // --- LÓGICA ROBUSTA COM TRATAMENTO DE FLAG ---
        int bytesToRead;
        bool isByteSized = (rawLineSize & 0x8000) != 0;

        if (isByteSized) {
            // O tamanho está em bytes, e o próprio campo de tamanho está incluído.
            bytesToRead = (rawLineSize & 0x7FFF) - 2;
        } else {
            // O tamanho está em words.
            bytesToRead = rawLineSize * 2;
        }
        
        if (bytesToRead < 0) break; // Verificação de segurança

        QByteArray lineData(bytesToRead, 0);
        int bytesRead = stream.readRawData(lineData.data(), bytesToRead);

        if (bytesRead < bytesToRead) break;

        QDataStream lineStream(lineData);
        lineStream.setByteOrder(QDataStream::LittleEndian);

        quint16 segmentCount;
        lineStream >> segmentCount;

        int currentX = 0; // Inicializa currentX no início da linha

        for (int s = 0; s < segmentCount; ++s) {
            if (lineStream.atEnd()) break;

            quint16 transparentOffset, colorCount;
            lineStream >> transparentOffset >> colorCount;

            currentX += transparentOffset; // Acumula o deslocamento de píxeis transparentes

            for (int p = 0; p < colorCount; ++p) {
                if (lineStream.atEnd()) break;

                quint16 pixelColor565;
                lineStream >> pixelColor565;

                if (currentX < width) {
                    // 3. Aplica a conversão e decodificação.
                    quint16 pixelColor555 = convert565to555(pixelColor565);
                    image.setPixel(currentX, y, decodeRgb555(pixelColor555));
                }
                currentX++; // Avança para o próximo píxel
            }
        }
    }

    return image;
}