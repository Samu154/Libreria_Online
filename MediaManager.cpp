#include "MediaManager.h"
#include <algorithm>  // Per std::find_if

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
