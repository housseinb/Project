#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Apply global stylesheet for all message boxes


    // Check database connection
    Connection c;
    if (c.createconnect()) {
        QMessageBox::information(nullptr, "Database Connection", "Connection successful.");
        MainWindow w;
        w.show();
        return a.exec();
    } else {
        QMessageBox::critical(nullptr, "Database Connection", "Connection failed!");
        return -1; // Exit the application if the connection fails
    }
}
