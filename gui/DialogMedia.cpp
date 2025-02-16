#include "DialogMedia.h"
#include "ui_DialogMedia.h"

// Include delle classi concrete
#include "model/Libri.h"
#include "model/Film.h"
#include "model/Serie_TV.h"

DialogMedia::DialogMedia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMedia)
{
    ui->setupUi(this);

    // Imposta gli elementi del combobox per selezionare il tipo di media
    ui->mediaTypeComboBox->addItem("Libri");
    ui->mediaTypeComboBox->addItem("Film");
    ui->mediaTypeComboBox->addItem("Serie_TV");

    // Mostra la pagina corretta nello stacked widget in base al tipo
    connect(ui->mediaTypeComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(on_mediaTypeComboBox_currentIndexChanged(int)));
}

DialogMedia::~DialogMedia()
{
    delete ui;
}

void DialogMedia::on_mediaTypeComboBox_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

Media* DialogMedia::getMedia() const
{
    // Dati comuni
    std::string title = ui->titleLineEdit->text().toStdString();
    std::string genre = ui->genreLineEdit->text().toStdString();
    int releaseYear = ui->releaseYearSpinBox->value();

    Media* media = nullptr;
    int typeIndex = ui->mediaTypeComboBox->currentIndex();
    switch (typeIndex) {
        case 0: { // Libro
            std::string author = ui->authorLineEdit->text().toStdString();
            int pageCount = ui->pageCountSpinBox->value();
            media = new Libri(title, genre, releaseYear, author, pageCount);
            break;
        }
        case 1: { // Film
            std::string director = ui->directorLineEdit->text().toStdString();
            int duration = ui->durationSpinBox->value();
            media = new Film(title, genre, releaseYear, director, duration);
            break;
        }
        case 2: { // Serie TV
            int seasons = ui->seasonsSpinBox->value();
            int episodes = ui->episodesSpinBox->value();
            std::string creator = ui->creatorLineEdit->text().toStdString();
            media = new Serie_TV(title, genre, releaseYear, seasons, episodes, creator);
            break;
        }
        default:
            break;
    }
    return media;
}
