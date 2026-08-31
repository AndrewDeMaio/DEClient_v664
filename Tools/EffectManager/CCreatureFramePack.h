#pragma once

#include <QVector>
#include <QScopedPointer>
#include <QIODevice>
#include <QtGlobal>

struct CCreatureFrame
{
    quint16 SpriteID;
    qint16 X;
    qint16 Y;

    CCreatureFrame() : SpriteID(0), X(0), Y(0) {}
    // Lê 6 bytes: spriteid (uint16), x (int16), y (int16)
    bool readFrom(QDataStream &ds)
    {
        ds.setByteOrder(QDataStream::LittleEndian);
        ds >> SpriteID >> X >> Y;
        return ds.status() == QDataStream::Ok;
    }
};

struct Direction
{
    QVector<CCreatureFrame> Frames;
};

struct Action
{
    QVector<Direction> Directions;
};

struct Creature
{
    QVector<Action> Actions;
};

class CCreatureFramePack
{
public:
    CCreatureFramePack() = default;
    // Constrói e tenta ler do device. Retorna falso se leitura falhar.
    bool loadFromDevice(QIODevice *device);

    const QVector<Creature>& creatures() const { return m_creatures; }
    int creatureCount() const { return m_creatures.size(); }

private:
    QVector<Creature> m_creatures;
};