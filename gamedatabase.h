#ifndef GAMEDATABASE_H
#define GAMEDATABASE_H
#include <QObject>
#include <QList>
#include "gamedata.h"

class QQmlEngine;
class QJSEngine;

class GameDataBase : public QObject
{
    Q_OBJECT
public:
    static QObject* gamedatabaseProvider(QQmlEngine* engine, QJSEngine* scriptEngine);
    Q_PROPERTY(int maxDirections READ getMaxDirections)
    Q_INVOKABLE quint32 getIdAt(int index) const;
    Q_INVOKABLE QString getTitle(quint32 id) const;
    Q_INVOKABLE QString getDescription(quint32 id) const;
    Q_INVOKABLE int getDirectionCount(quint32 parentId) const;
    Q_INVOKABLE QString getDirection(quint32 parentId, int directionIndex) const;
    Q_INVOKABLE quint32 getDirectionTargetId(quint32 parentId, int directionIndex) const;
    Q_INVOKABLE int getIndexOf(quint32 id) const;
    int numOfPlaces() const;
    int getMaxDirections() const;
    quint32 getIdOf(const QString title) const;
signals:
    void indexDeleted(int index);
    void indexAdded(int index);
    void titleModified(int index, QString title);
    void directionDeletedFromId(quint32 id);
    void directionAddedForId(quint32 id);
public slots:
    void addDirection(quint32 parentId, QString text, quint32 targetId);
    void deleteDirection(quint32 parentId, int directionIndex);
    void addData(QString title, QString description);
    void deleteData(quint32 id);
    void setTitle(quint32 id, QString title);
    void setDescription(quint32 id, QString description);
    void setDirection(quint32 parentId, int directionIndex, QString direction);
    void setDirectionTargetId(quint32 parentId, int directionIndex, quint32 targetId);
private:
    GameDataBase();
    GameData getGameData(quint32 id) const;
    GameData& getGameDataRef(quint32 id);
    static GameDataBase* s_instance;
    QList<GameData> m_gameDataList;
};

#endif // GAMEDATABASE_H
