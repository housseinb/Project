#include "client.h"
#include "connection.h"
#include <QDebug>
#include <QSqlError>

Client::Client()
{
    idClient = 0;
    firstName = "";
    lastName = "";
    email = "";
    dateOfBirth = QDate::currentDate();
    address = "";
    phone = "";
    diploma = "";
    domain = "";
}

Client::Client(QString firstName, QString lastName, QString email, QDate dateOfBirth,
               QString address, QString phone, QString diploma, QString domain, QStringList skills)
{
    this->idClient = 0; // Will be assigned by the database
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->dateOfBirth = dateOfBirth;
    this->address = address;
    this->phone = phone;
    this->diploma = diploma;
    this->domain = domain;
    this->skills = skills;
}

Client::Client(int idClient, QString firstName, QString lastName, QString email, QDate dateOfBirth,
               QString address, QString phone, QString diploma, QString domain, QStringList skills)
{
    this->idClient = idClient;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->dateOfBirth = dateOfBirth;
    this->address = address;
    this->phone = phone;
    this->diploma = diploma;
    this->domain = domain;
    this->skills = skills;
}

bool Client::addClient() const
{

    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (NOM, PRENOM, EMAIL, DATE_NAISSANCE, ADRESSE, TELEPHONE, DIPLOME, DOMAINE_ETUDE, SKILLS) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");

    // Use valid data
    query.addBindValue(firstName);       // "John"
    query.addBindValue(lastName);        // "Doe"
    query.addBindValue(email);            // "john.doe@example.com"
    query.addBindValue(dateOfBirth);     // QDate object for "1990-01-01"
    query.addBindValue(address);          // "123 Main St"
    query.addBindValue(phone);            // "555-1234"
    query.addBindValue("Technicien");     // Valid diploma
    query.addBindValue("Génie Logiciel"); // Valid domain
    query.addBindValue("C/C++");          // Valid skill

    // Debugging: Print values being inserted
    qDebug() << "Inserting client with values:";
    qDebug() << "First Name:" << firstName;
    qDebug() << "Last Name:" << lastName;
    qDebug() << "Email:" << email;
    qDebug() << "Date of Birth:" << dateOfBirth.toString("yyyy-MM-dd");
    qDebug() << "Address:" << address;
    qDebug() << "Phone:" << phone;
    qDebug() << "Diploma:" << "Technicien";
    qDebug() << "Domain:" << "Génie Logiciel";
    qDebug() << "Skills:" << "C/C++";

    if (!query.exec()) {
        qDebug() << "Error inserting client:";
        qDebug() << "Error code:" << query.lastError().nativeErrorCode();
        qDebug() << "Error text:" << query.lastError().text();
        qDebug() << "Error type:" << query.lastError().type();
        qDebug() << "Query:" << query.lastQuery();
        return false;
    }

    qDebug() << "Client added successfully!";
    return true;
}

// Other methods (deleteClient, getAllClients, search) remain unchanged
bool Client::deleteClient(int idClient) const
{

    QSqlQuery query;
    query.prepare("DELETE FROM Client WHERE Id_Client = :idClient");
    query.bindValue(":idClient", idClient);

    if (!query.exec()) {
        qDebug() << "Error deleting client:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<Client> Client::getAllClients() const
{
    QList<Client> clients;


    QSqlQuery query("SELECT * FROM Client");

    while (query.next())
    {
        // Use index-based access instead of field names to avoid encoding issues
        int id = query.value(0).toInt(); // Assuming Id_Client is the first column
        QString firstName = query.value(1).toString(); // Assuming Nom is the second column
        QString lastName = query.value(2).toString(); // Assuming Prenom is the third column
        QString email = query.value(3).toString(); // Assuming Email is the fourth column
        QDate dateOfBirth = query.value(4).toDate(); // Assuming Date_Naissance is the fifth column
        QString address = query.value(5).toString(); // Assuming Adresse is the sixth column
        QString phone = query.value(6).toString(); // Assuming Telephone is the seventh column
        QString diploma = query.value(7).toString(); // Assuming Diplome is the eighth column
        QString domain = query.value(8).toString(); // Assuming Domaine_Etude is the ninth column
        QStringList skills = query.value(9).toString().split(", "); // Assuming Competences is the tenth column

        // Debugging to see what's being retrieved
        qDebug() << "Retrieved client:" << id << firstName << lastName << email;

        Client client(id, firstName, lastName, email, dateOfBirth, address, phone, diploma, domain, skills);
        clients.append(client);
    }

    return clients;
}

QSqlQueryModel* Client::search(const QString &searchText) const
{
    auto* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM Client WHERE Nom LIKE :search OR Prenom LIKE :search");
    query.bindValue(":search", "%" + searchText + "%");

    if (query.exec()) {
        model->setQuery(std::move(query));
    } else {
        qDebug() << "Error executing search query:" << query.lastError().text();
    }

    return model;
}
