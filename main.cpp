#include <QApplication>
#include "MainWindow.h" 

int main(int argc, char *argv[])
{
    // Inizializza l'applicazione Qt
    QApplication app(argc, argv);
    
    // Crea l'istanza della finestra principale
    MainWindow mainWindow;
    
    // Mostra la finestra principale
    mainWindow.show();
    
    // Avvia il ciclo di eventi dell'applicazione e attende la chiusura
    return app.exec();
}
