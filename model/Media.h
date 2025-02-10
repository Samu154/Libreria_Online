#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <iostream>

// La classe Media rappresenta l'astrazione di un media (libro, serie TV, film)
class Media {
protected:
    std::string title;      
    std::string genre;      
    int releaseYear;        

public:
    // Costruttore: inizializza i dati comuni del media
    Media(const std::string &title, const std::string &genre, int releaseYear);

    // Distruttore virtuale (importante per il polimorfismo)
    virtual ~Media();

    std::string getTitle() const;

    std::string getGenre() const;

    int getReleaseYear() const;

    // Metodo virtuale puro per la visualizzazione dei dettagli.
    // Ogni classe derivata dovrà implementare il proprio comportamento.
    virtual void displayDetails() const = 0;
};

#endif
