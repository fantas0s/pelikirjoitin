#include "databasefilewriter.h"
#include "gamedatabase.h"
#include <QXmlStreamWriter>
#include <QFile>

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

DataBaseFileWriter::DataBaseFileWriter(QObject *parent) :
    QObject(parent)
{
    m_database = qobject_cast<GameDataBase*>(GameDataBase::gamedatabaseProvider(nullptr, nullptr));
}

void DataBaseFileWriter::saveGame(QString gameName)
{
    QString errorString = m_database->getConflictString();
    if (!errorString.isEmpty()) {
        emit saveFailed(errorString);
        return;
    }
    QFile output("testfile.txt");
    if (output.open(QIODevice::WriteOnly)) {
        QXmlStreamWriter stream(&output);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement(s_topLevelElementName);
        stream.writeAttribute(s_versionAttributeName, QString("%1.%2").arg(VERSION_MAJOR).arg(VERSION_MINOR));
        stream.writeTextElement(s_nameElementName, gameName);
        if (m_database->numOfPlaces()) {
            stream.writeTextElement(s_beginElementName, m_database->getTitle(m_database->getIdAt(0)));
            stream.writeStartElement(s_gameElementName);
            for (int idx = 0 ; idx < m_database->numOfPlaces() ; ++idx) {
                quint32 currentId = m_database->getIdAt(idx);
                stream.writeStartElement(s_placeElementName);
                stream.writeAttribute(s_nameAttributeName, m_database->getTitle(currentId));
                stream.writeTextElement(s_textElementName, m_database->getDescription(currentId));
                for (int directionIdx = 0 ; directionIdx < m_database->getDirectionCount(currentId) ; ++directionIdx) {
                    stream.writeStartElement(s_choiceElementName);
                    stream.writeAttribute(s_targetAttributeName, m_database->getTitle(m_database->getDirectionTargetId(currentId, directionIdx)));
                    stream.writeCharacters(m_database->getDirection(currentId, directionIdx));
                    stream.writeEndElement();
                }
                stream.writeEndElement();
            }
            stream.writeEndElement();
        }
        stream.writeEndElement();
        stream.writeEndDocument();
        output.close();
        emit saveSuccessful();
    } else {
        emit saveFailed("Tiedoston avaaminen epäonnistui");
    }
}
