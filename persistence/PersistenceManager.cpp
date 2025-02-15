#include "PersistenceManager.h"

// Qt include per JSON e file I/O
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

// Include delle classi concrete
#include "Libri.h"
#include "Film.h"
#include "Serie_TV.h"

PersistenceManager::PersistenceManager() {}

PersistenceManager::~PersistenceManager() {}

// -----------------------
// Salvataggio in JSON
// -----------------------
bool PersistenceManager::saveToJson(const QString &filePath, const std::vector<Media*> &mediaList) {
    QJsonArray mediaArray;
    
    // Per ogni oggetto Media nella lista, costruiamo un oggetto JSON con i dati comuni e specifici.
    for (Media* media : mediaList) {
        QJsonObject mediaObject;
        mediaObject["title"] = QString::fromStdString(media->getTitle());
        mediaObject["genre"] = QString::fromStdString(media->getGenre());
        mediaObject["releaseYear"] = media->getReleaseYear();

        // Determiniamo il tipo concreto con dynamic_cast
        if (Libro* libro = dynamic_cast<Libro*>(media)) {
            mediaObject["type"] = "Libro";
            mediaObject["author"] = QString::fromStdString(libro->getAuthor());
            mediaObject["pageCount"] = libro->getPageCount();
        }
        else if (Serie_TV* serie = dynamic_cast<Serie_TV*>(media)) {
            mediaObject["type"] = "Serie_TV";
            mediaObject["seasons"] = serie->getSeasons();
            mediaObject["episodes"] = serie->getEpisodes();
            mediaObject["creator"] = QString::fromStdString(serie->getCreator());
        }
        else if (Film* film = dynamic_cast<Film*>(media)) {
            mediaObject["type"] = "Film";
            mediaObject["director"] = QString::fromStdString(film->getDirector());
            mediaObject["duration"] = film->getDuration();
        }
        mediaArray.append(mediaObject);
    }

    QJsonDocument doc(mediaArray);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    file.write(doc.toJson());
    file.close();
    return true;
}

// -----------------------
// Caricamento da JSON
// -----------------------
bool PersistenceManager::loadFromJson(const QString &filePath, std::vector<Media*> &mediaList) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray())
        return false;
    
    QJsonArray mediaArray = doc.array();
    
    // Puliamo la lista esistente (liberando la memoria) prima di caricare nuovi dati
    for (Media* media : mediaList) {
        delete media;
    }
    mediaList.clear();

    // Per ogni oggetto JSON, ricostruiamo l'oggetto Media corretto
    for (int i = 0; i < mediaArray.size(); ++i) {
        QJsonObject obj = mediaArray[i].toObject();
        std::string title = obj["title"].toString().toStdString();
        std::string genre = obj["genre"].toString().toStdString();
        int releaseYear = obj["releaseYear"].toInt();
        QString type = obj["type"].toString();

        Media* media = nullptr;
        if (type == "Libro") {
            std::string author = obj["author"].toString().toStdString();
            int pageCount = obj["pageCount"].toInt();
            media = new Libro(title, genre, releaseYear, author, pageCount);
        }
        else if (type == "Serie_TV") {
            int seasons = obj["seasons"].toInt();
            int episodes = obj["episodes"].toInt();
            std::string creator = obj["creator"].toString().toStdString();
            media = new Serie_TV(title, genre, releaseYear, seasons, episodes, creator);
        }
        else if (type == "Film") {
            std::string director = obj["director"].toString().toStdString();
            int duration = obj["duration"].toInt();
            media = new Film(title, genre, releaseYear, director, duration);
        }
        if (media != nullptr) {
            mediaList.push_back(media);
        }
    }
    return true;
}

// -----------------------
// Salvataggio in XML
// -----------------------
bool PersistenceManager::saveToXml(const QString &filePath, const std::vector<Media*> &mediaList) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("MediaList");

    for (Media* media : mediaList) {
        xmlWriter.writeStartElement("Media");
        xmlWriter.writeTextElement("Title", QString::fromStdString(media->getTitle()));
        xmlWriter.writeTextElement("Genre", QString::fromStdString(media->getGenre()));
        xmlWriter.writeTextElement("ReleaseYear", QString::number(media->getReleaseYear()));

        if (Libro* libro = dynamic_cast<Libro*>(media)) {
            xmlWriter.writeTextElement("Type", "Libro");
            xmlWriter.writeTextElement("Author", QString::fromStdString(libro->getAuthor()));
            xmlWriter.writeTextElement("PageCount", QString::number(libro->getPageCount()));
        }
        else if (Serie_TV* serie = dynamic_cast<Serie_TV*>(media)) {
            xmlWriter.writeTextElement("Type", "Serie_TV");
            xmlWriter.writeTextElement("Seasons", QString::number(serie->getSeasons()));
            xmlWriter.writeTextElement("Episodes", QString::number(serie->getEpisodes()));
            xmlWriter.writeTextElement("Creator", QString::fromStdString(serie->getCreator()));
        }
        else if (Film* film = dynamic_cast<Film*>(media)) {
            xmlWriter.writeTextElement("Type", "Film");
            xmlWriter.writeTextElement("Director", QString::fromStdString(film->getDirector()));
            xmlWriter.writeTextElement("Duration", QString::number(film->getDuration()));
        }
        xmlWriter.writeEndElement(); // Fine Media
    }

    xmlWriter.writeEndElement(); // Fine MediaList
    xmlWriter.writeEndDocument();
    file.close();
    return true;
}

// -----------------------
// Caricamento da XML
// -----------------------
bool PersistenceManager::loadFromXml(const QString &filePath, std::vector<Media*> &mediaList) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QXmlStreamReader xmlReader(&file);
    
    // Puliamo la lista esistente (liberando la memoria) prima di caricare nuovi dati
    for (Media* media : mediaList) {
        delete media;
    }
    mediaList.clear();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if (token == QXmlStreamReader::StartElement && xmlReader.name() == "Media") {
            // Variabili temporanee per i dati comuni e specifici
            QString title, genre, type;
            int releaseYear = 0;
            // Variabili per Libro
            QString author;
            int pageCount = 0;
            // Variabili per Serie_TV
            int seasons = 0, episodes = 0;
            QString creator;
            // Variabili per Film
            QString director;
            int duration = 0;

            // Legge i dati all'interno del tag <Media>
            while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "Media")) {
                if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
                    if (xmlReader.name() == "Title")
                        title = xmlReader.readElementText();
                    else if (xmlReader.name() == "Genre")
                        genre = xmlReader.readElementText();
                    else if (xmlReader.name() == "ReleaseYear")
                        releaseYear = xmlReader.readElementText().toInt();
                    else if (xmlReader.name() == "Type")
                        type = xmlReader.readElementText();
                    else if (xmlReader.name() == "Author")
                        author = xmlReader.readElementText();
                    else if (xmlReader.name() == "PageCount")
                        pageCount = xmlReader.readElementText().toInt();
                    else if (xmlReader.name() == "Seasons")
                        seasons = xmlReader.readElementText().toInt();
                    else if (xmlReader.name() == "Episodes")
                        episodes = xmlReader.readElementText().toInt();
                    else if (xmlReader.name() == "Creator")
                        creator = xmlReader.readElementText();
                    else if (xmlReader.name() == "Director")
                        director = xmlReader.readElementText();
                    else if (xmlReader.name() == "Duration")
                        duration = xmlReader.readElementText().toInt();
                    else
                        xmlReader.skipCurrentElement();
                }
                xmlReader.readNext();
            }

            Media* media = nullptr;
            if (type == "Libro") {
                media = new Libro(title.toStdString(), genre.toStdString(), releaseYear,
                                  author.toStdString(), pageCount);
            }
            else if (type == "Serie_TV") {
                media = new Serie_TV(title.toStdString(), genre.toStdString(), releaseYear,
                                     seasons, episodes, creator.toStdString());
            }
            else if (type == "Film") {
                media = new Film(title.toStdString(), genre.toStdString(), releaseYear,
                                 director.toStdString(), duration);
            }
            if (media)
                mediaList.push_back(media);
        }
    }
    
    file.close();
    return !xmlReader.hasError();
}
