#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPushButton>
#include <QDebug>

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
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);

    connect(ui->btnTutto, &QPushButton::clicked, this, &MainWindow::onFilterButtonClicked);
    connect(ui->btnLibri, &QPushButton::clicked, this, &MainWindow::onFilterButtonClicked);
    connect(ui->btnFilm, &QPushButton::clicked, this, &MainWindow::onFilterButtonClicked);
    connect(ui->btnSerieTV, &QPushButton::clicked, this, &MainWindow::onFilterButtonClicked);

    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::onEditButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    qDebug() << "Testo ricerca:" << text;
    // Inserisci qui la logica di ricerca
}

void MainWindow::onSaveButtonClicked()
{
    qDebug() << "Pulsante Salva premuto";
    // Inserisci qui la logica di salvataggio (es. tramite PersistenceManager)
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
    // Aggiorna i risultati della ricerca in base ai filtri
}

void MainWindow::onEditButtonClicked()
{
    qDebug() << "Pulsante Modifica premuto";
    // Inserisci qui la logica per modificare un prodotto
}

void MainWindow::onDeleteButtonClicked()
{
    qDebug() << "Pulsante Cancella premuto";
    // Inserisci qui la logica per cancellare un prodotto
}

void MainWindow::onAddButtonClicked()
{
    qDebug() << "Pulsante + premuto";
    // Inserisci qui la logica per aggiungere un nuovo prodotto
}
