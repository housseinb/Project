#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    c.createconnect();
    MainWindow w;
    w.show();
    return a.exec();
}
