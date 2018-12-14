#include "gamedata.h"

GameData::GameData(quint32 idToUse) :
    id(idToUse)
{
}

GameData::GameData(const GameData &other) :
    id(other.id),
    title(other.title),
    description(other.description),
    directionList(other.directionList),
    directionIdList(other.directionIdList)
{
}

/* Private, not to be used. */
GameData::GameData() :
    id(0)
{
}

bool GameData::operator==(const GameData &other)
{
    return id == other.id;
}
