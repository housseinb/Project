#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QDebug>

class RendezVous
{
public:
    // Constructors
    RendezVous();
    RendezVous(int id_rdv, int id_client, int code_fiscal, QString nom,
               int num_tel, QString email, QString date_de_reservation,
               QString heure_de_reservation);

    // Getters and Setters
    int getIdRdv();
    void setIdRdv(int id);

    int getIdClient();
    void setIdClient(int id);

    int getCodeFiscal();
    void setCodeFiscal(int code_fiscal);

    QString getNom();
    void setNom(QString nom);

    int getNumTel();
    void setNumTel(int num_tel);

    QString getEmail();
    void setEmail(QString email);

    QString getDateDeReservation();
    void setDateDeReservation(QString date);

    QString getHeureDeReservation();
    void setHeureDeReservation(QString heure);

    // CRUD operations
    bool ajouter();
    bool modifier(int id, int id_client, QString code_fiscal, QString nom,
                  int num_tel, QString email, QString date_de_reservation,
                  QString heure_de_reservation);
    bool supprimer(int id_rdv);
    QSqlQueryModel* afficher();
    QSqlQueryModel* trienom();
    QSqlQueryModel* triedate();
    QSqlQueryModel* trieheure();
    bool getsonposrlist();

private:
    int id_rdv;
    int id_client;
    int code_fiscal;
    QString nom;
    int num_tel;
    QString email;
    QString date_de_reservation;
    QString heure_de_reservation;
};

#endif // RENDEZVOUS_H
