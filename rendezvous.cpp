#include "rendezvous.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDebug>

RendezVous::RendezVous()
{
    id_rdv = 0;
    id_client = 0;
    code_fiscal = 0;
    nom = " ";
    num_tel = 0;
    email = " ";
    date_de_reservation = " ";
    heure_de_reservation = " ";
}

RendezVous::RendezVous(int id_rdv, int id_client, int code_fiscal, QString nom,
                       int num_tel, QString email, QString date_de_reservation,
                       QString heure_de_reservation)
{
    this->id_rdv = id_rdv;
    this->id_client = id_client;
    this->code_fiscal = code_fiscal;
    this->nom = nom;
    this->num_tel = num_tel;
    this->email = email;
    this->date_de_reservation = date_de_reservation;
    this->heure_de_reservation = heure_de_reservation;
}

int RendezVous::getIdRdv() { return id_rdv; }
void RendezVous::setIdRdv(int id) { id_rdv = id; }

int RendezVous::getIdClient() { return id_client; }
void RendezVous::setIdClient(int id) { id_client = id; }

int RendezVous::getCodeFiscal() { return code_fiscal; }
void RendezVous::setCodeFiscal(int code_fiscal) { this->code_fiscal = code_fiscal; }

QString RendezVous::getNom() { return nom; }
void RendezVous::setNom(QString nom) { this->nom = nom; }

int RendezVous::getNumTel() { return num_tel; }
void RendezVous::setNumTel(int num_tel) { this->num_tel = num_tel; }

QString RendezVous::getEmail() { return email; }
void RendezVous::setEmail(QString email) { this->email = email; }

QString RendezVous::getDateDeReservation() { return date_de_reservation; }
void RendezVous::setDateDeReservation(QString date) { date_de_reservation = date; }

QString RendezVous::getHeureDeReservation() { return heure_de_reservation; }
void RendezVous::setHeureDeReservation(QString heure) { heure_de_reservation = heure; }

bool RendezVous::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO rendezvous (id_client, code_fiscal, nom, num_tel, email, date_de_reservation, heure_de_reservation) "
                  "VALUES (:id_client, :code_fiscal, :nom, :num_tel, :email, :date_de_reservation, :heure_de_reservation)");
    query.bindValue(":id_client", id_client);
    query.bindValue(":code_fiscal", code_fiscal);
    query.bindValue(":nom", nom);
    query.bindValue(":num_tel", num_tel);
    query.bindValue(":email", email);
    query.bindValue(":date_de_reservation", date_de_reservation);
    query.bindValue(":heure_de_reservation", heure_de_reservation);
    return query.exec();
}


bool RendezVous::getsonposrlist()
{
    QSqlQuery query;
    query.prepare("INSERT INTO rendezvous (id_client, code_fiscal, nom, num_tel, email, date_de_reservation, heure_de_reservation) "
                  "VALUES (:id_client, :code_fiscal, :nom, :num_tel, :email, :date_de_reservation, :heure_de_reservation)");
    query.bindValue(":id_client", id_client);
    query.bindValue(":code_fiscal", code_fiscal);
    query.bindValue(":nom", nom);
    query.bindValue(":num_tel", num_tel);
    query.bindValue(":email", email);
    query.bindValue(":date_de_reservation", date_de_reservation);
    query.bindValue(":heure_de_reservation", heure_de_reservation);
    return query.exec();
}


bool RendezVous::modifier(int id, int id_client, QString code_fiscal, QString nom,
                          int num_tel, QString email, QString date_de_reservation,
                          QString heure_de_reservation)
{
    QSqlQuery query;
    query.prepare("UPDATE rendezvous SET id_client = :id_client, code_fiscal = :code_fiscal, nom = :nom, "
                  "num_tel = :num_tel, email = :email, date_de_reservation = :date_de_reservation, "
                  "heure_de_reservation = :heure_de_reservation WHERE id_rdv = :id_rdv");
    query.bindValue(":id_client", id_client);
    query.bindValue(":code_fiscal", code_fiscal);
    query.bindValue(":nom", nom);
    query.bindValue(":num_tel", num_tel);
    query.bindValue(":email", email);
    query.bindValue(":date_de_reservation", date_de_reservation);
    query.bindValue(":heure_de_reservation", heure_de_reservation);
    query.bindValue(":id_rdv", id);
    return query.exec();
}

bool RendezVous::supprimer(int id_rdv)
{
    QSqlQuery query;
    query.prepare("DELETE FROM rendezvous WHERE ID_RDV = :id_rdv");
    query.bindValue(":id_rdv", id_rdv);
    return query.exec();
}

QSqlQueryModel* RendezVous::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM rendezvous");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Code Fiscal"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Num Tel"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de Réservation"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Heure de Réservation"));
    return model;
}

QSqlQueryModel* RendezVous::trienom()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM rendezvous ORDER BY NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Code Fiscal"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Num Tel"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de Réservation"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Heure de Réservation"));
    return model;
}

QSqlQueryModel* RendezVous::trieheure()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM rendezvous ORDER BY HEURE_DE_RESERVATION");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Code Fiscal"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Num Tel"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de Réservation"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Heure de Réservation"));
    return model;
}

QSqlQueryModel* RendezVous::triedate()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM rendezvous ORDER BY DATE_DE_RESERVATION");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Code Fiscal"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Num Tel"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de Réservation"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Heure de Réservation"));
    return model;
}
