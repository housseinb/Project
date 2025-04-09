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
    void on_add_clicked();
    void on_upd_clicked();
    void on_del_clicked();
    void on_load_clicked();
    void on_downloadPdf_clicked();
    void on_filter_currentIndexChanged(int index);
    void updateDomainStatistics();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    void loadTableData();
    void setupUI();
    void setupConnections();
    void checkDatabaseConnection();
    QString loadedCodeFiscal;
};

#endif // MAINWINDOW_H
