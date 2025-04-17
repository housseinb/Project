#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    if (c.createConnect()) {
        qDebug() << "Connexion à la base de données établie.";
    } else {
        qDebug() << "Échec de la connexion à la base de données.";
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
