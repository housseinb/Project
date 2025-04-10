#include "client.h"
#include "connection.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QProcess>
#include <QCoreApplication>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

const QMap<QString, QString> diplomaMap = {
    {"Technician", "Technicien"},
    {"Master", "Master"},
    {"Engineer", "Ingénieur"}
};

const QMap<QString, QString> domainMap = {
    {"Software Engineering", "Génie Logiciel"},
    {"Embedded Systems", "Systèmes Embarqués"},
    {"Data Science", "Data Science"},
    {"Business Intelligence", "Business Intelligence"}
};

const QMap<QString, QString> skillsMap = {
    {"Digital Marketing", "Marketing Digital"},
    {"Multimedia Design", "Design et Multimédia"},
    {"C/C++", "C/C++"},
    {"Python", "Python"},
    {"Frontend", "Frontend"},
    {"Backend", "Backend"},
    {"Full Stack MERN", "Full Stack MERN"},
    {"Full Stack JS", "Full Stack JS"},
    {"Mobile", "Mobile"},
    {"Security", "Sécurité"}
};

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

    QString dbDiploma = diplomaMap.value(diploma, "Technicien");
    QString dbDomain = domainMap.value(domain, "Génie Logiciel");

    QStringList dbSkills;
    for (const QString& skill : skills) {
        dbSkills.append(skillsMap.value(skill, skill));
    }
    QString skillsValue = dbSkills.join(", ");


    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(email);
    query.addBindValue(dateOfBirth);
    query.addBindValue(address);
    query.addBindValue(phone);
    query.addBindValue(dbDiploma);
    query.addBindValue(dbDomain);
    query.addBindValue(skillsValue);

    if (!query.exec()) {
        qDebug() << "Error inserting client:" << query.lastError().text();
        return false;
    }

    return true;
}


bool Client::deleteClient(int idClient) const
{
    QSqlQuery query;
    query.prepare("DELETE FROM Client WHERE ID_CLIENT = :idClient");
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
    QSqlQuery query("SELECT ID_CLIENT, NOM, PRENOM, EMAIL, DATE_NAISSANCE, ADRESSE, TELEPHONE, DIPLOME, DOMAINE_ETUDE, SKILLS FROM CLIENT");

    while (query.next())
    {
        int id = query.value("ID_CLIENT").toInt();
        QString firstName = query.value("NOM").toString();
        QString lastName = query.value("PRENOM").toString();
        QString email = query.value("EMAIL").toString();
        QDate dateOfBirth = query.value("DATE_NAISSANCE").toDate();
        QString address = query.value("ADRESSE").toString();
        QString phone = query.value("TELEPHONE").toString();
        QString diploma = query.value("DIPLOME").toString();
        QString domain = query.value("DOMAINE_ETUDE").toString();
        QString skills = query.value("SKILLS").toString();

        // Debug output to verify values
        qDebug() << "ID:" << id << "First Name:" << firstName << "Last Name:" << lastName << "Email:" << email
                 << "DOB:" << dateOfBirth.toString() << "Address:" << address << "Phone:" << phone
                 << "Diploma:" << diploma << "Domain:" << domain << "Skills:" << skills;

        QStringList skillsList = skills.split(","); // Split skills into a list

        Client client(id, firstName, lastName, email, dateOfBirth, address, phone, diploma, domain, skillsList);
        clients.append(client);
        qDebug() << "Diploma:" << diploma << "Domain:" << domain << "Skills:" << skills;
    }

    return clients;
}

QSqlQueryModel* Client::search(const QString &searchText) const
{
    auto* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM Client WHERE "
                  "Nom LIKE :search OR "
                  "Prenom LIKE :search OR "
                  "Email LIKE :search OR "
                  "Diplome LIKE :search OR "
                  "Domaine_Etude LIKE :search OR "
                  "Skills LIKE :search");
    query.bindValue(":search", "%" + searchText + "%");

    if (query.exec()) {
        model->setQuery(std::move(query));
    } else {
        qDebug() << "Error executing search query:" << query.lastError().text();
    }

    return model;
}
bool Client::updateClient(int idClient, QString firstName, QString lastName, QString email, QDate dateOfBirth,
                          QString address, QString phone, QString diploma, QString domain, QStringList skills) const
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET NOM = ?, PRENOM = ?, EMAIL = ?, DATE_NAISSANCE = ?, ADRESSE = ?, TELEPHONE = ?, DIPLOME = ?, DOMAINE_ETUDE = ?, SKILLS = ? WHERE ID_CLIENT = ?");

    QString dbDiploma = diplomaMap.value(diploma, "Technicien");
    QString dbDomain = domainMap.value(domain, "Génie Logiciel");

    QStringList dbSkills;
    for (const QString& skill : skills) {
        dbSkills.append(skillsMap.value(skill, skill));
    }

    QString skillsValue = dbSkills.isEmpty() ? "C/C++" : dbSkills.join(", ");

    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(email);
    query.addBindValue(dateOfBirth);
    query.addBindValue(address);
    query.addBindValue(phone);
    query.addBindValue(dbDiploma);
    query.addBindValue(dbDomain);
    query.addBindValue(skillsValue);
    query.addBindValue(idClient);

    if (!query.exec()) {
        qDebug() << "Error updating client:" << query.lastError().text();
        return false;
    }

    return true;
}
QMap<QString, int> Client::getClientsByDiploma() {
    QMap<QString, int> diplomaCounts;
    QSqlQuery query("SELECT DIPLOME, COUNT(*) FROM CLIENT GROUP BY DIPLOME");

    while (query.next()) {
        QString diploma = query.value(0).toString();
        int count = query.value(1).toInt();
        diplomaCounts[diploma] = count;
    }

    return diplomaCounts;
}

QMap<QString, int> Client::getClientsByDomain() {
    QMap<QString, int> domainCounts;
    QSqlQuery query("SELECT DOMAINE_ETUDE, COUNT(*) FROM CLIENT GROUP BY DOMAINE_ETUDE");

    while (query.next()) {
        QString domain = query.value(0).toString();
        int count = query.value(1).toInt();
        domainCounts[domain] = count;
    }

    return domainCounts;
}

QMap<QString, int> Client::getClientsByAgeGroup() {
    QMap<QString, int> ageGroups;
    QSqlQuery query("SELECT "
                    "CASE "
                    "WHEN FLOOR(DATEDIFF(CURRENT_DATE, DATE_NAISSANCE)/365 &lt; 20 THEN 'Under 20' "
                    "WHEN FLOOR(DATEDIFF(CURRENT_DATE, DATE_NAISSANCE)/365 BETWEEN 20 AND 29 THEN '20-29' "
                    "WHEN FLOOR(DATEDIFF(CURRENT_DATE, DATE_NAISSANCE)/365 BETWEEN 30 AND 39 THEN '30-39' "
                    "WHEN FLOOR(DATEDIFF(CURRENT_DATE, DATE_NAISSANCE)/365 BETWEEN 40 AND 49 THEN '40-49' "
                    "ELSE '50+' "
                    "END AS age_group, "
                    "COUNT(*) "
                    "FROM CLIENT "
                    "GROUP BY age_group");

    while (query.next()) {
        QString ageGroup = query.value(0).toString();
        int count = query.value(1).toInt();
        ageGroups[ageGroup] = count;
    }

    return ageGroups;
}
//////////
///
///
///
QStringList Client::extractSkillsFromPDF(const QString &pdfPath)
{
    QStringList skills;
    QProcess pythonProcess;

    // Determine Python executable
    QString pythonExe = "python"; // Default

#ifdef Q_OS_WIN
    pythonExe = "python.exe"; // Windows
#endif

    // Get script path (next to executable)
    QString scriptPath = QDir::toNativeSeparators(
        QCoreApplication::applicationDirPath() + "/skill_extractor.py"
        );

    pythonProcess.start(pythonExe, {scriptPath, QDir::toNativeSeparators(pdfPath)});

    if (!pythonProcess.waitForFinished(5000)) { // 5-second timeout
        qDebug() << "Python process error:" << pythonProcess.errorString();
        return skills;
    }

    QByteArray output = pythonProcess.readAllStandardOutput();
    QJsonDocument doc = QJsonDocument::fromJson(output);

    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        if (obj["status"].toString() == "success") {
            QJsonArray skillsArray = obj["skills"].toArray();
            for (const QJsonValue &value : skillsArray) {
                skills.append(value.toString());
            }
        } else {
            qDebug() << "Skill extraction error:" << obj["message"].toString();
        }
    }

    return skills;
}

/*void Client::addSkills(const QStringList &newSkills)
{
    for (const QString &skill : newSkills) {
        if (!skills.contains(skill, Qt::CaseInsensitive)) {
            skills.append(skill);
        }
    }
}
*/
