#include <QApplication>
#include "MainWindow.h" 
#include "MediaManager.h"

int main(int argc, char *argv[])
{
    // Inizializza l'applicazione Qt
    QApplication app(argc, argv);

    MediaManager manager;
    manager.loadPredefinedData(); // Carica i dati predefiniti
    
    // Crea l'istanza della finestra principale
    MainWindow mainWindow;
    
    // Mostra la finestra principale
    mainWindow.show();
    
    // Avvia il ciclo di eventi dell'applicazione e attende la chiusura
    return app.exec();
}
