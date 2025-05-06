#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
private:
    QSqlDatabase db;
    static Connection* instance;

public:
    Connection();
    ~Connection();
    bool createconnect();
    void closeConnection();

    // Singleton pattern to ensure one database connection
    static Connection* getInstance();
    static bool isConnected();
};

#endif // CONNECTION_H
