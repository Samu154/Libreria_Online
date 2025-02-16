#ifndef DIALOGMEDIA_H
#define DIALOGMEDIA_H

#include <QDialog>
#include "model/Media.h"

namespace Ui {
class DialogMedia;
}

class DialogMedia : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMedia(QWidget *parent = nullptr);
    ~DialogMedia();

    // Restituisce un nuovo oggetto Media creato in base ai dati inseriti
    Media* getMedia() const;

private slots:
    // Cambia la pagina dello stacked widget in base al tipo selezionato
    void on_mediaTypeComboBox_currentIndexChanged(int index);

private:
    Ui::DialogMedia *ui;
};

#endif
