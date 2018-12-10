#include "gamedata.h"

GameData::GameData() :
    id(0)
{
}

bool GameData::operator==(const GameData &other)
{
    return id == other.id;
}
