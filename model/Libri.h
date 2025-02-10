#ifndef LIBRI_H
#define LIBRI_H

#include <string>
#include <iostream>
#include "Media.h"

class Libri : public Media {
private:
    std::string author;   
    int pageCount;        

public:
    // Costruttore: inizializza gli attributi comuni e quelli specifici del libro
    Libri(const std::string &title, const std::string &genre, int releaseYear,
          const std::string &author, int pageCount);

    // Distruttore virtuale (override)
    ~Libri() override;

    std::string getAuthor() const;

    int getPageCount() const;

    // Implementazione dell'interfaccia virtuale pura di Media per visualizzare i dettagli del libro
    void displayDetails() const override;
};

#endif
