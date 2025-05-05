#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "nour.h"
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
    void showNour();

private:
    Ui::MainWindow *ui;
    Nour *nourWindow;
};


#endif // MAINWINDOW_H
