#include "connection.h"

Connection::Connection() {}

bool Connection::createconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Project2A"); // Nom de la source de données
    db.setUserName("ProjectCPP2A12"); // Nom de l'utilisateur
    db.setPassword("NOVA"); // Mot de passe

    if (db.open()) {
        qDebug() << "Database connection successful.";
        return true;
    } else {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return false;
    }
}
