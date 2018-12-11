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
    Q_PROPERTY(int maxDirections READ getMaxDirections)
    Q_INVOKABLE quint32 id(int index) const;
    int numOfPlaces() const;
    Q_INVOKABLE QString title(quint32 id) const;
    Q_INVOKABLE QString description(quint32 id) const;
    Q_INVOKABLE int directionCount(quint32 parentId) const;
    Q_INVOKABLE QString direction(quint32 parentId, int directionIndex) const;
    Q_INVOKABLE quint32 directionTargetId(quint32 parentId, int directionIndex) const;
    int getMaxDirections() const;
signals:
    void idDeleted(quint32 id);
    void indexDeleted(int index);
    void idAdded(quint32 id);
    void indexAdded(int index);
    void directionDeletedFromId(quint32 id);
    void directionAddedForId(quint32 id);
public slots:
    void addDirection(quint32 parentId, QString text, quint32 targetId);
    void deleteDirection(quint32 parentId, int directionIndex);
private:
    GameDataBase();
    GameData getGameData(quint32 id) const;
    GameData& getGameDataRef(quint32 id);
    static GameDataBase* s_instance;
    QVector<GameData> m_gameDataList;
};

#endif // GAMEDATABASE_H
