#include "Media.h"

// Implementazione del costruttore
Media::Media(const std::string &title, const std::string &genre, int releaseYear)
    : title(title), genre(genre), releaseYear(releaseYear)
{}

// Distruttore virtuale
Media::~Media() {}

std::string Media::getTitle() const {
    return title;
}

std::string Media::getGenre() const {
    return genre;
}

int Media::getReleaseYear() const {
    return releaseYear;
}
