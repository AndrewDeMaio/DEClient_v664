#ifndef SHADOWSPRITEDECODER_H
#define SHADOWSPRITEDECODER_H

#include <QImage>
#include <QByteArray>

class ShadowSpriteDecoder
{
public:
    // Decodifica um sprite em bytes (formato .sspk específico).
    // Retorna QImage vazia se falhar.
    static QImage decode(const QByteArray& spriteData);
};

#endif // SHADOWSPRITEDECODER_H