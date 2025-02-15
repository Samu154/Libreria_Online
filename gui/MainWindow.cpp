#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPushButton>
#include <QDebug>
#include <QListWidget>
#include "DialogMedia.h"
#include "PersistenceManager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Rendi checkable i pulsanti dei filtri
    ui->btnTutto->setCheckable(true);
    ui->btnLibri->setCheckable(true);
    ui->btnFilm->setCheckable(true);
    ui->btnSerieTV->setCheckable(true);
    // Di default "Tutto" è selezionato
    ui->btnTutto->setChecked(true);

    // Connessioni per ricerca e pulsanti
    connect(ui->searchLineEdit, &QLineEdit::textChanged,
            this, &MainWindow::onSearchTextChanged);
    connect(ui->saveButton, &QPushButton::clicked,
            this, &MainWindow::onSaveButtonClicked);

    connect(ui->btnTutto, &QPushButton::clicked,
            this, &MainWindow::onFilterButtonClicked);
    connect(ui->btnLibri, &QPushButton::clicked,
            this, &MainWindow::onFilterButtonClicked);
    connect(ui->btnFilm, &QPushButton::clicked,
            this, &MainWindow::onFilterButtonClicked);
    connect(ui->btnSerieTV, &QPushButton::clicked,
            this, &MainWindow::onFilterButtonClicked);

    connect(ui->editButton, &QPushButton::clicked,
            this, &MainWindow::onEditButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked,
            this, &MainWindow::onDeleteButtonClicked);
    connect(ui->addButton, &QPushButton::clicked,
            this, &MainWindow::onAddButtonClicked);

    // Carica dati predefiniti nel MediaManager (metodo implementato in MediaManager)
    mediaManager.loadPredefinedData();
    updateResultsList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Funzione ausiliaria per aggiornare la lista dei risultati nell'interfaccia
void MainWindow::updateResultsList()
{
    ui->resultsListWidget->clear();
    const auto &mediaList = mediaManager.getMediaList();
    for (Media* m : mediaList) {
        // Aggiungiamo ogni media come item, visualizzando il titolo
        new QListWidgetItem(QString::fromStdString(m->getTitle()), ui->resultsListWidget);
    }
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    qDebug() << "Testo ricerca:" << text;

    // Filtra la lista di media in base al testo della ricerca
    std::vector<Media*> risultati;
    QString query = text.toLower();
    const auto &mediaList = mediaManager.getMediaList();
    for (Media* m : mediaList) {
        QString titolo = QString::fromStdString(m->getTitle()).toLower();
        if (titolo.contains(query))
            risultati.push_back(m);
    }

    // Aggiorna il QListWidget con i risultati filtrati
    ui->resultsListWidget->clear();
    for (Media* m : risultati) {
        new QListWidgetItem(QString::fromStdString(m->getTitle()), ui->resultsListWidget);
    }
}

void MainWindow::onSaveButtonClicked()
{
    qDebug() << "Pulsante Salva premuto";
    // Utilizza il PersistenceManager per salvare i dati in formato JSON
    PersistenceManager pm;
    if (pm.saveToJson("data.json", mediaManager.getMediaList()))
        qDebug() << "Dati salvati con successo.";
    else
        qDebug() << "Errore nel salvataggio dei dati.";
}

void MainWindow::onFilterButtonClicked()
{
    // Otteniamo il pulsante che ha inviato il segnale
    QPushButton *senderBtn = qobject_cast<QPushButton*>(sender());
    if (!senderBtn)
        return;

    // Se "Tutto" è cliccato, deseleziona gli altri
    if (senderBtn == ui->btnTutto && senderBtn->isChecked()) {
        ui->btnLibri->setChecked(false);
        ui->btnFilm->setChecked(false);
        ui->btnSerieTV->setChecked(false);
    } else {
        // Se si clicca un filtro diverso da "Tutto", deseleziona "Tutto"
        ui->btnTutto->setChecked(false);
        // Conta quanti filtri (escluso "Tutto") sono selezionati
        int count = 0;
        if (ui->btnLibri->isChecked()) count++;
        if (ui->btnFilm->isChecked()) count++;
        if (ui->btnSerieTV->isChecked()) count++;
        // Se ne sono selezionati 3, torna a "Tutto"
        if (count >= 3) {
            ui->btnTutto->setChecked(true);
            ui->btnLibri->setChecked(false);
            ui->btnFilm->setChecked(false);
            ui->btnSerieTV->setChecked(false);
        }
    }
    qDebug() << "Filtri: Tutto:" << ui->btnTutto->isChecked()
             << "Libri:" << ui->btnLibri->isChecked()
             << "Film:" << ui->btnFilm->isChecked()
             << "SerieTV:" << ui->btnSerieTV->isChecked();

    // Filtra i media in base ai pulsanti selezionati
    std::vector<Media*> filtrati;
    const auto &mediaList = mediaManager.getMediaList();
    for (Media* m : mediaList) {
        std::string type = m->getType(); // Metodo virtuale implementato nelle classi derivate
        bool match = false;
        if (ui->btnTutto->isChecked())
            match = true;
        else {
            if (ui->btnLibri->isChecked() && type == "Libro")
                match = true;
            if (ui->btnFilm->isChecked() && type == "Film")
                match = true;
            if (ui->btnSerieTV->isChecked() && type == "Serie_TV")
                match = true;
        }
        if (match)
            filtrati.push_back(m);
    }
    // Aggiorna il QListWidget con i risultati filtrati
    ui->resultsListWidget->clear();
    for (Media* m : filtrati) {
        new QListWidgetItem(QString::fromStdString(m->getTitle()), ui->resultsListWidget);
    }
}

void MainWindow::onEditButtonClicked()
{
    qDebug() << "Pulsante Modifica premuto";
    // Verifica se è selezionato un elemento nella lista dei risultati
    QListWidgetItem *item = ui->resultsListWidget->currentItem();
    if (!item) {
        qDebug() << "Nessun elemento selezionato per la modifica.";
        return;
    }
    // Ottieni il titolo (o un identificatore) del media selezionato
    std::string title = item->text().toStdString();
    Media* media = mediaManager.findMedia(title);
    if (!media) {
        qDebug() << "Media non trovato per la modifica.";
        return;
    }
    // Apri il dialog per modificare il media
    DialogMedia dialog(this);
    // Popola il dialog con i dati del media (il metodo setMediaData va implementato in DialogMedia)
    dialog.setMediaData(media);
    if (dialog.exec() == QDialog::Accepted) {
        // Ottieni il media aggiornato dal dialog
        Media* newMedia = dialog.getMedia();
        mediaManager.updateMedia(title, newMedia);
        updateResultsList();
    }
}

void MainWindow::onDeleteButtonClicked()
{
    qDebug() << "Pulsante Cancella premuto";
    QListWidgetItem *item = ui->resultsListWidget->currentItem();
    if (!item) {
        qDebug() << "Nessun elemento selezionato per la cancellazione.";
        return;
    }
    std::string title = item->text().toStdString();
    if (mediaManager.removeMedia(title)) {
        qDebug() << "Media cancellato.";
        updateResultsList();
    } else {
        qDebug() << "Errore nella cancellazione del media.";
    }
}

void MainWindow::onAddButtonClicked()
{
    qDebug() << "Pulsante + premuto";
    // Apri il dialog per aggiungere un nuovo media
    DialogMedia dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Media* newMedia = dialog.getMedia();
        mediaManager.addMedia(newMedia);
        updateResultsList();
    }
}
