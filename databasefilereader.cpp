#include "databasefilereader.h"
#include "gamedatabase.h"
#include "choicetempstoreitem.h"
#include <QXmlStreamReader>
#include <QFile>
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
        stream.readNextStartElement();
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
    QList<ChoiceTempStoreItem> choiceStorage;
    while (stream.readNextStartElement()) {
        if (stream.name() == s_placeElementName) {
            successRead = readAndStoreAPlace(stream, &choiceStorage);
            if (!successRead) {
                break;
            }
        } else {
            stream.skipCurrentElement();
        }
    }
    if (successRead) {
        for (ChoiceTempStoreItem item : choiceStorage) {
            quint32 parentId = m_database->getIdOf(item.parentName);
            int targetIdx = 0;
            for (QString& str : item.choices) {
                m_database->addDirection(parentId, str, m_database->getIdOf(item.choiceTargets[targetIdx]));
                targetIdx++;
            }
        }
    }
    return successRead;
}


bool DataBaseFileReader::readAndStoreAPlace(QXmlStreamReader &stream, QList<ChoiceTempStoreItem> *choiceItemStore)
{
    bool successRead = true;
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
    while (successRead &&
           stream.readNextStartElement()) {
        if (stream.name() == s_textElementName) {
            if (description.isEmpty()) {
                description = stream.readElementText();
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
            ChoiceTempStoreItem itemToAdd;
            int targetIdx = 0;
            itemToAdd.parentName = title;
            for (QString& str : choiceTexts) {
                itemToAdd.choices << str;
                itemToAdd.choiceTargets << choiceTargets[targetIdx];
                targetIdx++;
            }
            choiceItemStore->append(itemToAdd);
        }
    }
    return successRead;
}
