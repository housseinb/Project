#include "mainwindow.h"
#include <QApplication>
#include "connection.h" // Include the connection class

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create an instance of the Connection class
    Connection conn;

    // Attempt to connect to the database
    if (conn.createconnect()) {
        qDebug() << "Database connection established successfully.";
    } else {
        qDebug() << "Failed to connect to the database.";
        return -1; // Exit if connection fails
    }

    // Create the main window
    MainWindow w;

    // Show the main window
    w.show();

    return a.exec();
}
