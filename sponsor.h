#ifndef SPONSOR_H
#define SPONSOR_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Sponsor
{
public:
    Sponsor();
    Sponsor(const QString &code_fiscal, const QString &nom, const QString &email,
            const QString &telephone, const QString &domaine, const QString &adresse,
            int annee_fondation, const QString &type_sponsoring, double capacite_financiere);

    // Getters
    QString getCodeFiscal() const;
    QString getNom() const;
    QString getEmail() const;
    QString getTelephone() const;
    QString getDomaine() const;
    QString getAdresse() const;
    int getAnneeFondation() const;
    QString getTypeSponsoring() const;
    double getCapaciteFinanciere() const;

    // Setters
    void setCodeFiscal(const QString &code_fiscal);
    void setNom(const QString &nom);
    void setEmail(const QString &email);
    void setTelephone(const QString &telephone);
    void setDomaine(const QString &domaine);
    void setAdresse(const QString &adresse);
    void setAnneeFondation(int annee_fondation);
    void setTypeSponsoring(const QString &type_sponsoring);
    void setCapaciteFinanciere(double capacite_financiere);

    // CRUD operations
    bool add() const;
    bool update() const;
    bool remove() const;
    bool load(const QString &code_fiscal);

    // Static methods
    static bool exists(const QString &code_fiscal);
    static bool emailExists(const QString &email);
    static int getTotalCount();
    static int getDomainCount(const QString &domain);

private:
    QString m_codeFiscal;
    QString m_nom;
    QString m_email;
    QString m_telephone;
    QString m_domaine;
    QString m_adresse;
    int m_anneeFondation;
    QString m_typeSponsoring;
    double m_capaciteFinanciere;
};

#endif // SPONSOR_H
