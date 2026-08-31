#include "CCreatureFramePack.h"
#include <QDataStream>
#include <QDebug>

bool CCreatureFramePack::loadFromDevice(QIODevice *device)
{
    if (!device || !device->isOpen()) return false;

    // Se o device reporta tamanho zero, não há nada a ler (comportamento similar ao C#)
    qint64 size = -1;
    if (device->isReadable() && device->openMode() & QIODevice::ReadOnly) {
        // já está aberto; ok
    }
    // tenta obter tamanho quando disponível
    if (device->bytesAvailable() == 0 && device->isSequential()) {
        // device sequencial (stream) — não podemos checar size; continuamos na leitura
    } else {
        // para QFile e outros, size() é válido
        size = device->size();
        if (size == 0) return true; // comporta-se como C# (retorna sem erro)
    }

    QDataStream ds(device);
    ds.setByteOrder(QDataStream::LittleEndian);

    quint16 creatureCount = 0;
    ds >> creatureCount;
    if (ds.status() != QDataStream::Ok) {
        qWarning() << "CCreatureFramePack: failed to read creature count";
        return false;
    }

    m_creatures.clear();
    m_creatures.reserve(creatureCount);

    for (quint16 ci = 0; ci < creatureCount; ++ci)
    {
        Creature cr;

        quint8 actionCount = 0;
        ds >> actionCount;
        if (ds.status() != QDataStream::Ok) {
            qWarning() << "CCreatureFramePack: failed to read action count for creature" << ci;
            return false;
        }

        cr.Actions.reserve(actionCount);

        for (quint8 a = 0; a < actionCount; ++a)
        {
            Action ac;

            quint8 dirCount = 0;
            ds >> dirCount;
            if (ds.status() != QDataStream::Ok) {
                qWarning() << "CCreatureFramePack: failed to read direction count for creature" << ci << "action" << a;
                return false;
            }

            ac.Directions.reserve(dirCount);

            for (quint8 d = 0; d < dirCount; ++d)
            {
                Direction di;

                quint16 frameCount = 0;
                ds >> frameCount;
                if (ds.status() != QDataStream::Ok) {
                    qWarning() << "CCreatureFramePack: failed to read frame count for creature" << ci << "action" << a << "dir" << d;
                    return false;
                }

                di.Frames.resize(frameCount);
                for (quint16 f = 0; f < frameCount; ++f)
                {
                    if (!di.Frames[f].readFrom(ds)) {
                        qWarning() << "CCreatureFramePack: failed to read frame" << f << "for creature" << ci << "action" << a << "dir" << d;
                        return false;
                    }
                }

                ac.Directions.append(std::move(di));
            }

            cr.Actions.append(std::move(ac));
        }

        m_creatures.append(std::move(cr));
    }

    return true;
}