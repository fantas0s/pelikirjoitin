#ifndef GAMEDATABASE_H
#define GAMEDATABASE_H
#include <QObject>
#include "gamedata.h"

class QQmlEngine;
class QJSEngine;

class GameDataBase : public QObject
{
    Q_OBJECT
public:
    static QObject* gamedatabaseProvider(QQmlEngine* engine, QJSEngine* scriptEngine);
    Q_INVOKABLE quint32 id(int index) const;
    int numOfPlaces() const;
    Q_INVOKABLE QString title(quint32 id) const;
    Q_INVOKABLE QString description(quint32 id) const;
    Q_INVOKABLE int directionCount(quint32 id) const;
    Q_INVOKABLE QString direction(quint32 id, int directionIndex) const;
private:
    GameDataBase();
    GameData getGameData(quint32 id) const;
    static GameDataBase* s_instance;
    QVector<GameData> m_gameDataList;
};

#endif // GAMEDATABASE_H
