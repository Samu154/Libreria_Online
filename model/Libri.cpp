#include "Libri.h"

// Costruttore: inizializza la parte comune (Media) e gli attributi specifici di Libri
Libri::Libri(const std::string &title, const std::string &genre, int releaseYear,
             const std::string &author, int pageCount)
    : Media(title, genre, releaseYear), author(author), pageCount(pageCount)
{}

// Distruttore virtuale
Libri::~Libri() {}

std::string Libri::getAuthor() const {
    return author;
}

int Libri::getPageCount() const {
    return pageCount;
}

// Implementazione del metodo virtuale puro per mostrare i dettagli del libro
void Libri::displayDetails() const {
    std::cout << "Libro: " << getTitle() << "\n"
              << "Genere: " << getGenre() << "\n"
              << "Anno di pubblicazione: " << getReleaseYear() << "\n"
              << "Autore: " << author << "\n"
              << "Numero di pagine: " << pageCount << "\n";
}
