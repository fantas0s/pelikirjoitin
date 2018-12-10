#ifndef GAMEDATABASE_H
#define GAMEDATABASE_H
#include <QObject>

class QQmlEngine;
class QJSEngine;

class GameDataBase : public QObject
{
    Q_OBJECT
public:
    static QObject* gamedatabaseProvider(QQmlEngine* engine, QJSEngine* scriptEngine);
    quint32 id(int index) const;
    int numOfPlaces() const;
    QString title(quint32 id) const;
    QString description(quint32 id) const;
    int directionCount(quint32 id) const;
    QString direction(quint32 id, int directionIndex) const;
private:
    GameDataBase();
    static GameDataBase* s_instance;
};

#endif // GAMEDATABASE_H
