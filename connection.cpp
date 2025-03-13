#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Project2A");
    db.setUserName("ProjectCpp2A12");
    db.setPassword("NOVA");

    if (db.open())
        test=true;





    return  test;
}
