#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>

class Connection {
public:
    Connection();
    bool createConnect();

private:
    QSqlDatabase db;
};

#endif // CONNECTION_H
