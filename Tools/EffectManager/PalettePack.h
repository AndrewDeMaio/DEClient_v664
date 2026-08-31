#pragma once

#include <QString>
#include <QVector>

// Define um tipo 'Palette' para clareza
using Palette = QVector<quint16>;

class PalettePack
{
public:
    PalettePack();

    bool load(const QString& path);
    bool save(const QString& path) const;

    bool isValid() const { return m_isValid; }
    const Palette* getPalette(int effectIndex) const;
    const QVector<Palette>& getPalettes() const { return m_palettes; }

    void setPalette(int effectIndex, const Palette& palette);

private:
    bool m_isValid = false;
    QVector<Palette> m_palettes;
};