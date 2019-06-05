#include "databasefilereader.h"
#include "gamedatabase.h"
#include <QXmlStreamReader>
#include <QDebug>

#define VERSION_MAJOR  1
#define VERSION_MINOR  0

const QString s_topLevelElementName = "PELIDATA";
const QString s_nameElementName = "NIMI";
const QString s_beginElementName = "ALKU";
const QString s_gameElementName = "PELI";
const QString s_placeElementName = "PAIKKA";
const QString s_textElementName = "TEKSTI";
const QString s_choiceElementName = "VALINTA";

const QString s_versionAttributeName = "versio";
const QString s_nameAttributeName = "nimi";
const QString s_targetAttributeName = "kohde";

DataBaseFileReader::DataBaseFileReader(QObject *parent) :
    QObject(parent)
{
    m_database = qobject_cast<GameDataBase*>(GameDataBase::gamedatabaseProvider(nullptr, nullptr));
}

bool DataBaseFileReader::readGame()
{
    QFile input("testfile.txt");
    bool successRead = false;
    if (input.open(QIODevice::ReadOnly)) {
        QXmlStreamReader stream(&input);
        if (stream.isStartElement() && stream.name() == s_topLevelElementName) {
            while (stream.readNextStartElement()) {
                if (stream.name() == s_gameElementName) {
                    successRead = readPlaces(stream);
                    if (!successRead) {
                        break;
                    }
                } else {
                    stream.skipCurrentElement();
                }
            }
        }
    }
    if (successRead) {
        emit readSuccessful();
    } else {
        emit readFailed("Tiedoston lukeminen epäonnistui");
    }
    return successRead;
}

bool DataBaseFileReader::readPlaces(QXmlStreamReader& stream)
{
    bool successRead = false;
    while (stream.readNextStartElement()) {
        if (stream.name() == s_placeElementName) {
            successRead = readAndStoreAPlace(stream);
            if (!successRead) {
                break;
            }
        } else {
            stream.skipCurrentElement();
        }
    }
    return successRead;
}


bool DataBaseFileReader::readAndStoreAPlace(QXmlStreamReader &stream)
{
    bool successRead = false;
    QString title;
    QXmlStreamAttributes attributes = stream.attributes();
    for (QXmlStreamAttribute& attr : attributes) {
        if (attr.name() == s_nameAttributeName) {
            title = attr.value().toString();
            break;
        }
    }
    QString description;
    QStringList choiceTexts;
    QStringList choiceTargets;
    while (stream.readNextStartElement()) {
        if (stream.name() == s_textElementName) {
            if (description.isEmpty()) {
                successRead = true;
            } else {
                qWarning() << "Double description!";
                successRead = false;
                break;
            }
        } else if (stream.name() == s_choiceElementName) {
            attributes = stream.attributes();
            for (QXmlStreamAttribute& attr : attributes) {
                if (attr.name() == s_targetAttributeName) {
                    choiceTargets << attr.value().toString();
                    break;
                }
            }
            choiceTexts << stream.readElementText();
            if (choiceTexts.length() > choiceTargets.length()) {
                choiceTargets << QString();
            }
        } else {
            stream.skipCurrentElement();
        }
    }
    if (successRead) {
        if (title.isEmpty() ||
            description.isEmpty() ||
            choiceTexts.length() != choiceTargets.length()) {
            successRead = false;
        } else {
            m_database->addData(title, description);
            quint32 parentId = m_database->getIdOf(title);
            int targetIdx = 0;
            for (QString& str : choiceTexts) {
                m_database->addDirection(parentId, str, m_database->getIdOf(choiceTargets[targetIdx]));
                targetIdx++;
            }
        }
    }
    return successRead;
}
