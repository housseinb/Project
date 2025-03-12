#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QList>

class Client
{
private:
    int idClient;
    QString firstName;
    QString lastName;
    QString email;
    QDate dateOfBirth;
    QString address;
    QString phone;
    QString diploma; // ComboBox field
    QString domain; // ComboBox field
    QStringList skills; // List of skills

public:
    Client();  // Default constructor
    Client(QString firstName, QString lastName, QString email, QDate dateOfBirth,
           QString address, QString phone, QString diploma, QString domain, QStringList skills); // Parameterized constructor
    Client(int idClient, QString firstName, QString lastName, QString email, QDate dateOfBirth,
           QString address, QString phone, QString diploma, QString domain, QStringList skills); // Parameterized constructor

    // Getters
    int getIdClient() const { return idClient; }
    QString getFirstName() const { return firstName; }
    QString getLastName() const { return lastName; }
    QString getEmail() const { return email; }
    QDate getDateOfBirth() const { return dateOfBirth; }
    QString getAddress() const { return address; }
    QString getPhone() const { return phone; }
    QString getDiploma() const { return diploma; }
    QString getDomain() const { return domain; }
    QStringList getSkills() const { return skills; }

    // Methods
    bool addClient() const;
    bool deleteClient(int idClient) const;
    QList<Client> getAllClients() const;
    QSqlQueryModel* search(const QString &searchText) const; // Search functionality
};

#endif // CLIENT_H
