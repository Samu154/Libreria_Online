#include "Film.h"

// Costruttore: inizializza la parte comune (Media) e gli attributi specifici di Film
Film::Film(const std::string &title, const std::string &genre, int releaseYear,
           int duration, const std::string &director)
    : Media(title, genre, releaseYear), duration(duration), director(director)
{
    // Eventuali inizializzazioni aggiuntive specifiche per Film possono essere inserite qui
}

// Distruttore virtuale
Film::~Film() {}

std::string Film::getDirector() const {
    return director;
}

int Film::getDuration() const {
    return duration;
}

// Implementazione del metodo virtuale puro per mostrare i dettagli del film
void Film::displayDetails() const {
    std::cout << "Film: " << getTitle() << "\n"
              << "Genere: " << getGenre() << "\n"
              << "Anno di pubblicazione: " << getReleaseYear() << "\n"
              << "Durata: " << duration << " minuti\n"
              << "Regista: " << director << "\n";
}