#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Employee
{
public:
    Employee();
    Employee(const QString &nom, const QString &email, const QString &poste, const QString &pwd);

    QString getNom() const;
    QString getEmail() const;
    QString getPoste() const;
    QString getMotDePasse() const;

    void setNom(const QString &nom);
    void setEmail(const QString &email);
    void setPoste(const QString &poste);
    void setMotDePasse(const QString &pwd);
    bool enregistre_employe_db();
    bool connection_employe_db(QString email , QString pwd);
    int id_user_connected();


private:
    QString nom;
    QString email;
    QString poste;
    QString pwd;
};

#endif // EMPLOYEE_H
