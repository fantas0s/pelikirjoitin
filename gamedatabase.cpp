#include "gamedatabase.h"

GameDataBase* GameDataBase::s_instance = nullptr;

GameDataBase::GameDataBase()
{
}

QObject* GameDataBase::gamedatabaseProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    if (!s_instance)
        s_instance = new GameDataBase();
    return s_instance;
}

quint32 GameDataBase::id(int index) const
{
    return index*index+1;
}

int GameDataBase::numOfPlaces() const
{
    return 3;
}

QString GameDataBase::title(quint32 id) const
{
    return QString("Otsikko %1").arg(id);
}

QString GameDataBase::description(quint32 id) const
{
    return QString("Kuvaus %0").arg(id);
}

int GameDataBase::directionCount(quint32 id) const
{
    Q_UNUSED(id);
    return 4;
}

QString GameDataBase::direction(quint32 id, int directionIndex) const
{
    return QString("Nappi %1 paikka %2").arg(id).arg(directionIndex);
}
