#pragma once

#include <QImage>
#include <QByteArray>
#include "PalettePack.h"

class ScreenSpriteDecoder
{
public:
    static QImage decode(const QByteArray& spriteData, const Palette& palette);
};