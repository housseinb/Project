#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "rendezvous.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_update_clicked();

private:
    int id;
    RendezVous r;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
