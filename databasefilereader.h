#ifndef DATABASEFILEREADER_H
#define DATABASEFILEREADER_H
#include <QObject>
#include <QString>
class GameDataBase;
class QXmlStreamReader;

class DataBaseFileReader : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseFileReader(QObject *parent = nullptr);
signals:
    void readSuccessful();
    void readFailed(QString errorText);
public slots:
    bool readGame();
private:
    GameDataBase *m_database;
    bool readPlaces(QXmlStreamReader &stream);
    bool readAndStoreAPlace(QXmlStreamReader &stream);
};

#endif // DATABASEFILEREADER_H
