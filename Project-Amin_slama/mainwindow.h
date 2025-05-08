#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QTableWidgetItem>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include "sponsor.h"
#include "chatbot.h"

#include <QTimer>
#include "tacheamine.h"  // Include the other UI header

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QSqlDatabase db;
    Chatbot *chatbot;
    QTimer *timer;

    void loadTableData();
    void setupUI();
    void setupConnections();
    void checkDatabaseConnection();
    void scrollToBottom();

    QString loadedCodeFiscal;

    tacheamine *tacheamineWindow; // Add this pointer to the new window
};

#endif // MAINWINDOW_H
