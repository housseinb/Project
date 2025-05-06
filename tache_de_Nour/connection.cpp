#include "connection.h"
#include <QDebug>

// Initialize the static instance pointer
Connection* Connection::instance = nullptr;

Connection::Connection()
{
    // Constructor is empty
}

Connection::~Connection()
{
    closeConnection();
}

bool Connection::createconnect()
{
    // Remove any existing connection with the same name
    if(QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QODBC");
    }

    db.setDatabaseName("Source_Projet2A"); // Your data source name
    db.setUserName("ProjectCpp2A12");
    db.setPassword("NOVA");

    qDebug() << "Available drivers:" << QSqlDatabase::drivers();

    if (db.open()) {
        qDebug() << "Database connection successful!";
        return true;
    } else {
        qDebug() << "Database error:" << db.lastError().text();
        return false;
    }
}

void Connection::closeConnection()
{
    if(db.isOpen()) {
        db.close();
        qDebug() << "Database connection closed.";
    }
}

Connection* Connection::getInstance()
{
    if (instance == nullptr) {
        instance = new Connection();
        instance->createconnect();
    }
    return instance;
}

bool Connection::isConnected()
{
    if (instance == nullptr) {
        return false;
    }
    return instance->db.isOpen();
}
