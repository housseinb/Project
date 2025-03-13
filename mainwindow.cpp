#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "projet.h"
#include <QSqlError>
#include <QMessageBox>


// Your other code...


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pm("C:/Users/ASUS-PC/Documents/Nova_Up/WhatsApp Image 2025-02-28 à 13.40.26_c87558a6.jpg");
    ui->img->setPixmap(pm);
    ui->img->setScaledContents(true);
    QPixmap pm2("C:/Users/ASUS-PC/Documents/Nova_Up/WhatsApp Image 2025-02-28 à 13.40.27_145f8b30.jpg");
    ui->img3->setPixmap(pm2);
    ui->img3->setScaledContents(true);
    QPixmap pm3("C:/Users/ASUS-PC/Documents/Nova_Up/WhatsApp Image 2025-02-28 à 13.40.26_c87558a6.jpg");
    ui->img2->setPixmap(pm3);
    ui->img2->setScaledContents(true);
    QPixmap pm4("C:/Users/ASUS-PC/Documents/Nova_Up/WhatsApp Image 2025-02-28 à 13.40.26_c87558a6.jpg");
    ui->img4->setPixmap(pm4);
    ui->img4->setScaledContents(true);

    QVector<Projet> projects;  // Vecteur pour stocker les projets

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM PROJET")) {
        qDebug() << "Erreur de préparation de la requête:" << query.lastError().text();
        return;
    }

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des projets :" << query.lastError().text();
        return;
    }

    while (query.next()) {
        Projet project;

        project.id = query.value("ID_PROJET").toInt();
        project.problem = query.value("PROBLEME_RESOLU").toString();
        project.target = query.value("PUBLIC_CIBLE").toString();
        project.proposition = query.value("PROPOSITION_DE_VALEUR").toString();
        project.analyze = query.value("ANALYSE_DU_MARCHE").toString();
        project.positioning = query.value("CONCURRENCE").toString();
        project.idea = query.value("VALIDATION_IDEE").toString();
        project.cof = query.value("COFONDATEURS").toString();
        project.key = query.value("TALENTS_A_RECRUTER").toString();
        project.tools = query.value("OUTILS_TECHNOLOGIQUES").toString();
        project.marketing = query.value("STRATEGIE_MARKETING").toString();
        project.testing = query.value("TESTS_UTILISATEURS").toString();
        project.expansion = query.value("EXPANSION_MARCHE").toString();
        project.revenu = query.value("SOURCE_REVENUS").toString();
        project.costs = query.value("COUTS").toString();
        project.how = query.value("MODELE_ACHIEVEMENT").toString();
        project.mvp = query.value("MVP").toString();
        project.gs = query.value("STRATEGIE_CROISSANCE").toString();
        project.sp = query.value("PARTENARIATS").toString();

        projects.append(project);
    }

    ui->tabaff->setRowCount(projects.size());
    ui->tabaff->setColumnCount(18);
    ui->tabaff->setHorizontalHeaderLabels({
        "ID", "Problem", "Target", "Proposition", "Analyze", "Positioning", "Idea",
        "Cof", "Key", "Tools", "Marketing", "Testing", "Expansion",
        "Revenu", "Costs", "How", "MVP", "Growth Strategy", "Partnerships"
    });

    for (int row = 0; row < projects.size(); ++row) {
        const Projet &p = projects[row];
        ui->tabaff->setItem(row, 0, new QTableWidgetItem(QString::number(p.id)));
        ui->tabaff->setItem(row, 1, new QTableWidgetItem(p.problem));
        ui->tabaff->setItem(row, 2, new QTableWidgetItem(p.target));
        ui->tabaff->setItem(row, 3, new QTableWidgetItem(p.proposition));
        ui->tabaff->setItem(row, 4, new QTableWidgetItem(p.analyze));
        ui->tabaff->setItem(row, 5, new QTableWidgetItem(p.positioning));
        ui->tabaff->setItem(row, 6, new QTableWidgetItem(p.idea));
        ui->tabaff->setItem(row, 7, new QTableWidgetItem(p.cof));
        ui->tabaff->setItem(row, 8, new QTableWidgetItem(p.key));
        ui->tabaff->setItem(row, 9, new QTableWidgetItem(p.tools));
        ui->tabaff->setItem(row, 10, new QTableWidgetItem(p.marketing));
        ui->tabaff->setItem(row, 11, new QTableWidgetItem(p.testing));
        ui->tabaff->setItem(row, 12, new QTableWidgetItem(p.expansion));
        ui->tabaff->setItem(row, 13, new QTableWidgetItem(p.revenu));
        ui->tabaff->setItem(row, 14, new QTableWidgetItem(p.costs));
        ui->tabaff->setItem(row, 15, new QTableWidgetItem(p.how));
        ui->tabaff->setItem(row, 16, new QTableWidgetItem(p.mvp));
        ui->tabaff->setItem(row, 17, new QTableWidgetItem(p.gs));
        ui->tabaff->setItem(row, 18, new QTableWidgetItem(p.sp));
    }

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_b3_clicked()
{
    QString problem = ui->problem->text();
    QString target = ui->target->text();
    QString proposition = ui->proposition->text();
    QString analyze = ui->analyze->text();
    QString positioning = ui->positioning->text();
    QString idea = ui->idea->text();
    QString cof = ui->cof->text();
    QString key = ui->key->text();
    QString tools = ui->tools->text();
    QString marketing = ui->marketing->text();
    QString testing = ui->testing->text();
    QString expansion = ui->expansion->text();
    QString revenu = ui->revenu->text();
    QString costs = ui->costs->text();
    QString how = ui->how->text();
    QString mvp = ui->MVP->text();
    QString gs = ui->GS->text();
    QString sp = ui->SP->text();

    Projet p(problem, target, proposition, analyze, positioning, idea, cof, key, tools, marketing, testing, expansion, revenu, costs, how, mvp, gs, sp);

    if (p.sauvegarder()) {
        QMessageBox::information(this, "Succès", "Le projet a été ajouter avec succès.");
    } else {
        qDebug() << "Error saving the project!";
    }
    ui->tabWidget->setCurrentIndex(3);
}


void MainWindow::on_b1_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void MainWindow::on_b2_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}


void MainWindow::on_b22_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_16_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void MainWindow::on_b11_clicked()
{
    ui->problem->setText("");
    ui->target->setText("");
    ui->proposition->setText("");
    ui->analyze->setText("");
    ui->positioning->setText("");
    ui->idea->setText("");
    ui->cof->setText("");
    ui->key->setText("");
    ui->tools->setText("");
    ui->marketing->setText("");
    ui->testing->setText("");
    ui->expansion->setText("");
    ui->revenu->setText("");
    ui->costs->setText("");
    ui->how->setText("");
    ui->MVP->setText("");
    ui->GS->setText("");
    ui->SP->setText("");
}


void MainWindow::on_b2_3_clicked()
{
    QString id = ui->id->text(); // Récupération de l'ID depuis l'interface

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM PROJET WHERE ID_PROJET = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de la récupération du projet : " + query.lastError().text());
        return;
    }

    if (query.next()) {
        ui->problem_3->setText(query.value("PROBLEME_RESOLU").toString());
        ui->target_3->setText(query.value("PUBLIC_CIBLE").toString());
        ui->proposition_3->setText(query.value("PROPOSITION_DE_VALEUR").toString());
        ui->analyze_3->setText(query.value("ANALYSE_DU_MARCHE").toString());
        ui->positioning_3->setText(query.value("CONCURRENCE").toString());
        ui->idea_3->setText(query.value("VALIDATION_IDEE").toString());
        ui->cof_3->setText(query.value("COFONDATEURS").toString());
        ui->key_3->setText(query.value("TALENTS_A_RECRUTER").toString());
        ui->tools_3->setText(query.value("OUTILS_TECHNOLOGIQUES").toString());
        ui->marketing_3->setText(query.value("STRATEGIE_MARKETING").toString());
        ui->testing_3->setText(query.value("TESTS_UTILISATEURS").toString());
        ui->expansion_3->setText(query.value("EXPANSION_MARCHE").toString());
        ui->revenu_3->setText(query.value("SOURCE_REVENUS").toString());
        ui->costs_3->setText(query.value("COUTS").toString());
        ui->how_3->setText(query.value("MODELE_ACHIEVEMENT").toString());
        ui->MVP_3->setText(query.value("MVP").toString());
        ui->GS_3->setText(query.value("STRATEGIE_CROISSANCE").toString());
        ui->SP_3->setText(query.value("PARTENARIATS").toString());
    } else {
        QMessageBox::information(this, "Aucun résultat", "Aucun projet trouvé avec cet ID.");
    }
    ui->tabWidget->setCurrentIndex(4);
}



void MainWindow::on_b1_3_clicked()
{
    ui->tabWidget->setCurrentIndex(5);
}


void MainWindow::on_b2_5_clicked()
{
    ui->tabWidget->setCurrentIndex(6);
}


void MainWindow::on_pushButton_18_clicked()
{
    ui->tabWidget->setCurrentIndex(5);
}


void MainWindow::on_b22_3_clicked()
{
    ui->tabWidget->setCurrentIndex(4);
}


void MainWindow::on_b11_3_clicked()
{
    ui->problem_3->setText("");
    ui->target_3->setText("");
    ui->proposition_3->setText("");
    ui->analyze_3->setText("");
    ui->positioning_3->setText("");
    ui->idea_3->setText("");
    ui->cof_3->setText("");
    ui->key_3->setText("");
    ui->tools_3->setText("");
    ui->marketing_3->setText("");
    ui->testing_3->setText("");
    ui->expansion_3->setText("");
    ui->revenu_3->setText("");
    ui->costs_3->setText("");
    ui->how_3->setText("");
    ui->MVP_3->setText("");
    ui->GS_3->setText("");
    ui->SP_3->setText("");
}


void MainWindow::on_b3_3_clicked()
{
    QString id = ui->id->text();

    QString problem = ui->problem_3->text();
    QString target = ui->target_3->text();
    QString proposition = ui->proposition_3->text();
    QString analyze = ui->analyze_3->text();
    QString positioning = ui->positioning_3->text();
    QString idea = ui->idea_3->text();
    QString cof = ui->cof_3->text();
    QString key = ui->key_3->text();
    QString tools = ui->tools_3->text();
    QString marketing = ui->marketing_3->text();
    QString testing = ui->testing_3->text();
    QString expansion = ui->expansion_3->text();
    QString revenu = ui->revenu_3->text();
    QString costs = ui->costs_3->text();
    QString how = ui->how_3->text();
    QString mvp = ui->MVP_3->text();
    QString gs = ui->GS_3->text();
    QString sp = ui->SP_3->text();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE PROJET SET "
                  "PROBLEME_RESOLU = :problem, "
                  "PUBLIC_CIBLE = :target, "
                  "PROPOSITION_DE_VALEUR = :proposition, "
                  "ANALYSE_DU_MARCHE = :analyze, "
                  "CONCURRENCE = :positioning, "
                  "VALIDATION_IDEE = :idea, "
                  "COFONDATEURS = :cof, "
                  "TALENTS_A_RECRUTER = :key, "
                  "OUTILS_TECHNOLOGIQUES = :tools, "
                  "STRATEGIE_MARKETING = :marketing, "
                  "TESTS_UTILISATEURS = :testing, "
                  "EXPANSION_MARCHE = :expansion, "
                  "SOURCE_REVENUS = :revenu, "
                  "COUTS = :costs, "
                  "MODELE_ACHIEVEMENT = :how, "
                  "MVP = :mvp, "
                  "STRATEGIE_CROISSANCE = :gs, "
                  "PARTENARIATS = :sp "
                  "WHERE ID_PROJET = :id");

    query.bindValue(":id", id);
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

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de la mise à jour du projet : " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Succès", "Le projet a été mis à jour avec succès.");

    QVector<Projet> projects;

    if (!query.prepare("SELECT * FROM PROJET")) {
        qDebug() << "Erreur de préparation de la requête:" << query.lastError().text();
        return;
    }

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des projets :" << query.lastError().text();
        return;
    }

    while (query.next()) {
        Projet project;

        project.id = query.value("ID_PROJET").toInt();
        project.problem = query.value("PROBLEME_RESOLU").toString();
        project.target = query.value("PUBLIC_CIBLE").toString();
        project.proposition = query.value("PROPOSITION_DE_VALEUR").toString();
        project.analyze = query.value("ANALYSE_DU_MARCHE").toString();
        project.positioning = query.value("CONCURRENCE").toString();
        project.idea = query.value("VALIDATION_IDEE").toString();
        project.cof = query.value("COFONDATEURS").toString();
        project.key = query.value("TALENTS_A_RECRUTER").toString();
        project.tools = query.value("OUTILS_TECHNOLOGIQUES").toString();
        project.marketing = query.value("STRATEGIE_MARKETING").toString();
        project.testing = query.value("TESTS_UTILISATEURS").toString();
        project.expansion = query.value("EXPANSION_MARCHE").toString();
        project.revenu = query.value("SOURCE_REVENUS").toString();
        project.costs = query.value("COUTS").toString();
        project.how = query.value("MODELE_ACHIEVEMENT").toString();
        project.mvp = query.value("MVP").toString();
        project.gs = query.value("STRATEGIE_CROISSANCE").toString();
        project.sp = query.value("PARTENARIATS").toString();

        projects.append(project);
    }

    ui->tabaff->setRowCount(projects.size()); // Nombre de lignes
    ui->tabaff->setColumnCount(18); // Ajusté au nombre de colonnes
    ui->tabaff->setHorizontalHeaderLabels({
        "ID", "Problem", "Target", "Proposition", "Analyze", "Positioning", "Idea",
        "Cof", "Key", "Tools", "Marketing", "Testing", "Expansion",
        "Revenu", "Costs", "How", "MVP", "Growth Strategy", "Partnerships"
    });


    for (int row = 0; row < projects.size(); ++row) {
        const Projet &p = projects[row];
        ui->tabaff->setItem(row, 0, new QTableWidgetItem(QString::number(p.id)));
        ui->tabaff->setItem(row, 1, new QTableWidgetItem(p.problem));
        ui->tabaff->setItem(row, 2, new QTableWidgetItem(p.target));
        ui->tabaff->setItem(row, 3, new QTableWidgetItem(p.proposition));
        ui->tabaff->setItem(row, 4, new QTableWidgetItem(p.analyze));
        ui->tabaff->setItem(row, 5, new QTableWidgetItem(p.positioning));
        ui->tabaff->setItem(row, 6, new QTableWidgetItem(p.idea));
        ui->tabaff->setItem(row, 7, new QTableWidgetItem(p.cof));
        ui->tabaff->setItem(row, 8, new QTableWidgetItem(p.key));
        ui->tabaff->setItem(row, 9, new QTableWidgetItem(p.tools));
        ui->tabaff->setItem(row, 10, new QTableWidgetItem(p.marketing));
        ui->tabaff->setItem(row, 11, new QTableWidgetItem(p.testing));
        ui->tabaff->setItem(row, 12, new QTableWidgetItem(p.expansion));
        ui->tabaff->setItem(row, 13, new QTableWidgetItem(p.revenu));
        ui->tabaff->setItem(row, 14, new QTableWidgetItem(p.costs));
        ui->tabaff->setItem(row, 15, new QTableWidgetItem(p.how));
        ui->tabaff->setItem(row, 16, new QTableWidgetItem(p.mvp));
        ui->tabaff->setItem(row, 17, new QTableWidgetItem(p.gs));
        ui->tabaff->setItem(row, 18, new QTableWidgetItem(p.sp));
    }
    ui->tabWidget->setCurrentIndex(3);
}


void MainWindow::on_b2_4_clicked()
{
    QString id = ui->id_2->text(); // Retrieve the ID from the UI

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM PROJET WHERE ID_PROJET = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du projet : " + query.lastError().text());
        return;
    }


    QMessageBox::information(this, "Succès", "Le projet a été supprimé avec succès.");

    QVector<Projet> projects;

    if (!query.prepare("SELECT * FROM PROJET")) {
        qDebug() << "Erreur de préparation de la requête:" << query.lastError().text();
        return;
    }

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des projets :" << query.lastError().text();
        return;
    }


    while (query.next()) {
        Projet project;

        project.id = query.value("ID_PROJET").toInt();
        project.problem = query.value("PROBLEME_RESOLU").toString();
        project.target = query.value("PUBLIC_CIBLE").toString();
        project.proposition = query.value("PROPOSITION_DE_VALEUR").toString();
        project.analyze = query.value("ANALYSE_DU_MARCHE").toString();
        project.positioning = query.value("CONCURRENCE").toString();
        project.idea = query.value("VALIDATION_IDEE").toString();
        project.cof = query.value("COFONDATEURS").toString();
        project.key = query.value("TALENTS_A_RECRUTER").toString();
        project.tools = query.value("OUTILS_TECHNOLOGIQUES").toString();
        project.marketing = query.value("STRATEGIE_MARKETING").toString();
        project.testing = query.value("TESTS_UTILISATEURS").toString();
        project.expansion = query.value("EXPANSION_MARCHE").toString();
        project.revenu = query.value("SOURCE_REVENUS").toString();
        project.costs = query.value("COUTS").toString();
        project.how = query.value("MODELE_ACHIEVEMENT").toString();
        project.mvp = query.value("MVP").toString();
        project.gs = query.value("STRATEGIE_CROISSANCE").toString();
        project.sp = query.value("PARTENARIATS").toString();

        projects.append(project);
    }

    // Configuration du tableau d'affichage
    ui->tabaff->setRowCount(projects.size()); // Nombre de lignes
    ui->tabaff->setColumnCount(18); // Ajusté au nombre de colonnes
    ui->tabaff->setHorizontalHeaderLabels({
        "ID", "Problem", "Target", "Proposition", "Analyze", "Positioning", "Idea",
        "Cof", "Key", "Tools", "Marketing", "Testing", "Expansion",
        "Revenu", "Costs", "How", "MVP", "Growth Strategy", "Partnerships"
    });

    for (int row = 0; row < projects.size(); ++row) {
        const Projet &p = projects[row];
        ui->tabaff->setItem(row, 0, new QTableWidgetItem(QString::number(p.id)));
        ui->tabaff->setItem(row, 1, new QTableWidgetItem(p.problem));
        ui->tabaff->setItem(row, 2, new QTableWidgetItem(p.target));
        ui->tabaff->setItem(row, 3, new QTableWidgetItem(p.proposition));
        ui->tabaff->setItem(row, 4, new QTableWidgetItem(p.analyze));
        ui->tabaff->setItem(row, 5, new QTableWidgetItem(p.positioning));
        ui->tabaff->setItem(row, 6, new QTableWidgetItem(p.idea));
        ui->tabaff->setItem(row, 7, new QTableWidgetItem(p.cof));
        ui->tabaff->setItem(row, 8, new QTableWidgetItem(p.key));
        ui->tabaff->setItem(row, 9, new QTableWidgetItem(p.tools));
        ui->tabaff->setItem(row, 10, new QTableWidgetItem(p.marketing));
        ui->tabaff->setItem(row, 11, new QTableWidgetItem(p.testing));
        ui->tabaff->setItem(row, 12, new QTableWidgetItem(p.expansion));
        ui->tabaff->setItem(row, 13, new QTableWidgetItem(p.revenu));
        ui->tabaff->setItem(row, 14, new QTableWidgetItem(p.costs));
        ui->tabaff->setItem(row, 15, new QTableWidgetItem(p.how));
        ui->tabaff->setItem(row, 16, new QTableWidgetItem(p.mvp));
        ui->tabaff->setItem(row, 17, new QTableWidgetItem(p.gs));
        ui->tabaff->setItem(row, 18, new QTableWidgetItem(p.sp));
    }
}

