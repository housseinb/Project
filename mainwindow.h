#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include "client.h"

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
    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_update_clicked(); // Update slot
    void on_pushButton_search_clicked(); // Search slot

private:
    Ui::MainWindow *ui;
    void clearInputFields();
    void displayClients(); // Method to display clients in table
};

#endif // MAINWINDOW_H
