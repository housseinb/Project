#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QSqlQuery>

class Projet {
public:
    int id;
    QString problem;
    QString target;
    QString proposition;
    QString analyze;
    QString positioning;
    QString idea;
    QString cof;
    QString key;
    QString tools;
    QString marketing;
    QString testing;
    QString expansion;
    QString revenu;
    QString costs;
    QString how;
    QString mvp;
    QString gs;
    QString sp;

public:
    // Constructeurs
    Projet();
    Projet(QString problem, QString target, QString proposition, QString analyze, QString positioning,
           QString idea, QString cof, QString key, QString tools, QString marketing, QString testing,
           QString expansion, QString revenu, QString costs, QString how, QString mvp, QString gs, QString sp);

    // Getters
    QString getProblem() const;
    QString getTarget() const;
    QString getProposition() const;
    QString getAnalyze() const;
    QString getPositioning() const;
    QString getIdea() const;
    QString getCof() const;
    QString getKey() const;
    QString getTools() const;
    QString getMarketing() const;
    QString getTesting() const;
    QString getExpansion() const;
    QString getRevenu() const;
    QString getCosts() const;
    QString getHow() const;
    QString getMvp() const;
    QString getGs() const;
    QString getSp() const;

    // Setters
    void setProblem(QString problem);
    void setTarget(QString target);
    void setProposition(QString proposition);
    void setAnalyze(QString analyze);
    void setPositioning(QString positioning);
    void setIdea(QString idea);
    void setCof(QString cof);
    void setKey(QString key);
    void setTools(QString tools);
    void setMarketing(QString marketing);
    void setTesting(QString testing);
    void setExpansion(QString expansion);
    void setRevenu(QString revenu);
    void setCosts(QString costs);
    void setHow(QString how);
    void setMvp(QString mvp);
    void setGs(QString gs);
    void setSp(QString sp);
    // Méthode pour sauvegarder dans la base de données
    bool sauvegarder();

};

#endif // PROJET_H
