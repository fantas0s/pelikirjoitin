#ifndef DATABASEFILEWRITER_H
#define DATABASEFILEWRITER_H
#include <QObject>
#include <QString>
class GameDataBase;

class DataBaseFileWriter : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseFileWriter(QObject *parent = nullptr);
signals:
    void saveSuccessful();
    void saveFailed(QString errorText);
public slots:
    void saveGame(QString gameName);
private:
    GameDataBase *m_database;
};

#endif // DATABASEFILEWRITER_H
