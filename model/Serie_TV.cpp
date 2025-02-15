#include "Serie_TV.h"

//Costruttore: inizializza la parte comune (Media) e gli attributi specifici di Serie_TV
Serie_TV::Serie_TV(const std::string &title, const std::string &genre, int releaseYear,
                   int seasons, int episodes, const std::string &creator)
    : Media(title, genre, releaseYear), seasons(seasons), episodes(episodes), creator(creator)
{}

//Distruttore virtuale
Serie_TV::~Serie_TV() {}

std::string Serie_TV::getCreator() const {
    return creator;
}

int Serie_TV::getSeasons() const {
    return seasons;
}

int Serie_TV::getEpisodes() const {
    return episodes;
}

//Implementazione del metodo virtuale puro per mostrare i dettagli della serie TV
void Serie_TV::displayDetails() const {
    std::cout << "Serie TV: " << getTitle() << "\n"
              << "Genere: " << getGenre() << "\n"
              << "Anno di pubblicazione: " << getReleaseYear() << "\n"
              << "Stagioni: " << seasons << "\n"
              << "Episodi: " << episodes << "\n"
              << "Creatore: " << creator << "\n";
}