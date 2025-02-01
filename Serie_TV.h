#ifndef SERIE_TV_H
#define SERIE_TV_H

#include <string>
#include <iostream>
#include "Media.h"

class Serie_TV : public Media {
private: 
    int seasons;
    int episodes;
    std::string creator;
public:
    // Costruttore: inizializza gli attributi comuni e quelli specifici della serie TV
    Serie_TV(const std::string &title, const std::string &genre, int releaseYear,
             int seasons, int episodes, const std::string &creator);

    // Distruttore virtuale (override)
    ~Serie_TV() override;

    std::string getCreator() const;

    int getSeasons() const;

    int getEpisodes() const;

    // Implementazione dell'interfaccia virtuale pura di Media per visualizzare i dettagli della serie TV
    void displayDetails() const override;
};

#endif