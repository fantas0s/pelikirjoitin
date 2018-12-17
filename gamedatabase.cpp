#include "gamedatabase.h"
#include <QDateTime>
#include <QDebug>

GameDataBase* GameDataBase::s_instance = nullptr;
static const int maxNumOfDirections = 4;
static quint32 currentId = 1;

static quint32 nextFreeId()
{
    currentId += (qrand() % 10) + 1;
    return currentId;
}

GameDataBase::GameDataBase()
{
    qsrand(QDateTime::currentSecsSinceEpoch());
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

int GameDataBase::getIndexOf(quint32 id) const
{
    GameData match(id);
    return m_gameDataList.indexOf(match);
}

GameData GameDataBase::getGameData(quint32 id) const
{
    int idx = getIndexOf(id);
    if (idx >= 0)
        return m_gameDataList.at(idx);
    else
        return GameData(id);
}

GameData& GameDataBase::getGameDataRef(quint32 id)
{
    int idx = getIndexOf(id);
    if (idx >= 0) {
        return m_gameDataList[idx];
    } else {
        qWarning() << "Gamedata index not found for reference!";
        static GameData match(id);
        return match;
    }
}

quint32 GameDataBase::getIdAt(int index) const
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

QString GameDataBase::getTitle(quint32 id) const
{
    return getGameData(id).title;
}

QString GameDataBase::getDescription(quint32 id) const
{
    return getGameData(id).description;
}

int GameDataBase::getDirectionCount(quint32 parentId) const
{
    return getGameData(parentId).directionList.length();
}

QString GameDataBase::getDirection(quint32 parentId, int directionIndex) const
{
    GameData dataItem = getGameData(parentId);
    if ((directionIndex >= 0) && directionIndex < dataItem.directionList.length())
        return dataItem.directionList.at(directionIndex);
    else
        return QString();
}

quint32 GameDataBase::getDirectionTargetId(quint32 parentId, int directionIndex) const
{
    GameData dataItem = getGameData(parentId);
    if ((directionIndex >= 0) && directionIndex < dataItem.directionIdList.length())
        return dataItem.directionIdList.at(directionIndex);
    else
        return 0;
}

void GameDataBase::setTitle(quint32 id, QString title)
{
    GameData& dataItem = getGameDataRef(id);
    dataItem.title = title;
    emit titleModified(getIndexOf(id), title);
}

void GameDataBase::setDescription(quint32 id, QString description)
{
    GameData& dataItem = getGameDataRef(id);
    dataItem.description = description;
}

void GameDataBase::setDirection(quint32 parentId, int directionIndex, QString direction)
{
    GameData& dataItem = getGameDataRef(parentId);
    if (dataItem.directionList.length() > directionIndex) {
        dataItem.directionList[directionIndex] = direction;
    } else {
        qWarning() << "Not enough directions, cannot modify" << directionIndex;
    }
}

void GameDataBase::setDirectionTargetId(quint32 parentId, int directionIndex, quint32 targetId)
{
    GameData& dataItem = getGameDataRef(parentId);
    if (dataItem.directionIdList.length() > directionIndex) {
        dataItem.directionIdList[directionIndex] = targetId;
    } else {
        qWarning() << "Not enough direction IDs, cannot modify" << directionIndex;
    }
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

void GameDataBase::addData(QString title, QString description)
{
    GameData dataItem(nextFreeId());
    dataItem.title = title;
    dataItem.description = description;
    m_gameDataList.append(dataItem);
    int idx = getIndexOf(dataItem.id);
    if (idx >= 0)
        emit indexAdded(idx);
}

void GameDataBase::deleteData(quint32 id)
{
    int idx = getIndexOf(id);
    if (idx >= 0) {
        m_gameDataList.removeAt(idx);
        emit indexDeleted(idx);
    }
}
