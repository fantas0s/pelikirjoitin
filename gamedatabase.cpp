#include "gamedatabase.h"

GameDataBase* GameDataBase::s_instance = nullptr;

GameDataBase::GameDataBase()
{
    GameData dataItem;
    dataItem.id = 7;
    dataItem.title = "Eteinen";
    dataItem.description = "Olet eteisessä.\nMinne menet?";
    dataItem.directionList.append("Vessaan");
    dataItem.directionList.append("Tuulikaappiin");
    dataItem.directionList.append("Mikaelin huoneeseen");
    dataItem.directionList.append("Martan huoneeseen");
    dataItem.directionList.append("Topiaksen huoneeseen");
    dataItem.directionList.append("Olohuoneeseen");
    m_gameDataList.append(dataItem);
    dataItem.id = 42;
    dataItem.title = "Olohuone";
    dataItem.description = "Olet Olohuoneessa.\nMinne menet?";
    dataItem.directionList.append("Keittiöön");
    dataItem.directionList.append("Kodinhoitohuoneeseen");
    m_gameDataList.append(dataItem);
    dataItem.id = 56;
    dataItem.title = "Keittiö";
    dataItem.description = "Keittiössä on ruokaa. Mitä teet?";
    dataItem.directionList.append("Syön");
    dataItem.directionList.append("Kurkistan jääkaappiin");
    dataItem.directionList.append("Katson onko pakastimessa jäätelöä");
    m_gameDataList.append(dataItem);
}

QObject* GameDataBase::gamedatabaseProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    if (!s_instance)
        s_instance = new GameDataBase();
    return s_instance;
}

GameData GameDataBase::getGameData(quint32 id) const
{
    GameData match;
    match.id = id;
    int idx = m_gameDataList.indexOf(match);
    if (idx >= 0)
        return m_gameDataList.at(idx);
    else
        return match;
}

quint32 GameDataBase::id(int index) const
{
    if ((index >= 0) && index < m_gameDataList.length())
        return m_gameDataList.at(index).id;
    else
        return 0;
}

int GameDataBase::numOfPlaces() const
{
    return m_gameDataList.length();
}

QString GameDataBase::title(quint32 id) const
{
    return getGameData(id).title;
}

QString GameDataBase::description(quint32 id) const
{
    return getGameData(id).description;
}

int GameDataBase::directionCount(quint32 id) const
{
    return getGameData(id).directionList.length();
}

QString GameDataBase::direction(quint32 id, int directionIndex) const
{
    GameData dataItem = getGameData(id);
    if ((directionIndex >= 0) && directionIndex < dataItem.directionList.length())
        return dataItem.directionList.at(directionIndex);
    else
        return QString();
}
