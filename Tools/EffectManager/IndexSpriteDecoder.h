#ifndef INDEXSPRITEDECODER_H
#define INDEXSPRITEDECODER_H

#include <QImage>
#include <QByteArray>

class IndexSpriteDecoder
{
public:
    // Decodifica um blob que representa um sprite (mesma assinatura do Generic).
    static QImage decode(const QByteArray& spriteData);

    // Decodifica a partir de um pacote indexado (.ispk-like).
    // 'index' é o índice do sprite solicitado dentro do pacote.
    static QImage decodeFromPack(const QByteArray& packData, int index);
};

#endif // INDEXSPRITEDECODER_H