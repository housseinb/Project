#include "projet.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

Projet::Projet()
    : problem(""), target(""), proposition(""), analyze(""), positioning(""),
    idea(""), cof(""), key(""), tools(""), marketing(""), testing(""),
    expansion(""), revenu(""), costs(""), how(""), mvp(""), gs(""), sp("") {}

Projet::Projet(QString problem, QString target, QString proposition, QString analyze, QString positioning,
               QString idea, QString cof, QString key, QString tools, QString marketing, QString testing,
               QString expansion, QString revenu, QString costs, QString how, QString mvp, QString gs, QString sp)
    : problem(problem), target(target), proposition(proposition), analyze(analyze), positioning(positioning),
    idea(idea), cof(cof), key(key), tools(tools), marketing(marketing), testing(testing),
    expansion(expansion), revenu(revenu), costs(costs), how(how), mvp(mvp), gs(gs), sp(sp) {}


// Getters
QString Projet::getProblem() const { return problem; }
QString Projet::getTarget() const { return target; }
QString Projet::getProposition() const { return proposition; }
QString Projet::getAnalyze() const { return analyze; }
QString Projet::getPositioning() const { return positioning; }
QString Projet::getIdea() const { return idea; }
QString Projet::getCof() const { return cof; }
QString Projet::getKey() const { return key; }
QString Projet::getTools() const { return tools; }
QString Projet::getMarketing() const { return marketing; }
QString Projet::getTesting() const { return testing; }
QString Projet::getExpansion() const { return expansion; }
QString Projet::getRevenu() const { return revenu; }
QString Projet::getCosts() const { return costs; }
QString Projet::getHow() const { return how; }
QString Projet::getMvp() const { return mvp; }
QString Projet::getGs() const { return gs; }
QString Projet::getSp() const { return sp; }

// Setters
void Projet::setProblem(QString problem) { this->problem = problem; }
void Projet::setTarget(QString target) { this->target = target; }
void Projet::setProposition(QString proposition) { this->proposition = proposition; }
void Projet::setAnalyze(QString analyze) { this->analyze = analyze; }
void Projet::setPositioning(QString positioning) { this->positioning = positioning; }
void Projet::setIdea(QString idea) { this->idea = idea; }
void Projet::setCof(QString cof) { this->cof = cof; }
void Projet::setKey(QString key) { this->key = key; }
void Projet::setTools(QString tools) { this->tools = tools; }
void Projet::setMarketing(QString marketing) { this->marketing = marketing; }
void Projet::setTesting(QString testing) { this->testing = testing; }
void Projet::setExpansion(QString expansion) { this->expansion = expansion; }
void Projet::setRevenu(QString revenu) { this->revenu = revenu; }
void Projet::setCosts(QString costs) { this->costs = costs; }
void Projet::setHow(QString how) { this->how = how; }
void Projet::setMvp(QString mvp) { this->mvp = mvp; }
void Projet::setGs(QString gs) { this->gs = gs; }
void Projet::setSp(QString sp) { this->sp = sp; }


bool Projet::sauvegarder() {
    QSqlQuery query;

    int clientId = 128;  // Example client ID - replace with dynamically fetched value

    query.prepare("INSERT INTO Projet (ID_PROJET, ID_CLIENT, PROBLEME_RESOLU, PUBLIC_CIBLE, PROPOSITION_DE_VALEUR, "
                  "ANALYSE_DU_MARCHE, CONCURRENCE, VALIDATION_IDEE, COFONDATEURS, TALENTS_A_RECRUTER, "
                  "OUTILS_TECHNOLOGIQUES, STRATEGIE_MARKETING, TESTS_UTILISATEURS, EXPANSION_MARCHE, "
                  "SOURCE_REVENUS, COUTS, MODELE_ACHIEVEMENT, MVP, STRATEGIE_CROISSANCE, PARTENARIATS) "
                  "VALUES (PROJET_SEQ.NEXTVAL, :clientId, :problem, :target, :proposition, :analyze, :positioning, "
                  ":idea, :cof, :key, :tools, :marketing, :testing, :expansion, :revenu, :costs, :how, :mvp, :gs, :sp)");

    query.bindValue(":clientId", clientId);  // Bind the dynamic client ID here
    query.bindValue(":problem", problem);
    query.bindValue(":target", target);
    query.bindValue(":proposition", proposition);
    query.bindValue(":analyze", analyze);
    query.bindValue(":positioning", positioning);
    query.bindValue(":idea", idea);
    query.bindValue(":cof", cof);
    query.bindValue(":key", key);
    query.bindValue(":tools", tools);
    query.bindValue(":marketing", marketing);
    query.bindValue(":testing", testing);
    query.bindValue(":expansion", expansion);
    query.bindValue(":revenu", revenu);
    query.bindValue(":costs", costs);
    query.bindValue(":how", how);
    query.bindValue(":mvp", mvp);
    query.bindValue(":gs", gs);
    query.bindValue(":sp", sp);

    // Handling CLOB fields: Ensure to use a QString or QSqlQuery::bindValue appropriately
    query.bindValue(":problem", problem);
    query.bindValue(":target", target);
    query.bindValue(":proposition", proposition);
    query.bindValue(":analyze", analyze);
    query.bindValue(":positioning", positioning);
    query.bindValue(":idea", idea);
    query.bindValue(":cof", cof);
    query.bindValue(":key", key);
    query.bindValue(":tools", tools);
    query.bindValue(":marketing", marketing);
    query.bindValue(":testing", testing);
    query.bindValue(":expansion", expansion);
    query.bindValue(":revenu", revenu);
    query.bindValue(":costs", costs);
    query.bindValue(":how", how);
    query.bindValue(":mvp", mvp);
    query.bindValue(":gs", gs);
    query.bindValue(":sp", sp);

    // Executing the query and checking for errors
    if (!query.exec()) {
        qDebug() << "Error saving project:" << query.lastError().text();
        return false;
    }

    return true;
}
