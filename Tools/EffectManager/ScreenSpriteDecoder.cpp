#include "ScreenSpriteDecoder.h"
#include <QDataStream>
#include <QDebug>
#include <QIODevice>

// Função auxiliar para decodificar a cor quando não há paleta.
// Esta lógica assume que o pixelData de 16 bits contém a cor diretamente.
static QRgb decodeColorWithoutPalette(quint16 pixelData)
{
    // Formato: R5 G6 B5 (RGB565)
    int red   = (pixelData & 0xF800) >> 11;
    int green = (pixelData & 0x07E0) >> 5;
    int blue  = (pixelData & 0x001F);

    red   = (red   * 255) / 31;
    green = (green * 255) / 63;
    blue  = (blue  * 255) / 31;

    // Sem informação de alfa, renderiza como opaco.
    return qRgba(red, green, blue, 255);
}

QImage ScreenSpriteDecoder::decode(const QByteArray& spriteData, const Palette& palette)
{
    bool usePalette = !palette.isEmpty();

    QDataStream stream(spriteData);
    stream.setByteOrder(QDataStream::LittleEndian);

    // 1. Lê o cabeçalho do sprite
    quint32 dataSize;
    quint16 width, height;
    stream >> dataSize >> width >> height;

    if (width == 0 || height == 0 || width > 2048 || height > 2048) {
        qWarning() << "Decoder Error: Invalid sprite dimensions. Width:" << width << "Height:" << height;
        return QImage();
    }

    // 2. Lê o bloco de dados RLE
    if (stream.device()->bytesAvailable() < dataSize) {
        qWarning() << "Decoder Error: Not enough data in stream for RLE data.";
        return QImage();
    }
    QByteArray rleDataBlock = stream.device()->read(dataSize);
    
    // 3. Cria a imagem e a preenche
    QImage image(width, height, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QDataStream rleStream(rleDataBlock);
    rleStream.setByteOrder(QDataStream::LittleEndian);

    for (int y = 0; y < height; ++y) {
        if (rleStream.atEnd()) break;

        quint8 packetCount;
        rleStream >> packetCount;

        int currentX = 0;
        for (int i = 0; i < packetCount; ++i) {
            if (rleStream.atEnd()) break;

            quint8 transparentCount, colorCount;
            rleStream >> transparentCount >> colorCount;

            currentX += transparentCount;

            for (int j = 0; j < colorCount; ++j) {
                if (rleStream.atEnd()) break;

                quint8 paletteIndex;
                rleStream >> paletteIndex;

                if (currentX < width)
                {
                    if (usePalette)
                    {
                        // O índice 0 da paleta é a cor transparente
                        if (paletteIndex == 0)
                        {
                            currentX++;
                            continue;
                        }

                        if (paletteIndex < palette.size())
                        {
                            quint16 color16bit = palette.at(paletteIndex);

                            // Decodifica a cor da paleta (RGB565)
                            int red = (color16bit & 0xF800) >> 11;
                            int green = (color16bit & 0x07E0) >> 5;
                            int blue = (color16bit & 0x001F);

                            // --- LÓGICA DE BRILHO (ALPHA SIMULADO) ---
                            // Calcula a luminosidade do pixel (0-255)
                            // A cor preta (r=0, g=0, b=0) terá luminosidade 0.
                            // Cores brilhantes terão alta luminosidade.
                            int luminosity = (red * 8) + (green * 4) + (blue * 8);

                            // Se o pixel for preto ou quase preto, trata como transparente (borda do brilho)
                            if (luminosity < 24)
                            { // Limiar ajustável
                                image.setPixel(currentX, y, qRgba(0, 0, 0, 0));
                            }
                            else
                            {
                                // Para outros pixels, usa a luminosidade como alfa para criar o brilho
                                red = (red * 255) / 31;
                                green = (green * 255) / 63;
                                blue = (blue * 255) / 31;
                                image.setPixel(currentX, y, qRgba(red, green, blue, qMin(255, luminosity)));
                            }
                        }
                    }
                    else
                    {
                        // Lógica de fallback sem paleta
                        image.setPixel(currentX, y, decodeColorWithoutPalette(paletteIndex));
                    }
                }
                currentX++;
            }
        }
    }

    return image;
}