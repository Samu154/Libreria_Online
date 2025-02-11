#ifndef MEDIA_MANAGER_H
#define MEDIA_MANAGER_H

#include <vector>
#include <string>
#include "Media.h"

/**
La classe MediaManager gestisce una collezione di oggetti Media.

Fornisce metodi per aggiungere, cercare, aggiornare e rimuovere media.
Utilizza un container (std::vector) per memorizzare puntatori a Media.
Il MediaManager è parte del modello logico e non ha dipendenze dall'interfaccia grafica.
**/
class MediaManager {
public:
    // Costruttore: inizializza il gestore dei media.
    MediaManager();

    // Distruttore: dealloca tutti i media memorizzati.
    ~MediaManager();

    /**
    Aggiunge un nuovo media alla collezione.
    
    "newMedia" Puntatore all'oggetto Media da aggiungere.
    **/
    void addMedia(Media* newMedia);

    /**
    Rimuove un media dalla collezione in base al titolo.
    
    Se viene trovato un media con il titolo corrispondente, viene eliminato e rimosso.
    
    "title" Il titolo del media da rimuovere.
    ritorna true se il media è stato trovato e rimosso, false altrimenti.
    **/
    bool removeMedia(const std::string &title);

    /**
    Cerca un media per titolo.
    
    "title" Il titolo del media da cercare.
    ritorna il puntatore al media trovato, oppure nullptr se non esiste.
    **/
    Media* findMedia(const std::string &title) const;

    /**
    Aggiorna un media esistente sostituendolo con un nuovo oggetto.
     
    Se viene trovato un media con il titolo specificato, viene eliminato e
    sostituito con updatedMedia.
    
    "title" Il titolo del media da aggiornare.
    puntatore al nuovo oggetto Media.
    ritorna true se l'aggiornamento è andato a buon fine, false se il media non è stato trovato.
    **/
    bool updateMedia(const std::string &title, Media* updatedMedia);

    /**
    Restituisce la lista completa dei media gestiti.
    ritorna un riferimento costante al vettore di puntatori a Media.
    **/
    const std::vector<Media*>& getMediaList() const;

    //Elimina e rimuove tutti i media dalla collezione.

    void clear();

    // Aggiungi qui la dichiarazione per il caricamento dei dati predefiniti
    void loadPredefinedData();

private:
    // Contenitore per memorizzare i puntatori ai media.
    std::vector<Media*> mediaList;
};

#endif
