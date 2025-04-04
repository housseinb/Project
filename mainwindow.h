#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "rendezvous.h"
#include <QCalendarWidget>
#include <QMainWindow>
#include <QComboBox>

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

    void on_pushButton_20_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_18_clicked();

    void on_Search_textChanged(const QString &arg1);

    void on_pushButton_11_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_22_clicked();

    void sendMail();

    void mailSent(QString status);

    void  markRendezvousOnCalendar(QCalendarWidget *calendar) ;

    void populateComboBox(QComboBox *sponsor);




private:
    int id;
    RendezVous r;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
