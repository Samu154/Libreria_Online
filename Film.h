#ifndef FILM_H
#define FILM_H

#include <string>
#include <iostream>
#include "Media.h"

class Film : public Media {
private:
    int duration;
    std::string director;
public:
    // Costruttore: inizializza gli attributi comuni e quelli specifici del film
    Film(const std::string &title, const std::string &genre, int releaseYear,
         int duration, const std::string &director);

    // Distruttore virtuale (override)
    ~Film() override;

    std::string getDirector() const;

    int getDuration() const;

    // Implementazione dell'interfaccia virtuale pura di Media per visualizzare i dettagli del film
    void displayDetails() const override;
};

#endif