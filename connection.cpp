#include "connection.h"
#include <QSqlError>
#include <QDebug>

Connection::Connection() {}

bool Connection::createConnect() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Project2A");
    db.setUserName("ProjectCpp2A12");
    db.setPassword("NOVA");

    if (!db.open()) {
        qDebug() << "Erreur de connexion:" << db.lastError().text();
        return false;
    }

    qDebug() << "Connexion réussie !";
    return true;
}
