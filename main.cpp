#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC"); // ou "QSQLITE", "QOCI", etc.
        db.setDatabaseName("Nom_de_ton_ODBC_ou_chemin_SQLite");
        qDebug() << "Erreur DB : " << db.lastError().text();
        if (!db.open()) {
            qDebug() << "Erreur d'ouverture DB :" << db.lastError().text();
        }
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    return a.exec();

}
// tconnecti programme a bd
