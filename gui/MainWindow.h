#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MediaManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Finestra principale dell'applicazione
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearchTextChanged(const QString &text);
    void onSaveButtonClicked();
    void onFilterButtonClicked();
    void onEditButtonClicked();
    void onDeleteButtonClicked();
    void onAddButtonClicked();

private:
    Ui::MainWindow *ui;
    MediaManager mediaManager;
};

#endif
