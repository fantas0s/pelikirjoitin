#include "gamedatabase.h"
#include <QDebug>

GameDataBase* GameDataBase::s_instance = nullptr;
static const int maxNumOfDirections = 4;

GameDataBase::GameDataBase()
{
    GameData dataItem;
    dataItem.id = 7;
    dataItem.title = "Eteinen";
    dataItem.description = "Olet eteisessä.\nMinne menet?";
    dataItem.directionList.append("Vessaan");
    dataItem.directionList.append("Tuulikaappiin");
    dataItem.directionList.append("Makuuhuoneeseen");
    dataItem.directionList.append("Olohuoneeseen");
    dataItem.directionIdList.append(1);
    dataItem.directionIdList.append(2);
    dataItem.directionIdList.append(3);
    dataItem.directionIdList.append(42);
    m_gameDataList.append(dataItem);
    dataItem.directionList.clear();
    dataItem.directionIdList.clear();
    dataItem.id = 42;
    dataItem.title = "Olohuone";
    dataItem.description = "Olet Olohuoneessa.\nMinne menet?";
    dataItem.directionList.append("Keittiöön");
    dataItem.directionList.append("Kodinhoitohuoneeseen");
    dataItem.directionList.append("Eteiseen");
    dataItem.directionIdList.append(56);
    dataItem.directionIdList.append(4);
    dataItem.directionIdList.append(7);
    m_gameDataList.append(dataItem);
    dataItem.directionList.clear();
    dataItem.directionIdList.clear();
    dataItem.id = 56;
    dataItem.title = "Keittiö";
    dataItem.description = "Keittiössä on ruokaa. Mitä teet?";
    dataItem.directionList.append("Syön");
    dataItem.directionList.append("Kurkistan jääkaappiin");
    dataItem.directionList.append("Katson onko pakastimessa jäätelöä");
    dataItem.directionIdList.append(12);
    dataItem.directionIdList.append(13);
    dataItem.directionIdList.append(14);
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

int GameDataBase::getMaxDirections() const
{
    return maxNumOfDirections;
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

GameData& GameDataBase::getGameDataRef(quint32 id)
{
    static GameData match;
    match.id = id;
    int idx = m_gameDataList.indexOf(match);
    if (idx >= 0) {
        return m_gameDataList[idx];
    } else {
        qWarning() << "Gamedata index not found for reference!";
        return match;
    }
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

int GameDataBase::directionCount(quint32 parentId) const
{
    return getGameData(parentId).directionList.length();
}

QString GameDataBase::direction(quint32 parentId, int directionIndex) const
{
    GameData dataItem = getGameData(parentId);
    if ((directionIndex >= 0) && directionIndex < dataItem.directionList.length())
        return dataItem.directionList.at(directionIndex);
    else
        return QString();
}

quint32 GameDataBase::directionTargetId(quint32 parentId, int directionIndex) const
{
    GameData dataItem = getGameData(parentId);
    if ((directionIndex >= 0) && directionIndex < dataItem.directionIdList.length())
        return dataItem.directionIdList.at(directionIndex);
    else
        return 0;
}

void GameDataBase::addDirection(quint32 parentId, QString text, quint32 targetId)
{
    GameData& dataItem = getGameDataRef(parentId);
    if ((dataItem.directionList.length() < getMaxDirections()) &&
        (dataItem.directionIdList.length() < getMaxDirections())) {
        dataItem.directionList.append(text);
        dataItem.directionIdList.append(targetId);
        emit directionAddedForId(parentId);
    } else {
        qWarning() << "Max num of directions reached, cannot add" << text;
    }
}

void GameDataBase::deleteDirection(quint32 parentId, int directionIndex)
{
    GameData& dataItem = getGameDataRef(parentId);
    if ((dataItem.directionList.length() > directionIndex) &&
        (dataItem.directionIdList.length() > directionIndex)) {
        dataItem.directionList.remove(directionIndex);
        dataItem.directionIdList.remove(directionIndex);
        emit directionDeletedFromId(parentId);
    } else {
        qWarning() << "Not enough directions, cannot remove" << directionIndex;
    }
}
