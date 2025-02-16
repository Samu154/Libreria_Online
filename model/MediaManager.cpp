#include "MediaManager.h"
#include <algorithm>  // Per std::find_if
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "persistence/PersistenceManager.h"

void MediaManager::loadPredefinedData() { // Carica i dati predefiniti
    QString filePath = "default_media.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Impossibile aprire il file predefinito:" << filePath;
        return;
    }

    QByteArray data = file.readAll(); // Legge tutto il contenuto del file
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data); // Converte il contenuto in un documento JSON
    if (!doc.isArray()) {
        qWarning() << "Il file predefinito non contiene un array JSON";
        return;
    }

    QJsonArray mediaArray = doc.array(); // Estrae l'array JSON

    // Itera su ogni oggetto e aggiungilo al MediaManager
    for (int i = 0; i < mediaArray.size(); ++i) {
        QJsonObject obj = mediaArray[i].toObject();
        std::string title = obj["title"].toString().toStdString();
        std::string genre = obj["genre"].toString().toStdString();
        int releaseYear = obj["releaseYear"].toInt();
        QString type = obj["type"].toString();

        Media* media = nullptr;
        if (type == "Libri") {
            std::string author = obj["author"].toString().toStdString();
            int pageCount = obj["pageCount"].toInt();
            media = new Libri(title, genre, releaseYear, author, pageCount);
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
            addMedia(media);  // addMedia è il metodo del MediaManager per aggiungere un Media
        }
    }
}

// Costruttore: non è necessaria un'inizializzazione particolare qui.
MediaManager::MediaManager() {
    // Inizialmente la lista dei media è vuota.
}

// Distruttore: elimina tutti i media per evitare memory leak.
MediaManager::~MediaManager() {
    clear();
}

// Aggiunge un nuovo media alla collezione.
void MediaManager::addMedia(Media* newMedia) {
    if (newMedia) {
        mediaList.push_back(newMedia);
    }
}

// Rimuove un media dalla collezione cercando per titolo.
// Restituisce true se il media viene trovato e rimosso, false altrimenti.
bool MediaManager::removeMedia(const std::string &title) {
    // Cerca l'elemento il cui titolo corrisponde a quello passato come parametro.
    auto it = std::find_if(mediaList.begin(), mediaList.end(),
                           [&title](Media* media) {
                               return media->getTitle() == title;
                           });
    if (it != mediaList.end()) {
        // Elimina il media per liberare la memoria.
        delete *it;
        // Rimuove il puntatore dalla lista.
        mediaList.erase(it);
        return true;
    }
    return false;
}

// Cerca un media per titolo.
// Se trovato, restituisce il puntatore al media; altrimenti, restituisce nullptr.
Media* MediaManager::findMedia(const std::string &title) const {
    auto it = std::find_if(mediaList.begin(), mediaList.end(),
                           [&title](Media* media) {
                               return media->getTitle() == title;
                           });
    return (it != mediaList.end()) ? *it : nullptr;
}

// Aggiorna un media esistente sostituendolo con updatedMedia.
// Se il media con il titolo specificato viene trovato, lo elimina e sostituisce con quello nuovo.
bool MediaManager::updateMedia(const std::string &title, Media* updatedMedia) {
    for (size_t i = 0; i < mediaList.size(); ++i) {
        if (mediaList[i]->getTitle() == title) {
            // Elimina il vecchio oggetto per evitare memory leak.
            delete mediaList[i];
            // Sostituisce con il nuovo oggetto.
            mediaList[i] = updatedMedia;
            return true;
        }
    }
    return false;
}

// Restituisce la lista dei media gestiti.
const std::vector<Media*>& MediaManager::getMediaList() const {
    return mediaList;
}

// Elimina tutti i media dalla collezione e svuota il vettore.
void MediaManager::clear() {
    for (Media* media : mediaList) {
        delete media;
    }
    mediaList.clear();
}
