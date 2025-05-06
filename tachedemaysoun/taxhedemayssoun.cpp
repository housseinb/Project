#include "taxhedemayssoun.h"
#include "ui_taxhedemayssoun.h"
#include "projet.h"
#include "barchartitem.h"
#include <QSqlError>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDateTime>
#include <QPrinter>
#include <QTextDocument>
#include <QProcess>
#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>

taxhedemayssoun::taxhedemayssoun(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::taxhedemayssoun)
{
    ui->setupUi(this);
    loadProjects();
}

taxhedemayssoun::~taxhedemayssoun()
{
    delete ui;
}

void taxhedemayssoun::loadProjects()
{
    QVector<Projet> projects;  // Vector to store projects

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM PROJET")) {
        qDebug() << "Query preparation error:" << query.lastError().text();
        return;
    }

    if (!query.exec()) {
        qDebug() << "Error retrieving projects:" << query.lastError().text();
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

    ui->tabaff_2->setRowCount(projects.size());
    ui->tabaff_2->setColumnCount(18);
    ui->tabaff_2->setHorizontalHeaderLabels({
        "ID", "Problem", "Target", "Proposition", "Analyze", "Positioning", "Idea",
        "Cof", "Key", "Tools", "Marketing", "Testing", "Expansion",
        "Revenu", "Costs", "How", "MVP", "Growth Strategy", "Partnerships"
    });

    for (int row = 0; row < projects.size(); ++row) {
        const Projet &p = projects[row];
        ui->tabaff_2->setItem(row, 0, new QTableWidgetItem(QString::number(p.id)));
        ui->tabaff_2->setItem(row, 1, new QTableWidgetItem(p.problem));
        ui->tabaff_2->setItem(row, 2, new QTableWidgetItem(p.target));
        ui->tabaff_2->setItem(row, 3, new QTableWidgetItem(p.proposition));
        ui->tabaff_2->setItem(row, 4, new QTableWidgetItem(p.analyze));
        ui->tabaff_2->setItem(row, 5, new QTableWidgetItem(p.positioning));
        ui->tabaff_2->setItem(row, 6, new QTableWidgetItem(p.idea));
        ui->tabaff_2->setItem(row, 7, new QTableWidgetItem(p.cof));
        ui->tabaff_2->setItem(row, 8, new QTableWidgetItem(p.key));
        ui->tabaff_2->setItem(row, 9, new QTableWidgetItem(p.tools));
        ui->tabaff_2->setItem(row, 10, new QTableWidgetItem(p.marketing));
        ui->tabaff_2->setItem(row, 11, new QTableWidgetItem(p.testing));
        ui->tabaff_2->setItem(row, 12, new QTableWidgetItem(p.expansion));
        ui->tabaff_2->setItem(row, 13, new QTableWidgetItem(p.revenu));
        ui->tabaff_2->setItem(row, 14, new QTableWidgetItem(p.costs));
        ui->tabaff_2->setItem(row, 15, new QTableWidgetItem(p.how));
        ui->tabaff_2->setItem(row, 16, new QTableWidgetItem(p.mvp));
        ui->tabaff_2->setItem(row, 17, new QTableWidgetItem(p.gs));
        ui->tabaff_2->setItem(row, 18, new QTableWidgetItem(p.sp));
    }
}




void taxhedemayssoun::on_b3_2_clicked()
{
    QString problem = ui->problem_2->text();
    QString target = ui->target_2->text();
    QString proposition = ui->proposition_2->text();
    QString analyze = ui->analyze_2->text();
    QString positioning = ui->positioning_2->text();
    QString idea = ui->idea_2->text();
    QString cof = ui->cof_2->text();
    QString key = ui->key_2->text();
    QString tools = ui->tools_2->text();
    QString marketing = ui->marketing_2->text();
    QString testing = ui->testing_2->text();
    QString expansion = ui->expansion_2->text();
    QString revenu = ui->revenu_2->text();
    QString costs = ui->costs_2->text();
    QString how = ui->how_2->text();
    QString mvp = ui->MVP_2->text();
    QString gs = ui->GS_2->text();
    QString sp = ui->SP_2->text();

    Projet p(problem, target, proposition, analyze, positioning, idea, cof, key, tools, marketing, testing, expansion, revenu, costs, how, mvp, gs, sp);

    if (p.sauvegarder()) {
        QMessageBox::information(this, "Succès", "Le projet a été ajouter avec succès.");
    } else {
        qDebug() << "Error saving the project!";
    }



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

    ui->tabaff_2->setRowCount(projects.size());
    ui->tabaff_2->setColumnCount(18);
    ui->tabaff_2->setHorizontalHeaderLabels({
        "ID", "Problem", "Target", "Proposition", "Analyze", "Positioning", "Idea",
        "Cof", "Key", "Tools", "Marketing", "Testing", "Expansion",
        "Revenu", "Costs", "How", "MVP", "Growth Strategy", "Partnerships"
    });

    for (int row = 0; row < projects.size(); ++row) {
        const Projet &p = projects[row];
        ui->tabaff_2->setItem(row, 0, new QTableWidgetItem(QString::number(p.id)));
        ui->tabaff_2->setItem(row, 1, new QTableWidgetItem(p.problem));
        ui->tabaff_2->setItem(row, 2, new QTableWidgetItem(p.target));
        ui->tabaff_2->setItem(row, 3, new QTableWidgetItem(p.proposition));
        ui->tabaff_2->setItem(row, 4, new QTableWidgetItem(p.analyze));
        ui->tabaff_2->setItem(row, 5, new QTableWidgetItem(p.positioning));
        ui->tabaff_2->setItem(row, 6, new QTableWidgetItem(p.idea));
        ui->tabaff_2->setItem(row, 7, new QTableWidgetItem(p.cof));
        ui->tabaff_2->setItem(row, 8, new QTableWidgetItem(p.key));
        ui->tabaff_2->setItem(row, 9, new QTableWidgetItem(p.tools));
        ui->tabaff_2->setItem(row, 10, new QTableWidgetItem(p.marketing));
        ui->tabaff_2->setItem(row, 11, new QTableWidgetItem(p.testing));
        ui->tabaff_2->setItem(row, 12, new QTableWidgetItem(p.expansion));
        ui->tabaff_2->setItem(row, 13, new QTableWidgetItem(p.revenu));
        ui->tabaff_2->setItem(row, 14, new QTableWidgetItem(p.costs));
        ui->tabaff_2->setItem(row, 15, new QTableWidgetItem(p.how));
        ui->tabaff_2->setItem(row, 16, new QTableWidgetItem(p.mvp));
        ui->tabaff_2->setItem(row, 17, new QTableWidgetItem(p.gs));
        ui->tabaff_2->setItem(row, 18, new QTableWidgetItem(p.sp));
    }

    ui->tabWidget->setCurrentIndex(3);
}


void taxhedemayssoun::on_b1_2_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void taxhedemayssoun::on_b2_2_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}


void taxhedemayssoun::on_b22_2_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}


void taxhedemayssoun::on_b11_2_clicked()
{
    ui->problem_2->setText("");
    ui->target_2->setText("");
    ui->proposition_2->setText("");
    ui->analyze_2->setText("");
    ui->positioning_2->setText("");
    ui->idea_2->setText("");
    ui->cof_2->setText("");
    ui->key_2->setText("");
    ui->tools_2->setText("");
    ui->marketing_2->setText("");
    ui->testing_2->setText("");
    ui->expansion_2->setText("");
    ui->revenu_2->setText("");
    ui->costs_2->setText("");
    ui->how_2->setText("");
    ui->MVP_2->setText("");
    ui->GS_2->setText("");
    ui->SP_2->setText("");
}


void taxhedemayssoun::on_pushButton_17_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void taxhedemayssoun::on_b2_6_clicked()
{
    QString id = ui->id_3->text(); // Récupération de l'ID depuis l'interface

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
        ui->problem_4->setText(query.value("PROBLEME_RESOLU").toString());
        ui->target_4->setText(query.value("PUBLIC_CIBLE").toString());
        ui->proposition_4->setText(query.value("PROPOSITION_DE_VALEUR").toString());
        ui->analyze_4->setText(query.value("ANALYSE_DU_MARCHE").toString());
        ui->positioning_4->setText(query.value("CONCURRENCE").toString());
        ui->idea_4->setText(query.value("VALIDATION_IDEE").toString());
        ui->cof_4->setText(query.value("COFONDATEURS").toString());
        ui->key_4->setText(query.value("TALENTS_A_RECRUTER").toString());
        ui->tools_4->setText(query.value("OUTILS_TECHNOLOGIQUES").toString());
        ui->marketing_4->setText(query.value("STRATEGIE_MARKETING").toString());
        ui->testing_4->setText(query.value("TESTS_UTILISATEURS").toString());
        ui->expansion_4->setText(query.value("EXPANSION_MARCHE").toString());
        ui->revenu_4->setText(query.value("SOURCE_REVENUS").toString());
        ui->costs_4->setText(query.value("COUTS").toString());
        ui->how_4->setText(query.value("MODELE_ACHIEVEMENT").toString());
        ui->MVP_4->setText(query.value("MVP").toString());
        ui->GS_4->setText(query.value("STRATEGIE_CROISSANCE").toString());
        ui->SP_4->setText(query.value("PARTENARIATS").toString());
    } else {
        QMessageBox::information(this, "Aucun résultat", "Aucun projet trouvé avec cet ID.");
    }
    ui->tabWidget->setCurrentIndex(5);
}


void taxhedemayssoun::on_b1_4_clicked()
{
    ui->tabWidget->setCurrentIndex(6);
}


void taxhedemayssoun::on_b2_8_clicked()
{
    ui->tabWidget->setCurrentIndex(7);
}


void taxhedemayssoun::on_b3_4_clicked()
{
    QString id = ui->id_3->text();

    QString problem = ui->problem_4->text();
    QString target = ui->target_4->text();
    QString proposition = ui->proposition_4->text();
    QString analyze = ui->analyze_4->text();
    QString positioning = ui->positioning_4->text();
    QString idea = ui->idea_4->text();
    QString cof = ui->cof_4->text();
    QString key = ui->key_4->text();
    QString tools = ui->tools_4->text();
    QString marketing = ui->marketing_4->text();
    QString testing = ui->testing_4->text();
    QString expansion = ui->expansion_4->text();
    QString revenu = ui->revenu_4->text();
    QString costs = ui->costs_4->text();
    QString how = ui->how_4->text();
    QString mvp = ui->MVP_4->text();
    QString gs = ui->GS_4->text();
    QString sp = ui->SP_4->text();

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
    ui->tabWidget->setCurrentIndex(3);
}


void taxhedemayssoun::on_tabWidget_currentChanged(int index)
{
    loadProjects();
    qDebug() << "Tab changed to index:" << index;

    // Ensure the database connection is open
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    // SQL query to fetch project costs
    QSqlQuery query;
    query.prepare(R"(
        SELECT
            CASE
                WHEN TO_NUMBER(COUTS) < 1000 THEN 'Under 1000'
                WHEN TO_NUMBER(COUTS) BETWEEN 1000 AND 10000 THEN '1000 to 10000'
                WHEN TO_NUMBER(COUTS) > 10000 THEN 'Above 10000'
            END AS CostCategory,
            COUNT(*) AS Count
        FROM
            PROJET
        GROUP BY
            CASE
                WHEN TO_NUMBER(COUTS) < 1000 THEN 'Under 1000'
                WHEN TO_NUMBER(COUTS) BETWEEN 1000 AND 10000 THEN '1000 to 10000'
                WHEN TO_NUMBER(COUTS) > 10000 THEN 'Above 10000'
            END
    )");

    // Execute the query and handle potential errors
    if (!query.exec()) {
        qDebug() << "Error fetching project costs:" << query.lastError();
        return;
    }

    // Initialize counters for different cost categories
    int under1000Count = 0;
    int between1000And10000Count = 0;
    int above10000Count = 0;

    // Process query results
    while (query.next()) {
        QString category = query.value(0).toString();
        int count = query.value(1).toInt();

        if (category == "Under 1000") {
            under1000Count = count;
        } else if (category == "1000 to 10000") {
            between1000And10000Count = count;
        } else if (category == "Above 10000") {
            above10000Count = count;
        }
    }

    qDebug() << "Projects under 1000:" << under1000Count;
    qDebug() << "Projects between 1000 and 10000:" << between1000And10000Count;
    qDebug() << "Projects above 10000:" << above10000Count;

    // Create a QGraphicsScene for the bar chart
    QGraphicsScene *scene = new QGraphicsScene(this);
    BarChartItem *barChart = new BarChartItem(under1000Count, between1000And10000Count, above10000Count);
    scene->addItem(barChart);

    // Find the QGraphicsView to display the bar chart
    QGraphicsView *graphicsView = findChild<QGraphicsView *>("graphicsView_2"); // Ensure this matches your UI
    if (graphicsView) {
        graphicsView->setScene(scene); // Set the new scene for the graphics view
    } else {
        qDebug() << "GraphicsView not found!";
    }

    // Prepare and display the statistics message
    QString statsMessage = QString("Total Projects:\n"
                                   "Under 1000: %1\n"
                                   "1000 to 10000: %2\n"
                                   "Above 10000: %3")
                               .arg(under1000Count)
                               .arg(between1000And10000Count)
                               .arg(above10000Count);

    // Update the QLabel with the statistics message
    QLabel *labelStats = findChild<QLabel *>("statlab_2"); // Ensure this matches your UI
    if (labelStats) {
        labelStats->setText(statsMessage);
    } else {
        qDebug() << "Label not found!";
    }
}


void taxhedemayssoun::on_pdf_2_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Enregistrer le PDF",
        "Projets_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".pdf",
        "PDF Files (*.pdf)"
        );

    if (filePath.isEmpty())
        return;

    // Current date and time
    QString currentDate = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm");

    // Start HTML document
    QString html = R"(
        <html>
        <head>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    font-size: 10pt;
                    margin: 20px;
                }
                .header {
                    display: flex;
                    justify-content: space-between;
                    align-items: center;
                    margin-bottom: 20px;
                }
                .header .title {
                    font-size: 18pt;
                    font-weight: bold;
                    text-align: center;
                    flex-grow: 1;
                }
                .logo {
                    width: 80px;
                    height: 80px;
                }
                table {
                    width: 100%;
                    border-collapse: collapse;
                    margin-top: 10px;
                }
                th, td {
                    border: 1px solid #bbb;
                    padding: 8px;
                    text-align: left;
                }
                th {
                    background-color: #f0f0f0;
                    font-weight: bold;
                }
                tr:nth-child(even) {
                    background-color: #f9f9f9;
                }
                .footer {
                    margin-top: 30px;
                    font-size: 8pt;
                    text-align: right;
                    color: #555;
                }
            </style>
        </head>
        <body>
            <div class="header">
                <img src='logo.png' class='logo' />
                <div class='title'>Liste des Projets</div>
                <div style='width: 80px;'></div> <!-- spacer -->
            </div>
            <table>
    )";

    // Header row
    html += "<tr>";
    for (int col = 0; col < ui->tabaff_2->columnCount(); ++col) {
        QString header = ui->tabaff_2->horizontalHeaderItem(col)->text().toHtmlEscaped();
        html += "<th>" + header + "</th>";
    }
    html += "</tr>";

    // Table content
    for (int row = 0; row < ui->tabaff_2->rowCount(); ++row) {
        if (ui->tabaff_2->isRowHidden(row)) continue;
        html += "<tr>";
        for (int col = 0; col < ui->tabaff_2->columnCount(); ++col) {
            QTableWidgetItem* item = ui->tabaff_2->item(row, col);
            QString text = item ? item->text().toHtmlEscaped() : "";
            html += "<td>" + text + "</td>";
        }
        html += "</tr>";
    }

    html += R"(
            </table>
            <div class='footer'>
                Exporté le: )" + currentDate + R"(</div>
        </body>
        </html>
    )";

    // Create and configure document
    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Landscape); // Landscape format

    document.print(&printer);

    QMessageBox::information(this, "Succès", "Le fichier PDF a été généré avec succès :\n" + filePath);
}


void taxhedemayssoun::on_btrie_2_clicked()
{
    if (triAscendant){
        ui->tabaff_2->sortItems(0, Qt::AscendingOrder);
        ui->idtrie_2->setText("ID sorted Ascending");
    }
    else{
        ui->tabaff_2->sortItems(0, Qt::DescendingOrder);
        ui->idtrie_2->setText("ID sorted Descending");
    }
    triAscendant = !triAscendant; // on inverse le sens pour la prochaine fois
}


void taxhedemayssoun::on_re_2_cursorPositionChanged(int arg1, int arg2)
{
    QString searchText = QString::number(arg1);

    for (int row = 0; row < ui->tabaff_2->rowCount(); ++row)
    {
        bool matchFound = false;
        for (int col = 0; col < ui->tabaff_2->columnCount(); ++col)
        {
            QTableWidgetItem *item = ui->tabaff_2->item(row, col);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive))
            {
                matchFound = true;
                break; // Sortir de la boucle si un match est trouvé
            }
        }
        ui->tabaff_2->setRowHidden(row, !matchFound); // Masquer ou afficher la ligne
    }
}


void taxhedemayssoun::on_b2_7_clicked()
{
    QString id = ui->id_4->text(); // Retrieve the ID from the UI

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
    ui->tabaff_2->setRowCount(projects.size()); // Nombre de lignes
    ui->tabaff_2->setColumnCount(18); // Ajusté au nombre de colonnes
    ui->tabaff_2->setHorizontalHeaderLabels({
        "ID", "Problem", "Target", "Proposition", "Analyze", "Positioning", "Idea",
        "Cof", "Key", "Tools", "Marketing", "Testing", "Expansion",
        "Revenu", "Costs", "How", "MVP", "Growth Strategy", "Partnerships"
    });

    for (int row = 0; row < projects.size(); ++row) {
        const Projet &p = projects[row];
        ui->tabaff_2->setItem(row, 0, new QTableWidgetItem(QString::number(p.id)));
        ui->tabaff_2->setItem(row, 1, new QTableWidgetItem(p.problem));
        ui->tabaff_2->setItem(row, 2, new QTableWidgetItem(p.target));
        ui->tabaff_2->setItem(row, 3, new QTableWidgetItem(p.proposition));
        ui->tabaff_2->setItem(row, 4, new QTableWidgetItem(p.analyze));
        ui->tabaff_2->setItem(row, 5, new QTableWidgetItem(p.positioning));
        ui->tabaff_2->setItem(row, 6, new QTableWidgetItem(p.idea));
        ui->tabaff_2->setItem(row, 7, new QTableWidgetItem(p.cof));
        ui->tabaff_2->setItem(row, 8, new QTableWidgetItem(p.key));
        ui->tabaff_2->setItem(row, 9, new QTableWidgetItem(p.tools));
        ui->tabaff_2->setItem(row, 10, new QTableWidgetItem(p.marketing));
        ui->tabaff_2->setItem(row, 11, new QTableWidgetItem(p.testing));
        ui->tabaff_2->setItem(row, 12, new QTableWidgetItem(p.expansion));
        ui->tabaff_2->setItem(row, 13, new QTableWidgetItem(p.revenu));
        ui->tabaff_2->setItem(row, 14, new QTableWidgetItem(p.costs));
        ui->tabaff_2->setItem(row, 15, new QTableWidgetItem(p.how));
        ui->tabaff_2->setItem(row, 16, new QTableWidgetItem(p.mvp));
        ui->tabaff_2->setItem(row, 17, new QTableWidgetItem(p.gs));
        ui->tabaff_2->setItem(row, 18, new QTableWidgetItem(p.sp));
    }
}


void taxhedemayssoun::on_gen_3_clicked()
{
    QString idg = ui->idg_2->text();

    if (idg.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    bool ok;
    int idValue = idg.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM PROJET WHERE ID_PROJET = :id");
    query.bindValue(":id", idValue); // Ensure this matches the DB column type

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de la récupération du projet : " + query.lastError().text());
        return;
    }

    if (!query.next()) {
        QMessageBox::information(this, "Projet introuvable", "Aucun projet avec cet ID.");
        return;
    }

    // Build your input string using a delimiter (e.g., '|')
    QStringList projectData;
    projectData << "Probleme_resolu:" + query.value("PROBLEME_RESOLU").toString();
    projectData << "Public_cible:" + query.value("PUBLIC_CIBLE").toString();
    projectData << "Proposition_de_valeur:" + query.value("PROPOSITION_DE_VALEUR").toString();
    projectData << "Analyse_du_marche:" + query.value("ANALYSE_DU_MARCHE").toString();
    projectData << "Concurrence:" + query.value("CONCURRENCE").toString();
    projectData << "Validation_idee:" + query.value("VALIDATION_IDEE").toString();
    projectData << "Cofondateurs:" + query.value("COFONDATEURS").toString();
    projectData << "Talents_a_recruter:" + query.value("TALENTS_A_RECRUTER").toString();
    projectData << "Outils_technologiques:" + query.value("OUTILS_TECHNOLOGIQUES").toString();
    projectData << "Strategie_marketing:" + query.value("STRATEGIE_MARKETING").toString();
    projectData << "Tests_utilisateurs:" + query.value("TESTS_UTILISATEURS").toString();
    projectData << "Expansion_du_marche:" + query.value("EXPANSION_MARCHE").toString();
    projectData << "Source_de_revenus:" + query.value("SOURCE_REVENUS").toString();
    projectData << "Couts:" + query.value("COUTS").toString();
    projectData << "how:" + query.value("MODELE_ACHIEVEMENT").toString();
    projectData << "mvp:" + query.value("MVP").toString();
    projectData << "Strategie_de_croissance:" + query.value("STRATEGIE_CROISSANCE").toString();
    projectData << "Partenariats:" + query.value("PARTENARIATS").toString();

    QString inputString = projectData.join("|");

    // Write input to input.txt
    QFile inputFile("C://Users//ASUS-PC//Documents//Nova_Up//bmc generator//input.txt");
    if (inputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&inputFile);
        out << inputString;
        inputFile.close();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'écriture dans input.txt.");
        return;
    }

    // Prepare and start the script
    QString scriptPath = "C://Users//ASUS-PC//Documents//Nova_Up//bmc generator//main.py";
    QProcess *process = new QProcess(this);  // Use a pointer to manage the process
    connect(process, &QProcess::finished, this, [this, process](int exitCode, QProcess::ExitStatus exitStatus) {
        process->deleteLater(); // Delete the process after it finishes
        if (exitStatus == QProcess::CrashExit) {
            QMessageBox::critical(this, "Erreur", "Le script Python a échoué.");
            return;
        }

        // Read output from output.txt
        QFile outputFile("C://Users//ASUS-PC//Documents//Nova_Up//bmc generator//output.txt");
        if (outputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&outputFile);
            QString output = in.readAll();
            outputFile.close();

            if (output.isEmpty()) {
                QMessageBox::warning(this, "Erreur", "Le script Python n'a renvoyé aucune sortie.");
                return;
            }

            ui->BMC_2->setText(output); // Set the output text in the BMC label
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la lecture de output.txt.");
        }
    });

    process->start("python", QStringList() << scriptPath);
}


void taxhedemayssoun::on_gen_4_clicked()
{
    QString idg = ui->idp_2->text();

    if (idg.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM PROJET WHERE ID_PROJET = :id");
    query.bindValue(":id", idg);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de la récupération du projet : " + query.lastError().text());
        return;
    }

    if (!query.next()) {
        QMessageBox::information(this, "Projet introuvable", "Aucun projet avec cet ID.");
        return;
    }

    // Build your input string using a delimiter (e.g., '|')
    QStringList projectData;
    projectData << "Probleme_resolu:" + query.value("PROBLEME_RESOLU").toString();
    projectData << "Public_cible:" + query.value("PUBLIC_CIBLE").toString();
    projectData << "Proposition_de_valeur:" + query.value("PROPOSITION_DE_VALEUR").toString();
    projectData << "Analyse_du_marche:" + query.value("ANALYSE_DU_MARCHE").toString();
    projectData << "Concurrence:" + query.value("CONCURRENCE").toString();
    projectData << "Validation_idee:" + query.value("VALIDATION_IDEE").toString();
    projectData << "Cofondateurs:" + query.value("COFONDATEURS").toString();
    projectData << "Talents_a_recruter:" + query.value("TALENTS_A_RECRUTER").toString();
    projectData << "Outils_technologiques:" + query.value("OUTILS_TECHNOLOGIQUES").toString();
    projectData << "Strategie_marketing:" + query.value("STRATEGIE_MARKETING").toString();
    projectData << "Tests_utilisateurs:" + query.value("TESTS_UTILISATEURS").toString();
    projectData << "Expansion_du_marche:" + query.value("EXPANSION_MARCHE").toString();
    projectData << "Source_de_revenus:" + query.value("SOURCE_REVENUS").toString();
    projectData << "Couts:" + query.value("COUTS").toString();
    projectData << "how:" + query.value("MODELE_ACHIEVEMENT").toString();
    projectData << "mvp:" + query.value("MVP").toString();
    projectData << "Strategie_de_croissance:" + query.value("STRATEGIE_CROISSANCE").toString();
    projectData << "Partenariats:" + query.value("PARTENARIATS").toString();


    QString inputString = projectData.join("|");

    // Write input to input.txt
    QFile inputFile("C://Users//ASUS-PC//Documents//Nova_Up//bmc generator//input.txt");
    if (inputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&inputFile);
        out << inputString;
        inputFile.close();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'écriture dans input.txt.");
        return;
    }

    // Prepare and start the script
    QString scriptPath = "C://Users//ASUS-PC//Documents//Nova_Up//bmc generator//prediction.py";
    QProcess *process = new QProcess(this);  // Use a pointer to manage the process
    connect(process, &QProcess::finished, this, [this, process](int exitCode, QProcess::ExitStatus exitStatus) {
        process->deleteLater(); // Delete the process after it finishes
        if (exitStatus == QProcess::CrashExit) {
            QMessageBox::critical(this, "Erreur", "Le script Python a échoué.");
            return;
        }

        // Read output from output.txt
        QFile outputFile("C://Users//ASUS-PC//Documents//Nova_Up//bmc generator//output.txt");
        if (outputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&outputFile);
            QString output = in.readAll();
            outputFile.close();

            if (output.isEmpty()) {
                QMessageBox::warning(this, "Erreur", "Le script Python n'a renvoyé aucune sortie.");
                return;
            }

            ui->pred_2->setText(output); // Set the output text in the BMC label
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la lecture de output.txt.");
        }
    });

    process->start("python", QStringList() << scriptPath);
}

