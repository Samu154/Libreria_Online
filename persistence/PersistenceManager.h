#ifndef PERSISTENCE_MANAGER_H
#define PERSISTENCE_MANAGER_H

#include <vector>
#include <QString>
#include "model/Media.h"

/**
La classe PersistenceManager gestisce il salvataggio e il caricamento dei media.

Fornisce metodi per salvare e caricare una lista di oggetti Media in formato JSON e XML.
Utilizza le classi Qt per la gestione dei file e dei formati strutturati.
**/
class PersistenceManager {
public:
    PersistenceManager();
    ~PersistenceManager();

    /**
    Salva la lista dei media in un file JSON.
    "filePath" Percorso del file di destinazione.
    "mediaList" Lista dei puntatori a Media da salvare.
    ritorna true se il salvataggio ha avuto successo, false altrimenti.
    **/
    bool saveToJson(const QString &filePath, const std::vector<Media*> &mediaList);

    /**
    Carica una lista di media da un file JSON.
    "filePath" Percorso del file sorgente.
    "mediaList" Lista (passata per riferimento) in cui verranno inseriti i media caricati.
    ritorna true se il caricamento ha avuto successo, false altrimenti.
    **/
    bool loadFromJson(const QString &filePath, std::vector<Media*> &mediaList);

    /**
    Salva la lista dei media in un file XML.
    "filePath" Percorso del file di destinazione.
    "mediaList" Lista dei puntatori a Media da salvare.
    ritorna true se il salvataggio ha avuto successo, false altrimenti.
    **/
    bool saveToXml(const QString &filePath, const std::vector<Media*> &mediaList);

    /**
    Carica una lista di media da un file XML.
    "filePath" Percorso del file sorgente.
    "mediaList" Lista (passata per riferimento) in cui verranno inseriti i media caricati.
    ritorna true se il caricamento ha avuto successo, false altrimenti.
    **/
    bool loadFromXml(const QString &filePath, std::vector<Media*> &mediaList);
};

#endif
