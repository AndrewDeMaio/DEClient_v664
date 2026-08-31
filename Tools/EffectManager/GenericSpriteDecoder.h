#ifndef GENERICSPRITEDECODER_H
#define GENERICSPRITEDECODER_H

#include <QImage>
#include <QByteArray>

class GenericSpriteDecoder
{
public:
    static QImage decode(const QByteArray& spriteData);
};

#endif // GENERICSPRITEDECODER_H