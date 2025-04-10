#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialize database connection
    Connection* c = Connection::getInstance();
    Q_UNUSED(c);
    bool test = Connection::isConnected();

    if(test) {
        MainWindow w;
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

        int result = a.exec();
        return result;
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return 1; // Exit with error code
    }
}
