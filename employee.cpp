#include "employee.h"

Employee::Employee() {}

Employee::Employee(const QString &nom, const QString &email, const QString &poste, const QString &pwd)
    : nom(nom), email(email), poste(poste), pwd(pwd) {}


QString Employee::getNom() const { return nom; }
QString Employee::getEmail() const { return email; }
QString Employee::getPoste() const { return poste; }
QString Employee::getMotDePasse() const { return pwd; }


void Employee::setNom(const QString &nom) { this->nom = nom; }
void Employee::setEmail(const QString &email) { this->email = email; }
void Employee::setPoste(const QString &poste) { this->poste = poste; }
void Employee::setMotDePasse(const QString &pwd) { this->pwd = pwd; }

#include <QMessageBox>

bool Employee::enregistre_employe_db() {
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE EMAIL = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la vérification de l'email: " + query.lastError().text());
        return false;
    }

    query.next();
    int count = query.value(0).toInt();

    if (count > 0) {
        QMessageBox::warning(nullptr, "Erreur", "Cet email est déjà utilisé.");
        return false;
    }

    query.prepare("INSERT INTO EMPLOYE (EMAIL, NOM, POSTE, MOT_DE_PASSE) "
                  "VALUES (:email, :nom, :poste, :mot_de_passe)");

    query.bindValue(":email", email);
    query.bindValue(":nom", nom);
    query.bindValue(":poste", poste);
    query.bindValue(":mot_de_passe", pwd);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de l'enregistrement de l'employé: " + query.lastError().text());
        return false;
    }
    QMessageBox::information(nullptr, "Succès", "Employé enregistré avec succès !");
    return true;
}

bool Employee::connection_employe_db(QString email, QString pwd) {
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYE WHERE EMAIL = :email AND MOT_DE_PASSE = :mot_de_passe");

    query.bindValue(":email", email);
    query.bindValue(":mot_de_passe", pwd);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la connexion de l'employé: " + query.lastError().text());
        return false;
    }

    if (query.next()) {
        this->email = query.value("EMAIL").toString();
        nom = query.value("NOM").toString();
        poste = query.value("POSTE").toString();
        pwd = query.value("MOT_DE_PASSE").toString();
        Employee e(nom, email, poste, pwd);
        QMessageBox::information(nullptr, "Succès", "Connexion réussie !");

        return true;
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Email ou mot de passe incorrect.");
        return false;
    }
}

int Employee::id_user_connected(){
    if (email.isEmpty()) {
        qDebug() << "Error: Email is empty";
        return -1;
    }

    QSqlQuery query;
    query.prepare("SELECT ID_EMP FROM EMPLOYE WHERE EMAIL = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Error fetching employee ID by email:" << query.lastError();
        return -1;
    }

    if (query.next()) {
        return query.value("ID_EMP").toInt();
    } else {
        qDebug() << "No user found with email:" << email;
        return -1;
    }
}



