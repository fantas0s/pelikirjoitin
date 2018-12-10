#ifndef GAMEDATA_H
#define GAMEDATA_H
#include <QString>
#include <QVector>
class GameData
{
public:
    GameData();
    quint32 id;
    QString title;
    QString description;
    QVector<QString> directionList;
    bool operator==(const GameData &other);
};

#endif // GAMEDATA_H