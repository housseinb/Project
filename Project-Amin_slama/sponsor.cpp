#include "sponsor.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Sponsor::Sponsor() :
    m_anneeFondation(0),
    m_capaciteFinanciere(0.0)
{
}

Sponsor::Sponsor(const QString &code_fiscal, const QString &nom, const QString &email,
                 const QString &telephone, const QString &domaine, const QString &adresse,
                 int annee_fondation, const QString &type_sponsoring, double capacite_financiere) :
    m_codeFiscal(code_fiscal),
    m_nom(nom),
    m_email(email),
    m_telephone(telephone),
    m_domaine(domaine),
    m_adresse(adresse),
    m_anneeFondation(annee_fondation),
    m_typeSponsoring(type_sponsoring),
    m_capaciteFinanciere(capacite_financiere)
{
}

// Getters
QString Sponsor::getCodeFiscal() const { return m_codeFiscal; }
QString Sponsor::getNom() const { return m_nom; }
QString Sponsor::getEmail() const { return m_email; }
QString Sponsor::getTelephone() const { return m_telephone; }
QString Sponsor::getDomaine() const { return m_domaine; }
QString Sponsor::getAdresse() const { return m_adresse; }
int Sponsor::getAnneeFondation() const { return m_anneeFondation; }
QString Sponsor::getTypeSponsoring() const { return m_typeSponsoring; }
double Sponsor::getCapaciteFinanciere() const { return m_capaciteFinanciere; }

// Setters
void Sponsor::setCodeFiscal(const QString &code_fiscal) { m_codeFiscal = code_fiscal; }
void Sponsor::setNom(const QString &nom) { m_nom = nom; }
void Sponsor::setEmail(const QString &email) { m_email = email; }
void Sponsor::setTelephone(const QString &telephone) { m_telephone = telephone; }
void Sponsor::setDomaine(const QString &domaine) { m_domaine = domaine; }
void Sponsor::setAdresse(const QString &adresse) { m_adresse = adresse; }
void Sponsor::setAnneeFondation(int annee_fondation) { m_anneeFondation = annee_fondation; }
void Sponsor::setTypeSponsoring(const QString &type_sponsoring) { m_typeSponsoring = type_sponsoring; }
void Sponsor::setCapaciteFinanciere(double capacite_financiere) { m_capaciteFinanciere = capacite_financiere; }

// CRUD operations
bool Sponsor::add() const {
    QSqlQuery query;
    query.prepare("INSERT INTO SPONSOR (CODE_FISCAL, NOM, EMAIL, TELEPHONE, DOMAINE, ADRESSE, ANNEE_FONDATION, TYPE_DE_SPONSORING, CAPACITE_FINANCIERE) "
                  "VALUES (:code_fiscal, :nom, :email, :telephone, :domaine, :adresse, :annee_fondation, :type_sponsoring, :capacite_financiere)");

    query.bindValue(":code_fiscal", m_codeFiscal);
    query.bindValue(":nom", m_nom);
    query.bindValue(":email", m_email);
    query.bindValue(":telephone", m_telephone);
    query.bindValue(":domaine", m_domaine);
    query.bindValue(":adresse", m_adresse);
    query.bindValue(":annee_fondation", m_anneeFondation);
    query.bindValue(":type_sponsoring", m_typeSponsoring);
    query.bindValue(":capacite_financiere", m_capaciteFinanciere);

    if (!query.exec()) {
        qDebug() << "SQL Error in add(): " << query.lastError().text();
        return false;
    }
    return true;
}

bool Sponsor::update() const {
    if (m_codeFiscal.isEmpty()) {
        qDebug() << "Code fiscal is empty. Update aborted.";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE SPONSOR SET "
                  "NOM = :nom, "
                  "EMAIL = :email, "
                  "TELEPHONE = :telephone, "
                  "DOMAINE = :domaine, "
                  "ADRESSE = :adresse, "
                  "ANNEE_FONDATION = :annee_fondation, "
                  "TYPE_DE_SPONSORING = :type_sponsoring, "
                  "CAPACITE_FINANCIERE = :capacite_financiere "
                  "WHERE CODE_FISCAL = :code_fiscal");

    query.bindValue(":code_fiscal", m_codeFiscal);
    query.bindValue(":nom", m_nom);
    query.bindValue(":email", m_email);
    query.bindValue(":telephone", m_telephone);
    query.bindValue(":domaine", m_domaine);
    query.bindValue(":adresse", m_adresse);
    query.bindValue(":annee_fondation", m_anneeFondation);
    query.bindValue(":type_sponsoring", m_typeSponsoring);
    query.bindValue(":capacite_financiere", m_capaciteFinanciere);

    if (!query.exec()) {
        qDebug() << "SQL Error in update(): " << query.lastError().text();
        return false;
    }
    return true;
}

bool Sponsor::remove() const {
    if (m_codeFiscal.isEmpty()) {
        qDebug() << "Code fiscal is empty. Removal aborted.";
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM SPONSOR WHERE CODE_FISCAL = :code_fiscal");
    query.bindValue(":code_fiscal", m_codeFiscal);

    if (!query.exec()) {
        qDebug() << "SQL Error in remove(): " << query.lastError().text();
        return false;
    }
    return true;
}

bool Sponsor::load(const QString &code_fiscal) {
    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSOR WHERE CODE_FISCAL = :code_fiscal");
    query.bindValue(":code_fiscal", code_fiscal);

    if (!query.exec()) {
        qDebug() << "SQL Error in load(): " << query.lastError().text();
        return false;
    }

    if (!query.next()) {
        return false;
    }

    m_codeFiscal = query.value("CODE_FISCAL").toString();
    m_nom = query.value("NOM").toString();
    m_email = query.value("EMAIL").toString();
    m_telephone = query.value("TELEPHONE").toString();
    m_domaine = query.value("DOMAINE").toString();
    m_adresse = query.value("ADRESSE").toString();
    m_anneeFondation = query.value("ANNEE_FONDATION").toInt();
    m_typeSponsoring = query.value("TYPE_DE_SPONSORING").toString();
    m_capaciteFinanciere = query.value("CAPACITE_FINANCIERE").toDouble();

    return true;
}

// Static methods
bool Sponsor::exists(const QString &code_fiscal) {
    QSqlQuery query;
    query.prepare("SELECT 1 FROM SPONSOR WHERE CODE_FISCAL = :code_fiscal LIMIT 1");
    query.bindValue(":code_fiscal", code_fiscal);

    if (query.exec() && query.next()) {
        return true;
    }

    qDebug() << "SQL Error in exists(): " << query.lastError().text();
    return false;
}

bool Sponsor::emailExists(const QString &email) {
    QSqlQuery query;
    query.prepare("SELECT 1 FROM SPONSOR WHERE EMAIL = :email LIMIT 1");
    query.bindValue(":email", email);

    if (query.exec() && query.next()) {
        return true;
    }

    qDebug() << "SQL Error in emailExists(): " << query.lastError().text();
    return false;
}

int Sponsor::getTotalCount() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SPONSOR");

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    qDebug() << "SQL Error in getTotalCount(): " << query.lastError().text();
    return 0;
}

int Sponsor::getDomainCount(const QString &domain) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SPONSOR WHERE DOMAINE = :domain");
    query.bindValue(":domain", domain);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    qDebug() << "SQL Error in getDomainCount(): " << query.lastError().text();
    return 0;
}
