#include "tacheamine.h"
#include "ui_tacheamine.h"
#include "sponsor.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDebug>
#include <QMarginsF>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <cmath>
#include <QDateTime>
#include <QScrollBar>
#include "chatbot.h"
#include <QPrinter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QPageSize>
#include <QPageLayout>
tacheamine::tacheamine(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tacheamine)
    , model(new QSqlTableModel(this))
{
    ui->setupUi(this);
    // Initially hide the chat interface
    ui->ChatBot->setVisible(false);
    ui->chatdisplay->setVisible(false);
    ui->userIn->setVisible(false);
    ui->insert->setVisible(false);

    // Style the chat container
    ui->ChatBot->setStyleSheet(
        "QWidget#ChatBot {"
        "background-color: #ffffff;"
        "border-radius: 12px;"
        "border: 1px solid #e0e0e0;"
        "padding: 12px;"
        "}"
        );

    // Modern chat display styling

    ui->chatdisplay->setStyleSheet(
        "QTextEdit {"
        "background-color: #f8f9fa;"
        "border: none;"
        "border-radius: 8px;"
        "padding: 12px;"
        "font-family: 'Segoe UI', Arial, sans-serif;"
        "font-size: 14px;"
        "color: #333333;"
        "}"
        "QScrollBar:vertical {"
        "width: 8px;"
        "background: transparent;"
        "}"
        "QScrollBar::handle:vertical {"
        "background: #cccccc;"
        "border-radius: 4px;"
        "min-height: 30px;"
        "}"
        );
    // Modern input area styling


    // Modern send button styling
    ui->insert->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "background-color: #aa00ff;"
        "border-radius: 20px;"
        "padding: 8px 16px;"
        "min-width: 80px;"
        "color: white;"
        "font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "background-color: #aaaaff;"
        "}"
        "QPushButton:pressed {"
        "background-color:#aa00ff; "
        "}"
        );

    // Chat bot button styling
    ui->bot->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "background-color: #aa00ff;"

        "border-radius: 20px;"
        "padding: 12px;"
        "}"
        "QPushButton:hover {"
        "background-color: #aaaaff;"
        "}"
        );

    // Set icons
    QIcon sendIcon("icon.png");
    ui->insert->setIcon(sendIcon);
    ui->insert->setIconSize(QSize(24, 24));

    ui->bot->setIcon(QIcon("bot.png"));
    ui->bot->setIconSize(QSize(32, 32));
    ui->bot->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "background-color: #aa00ff;"
        "border-radius: 20px;"
        "padding: 8px;"
        "}"
        "QPushButton:hover {"
        "background-color: #aaaaff;"
        "}"
        );

    // Initialize database and UI
    setupUI();
    db = QSqlDatabase::database();
    checkDatabaseConnection();
    setupConnections();


    // Initialize chatbot
    chatbot = new Chatbot(db);
    QSqlQuery testQuery(db);
    if (testQuery.exec("SELECT ID_PROJET, PROBLEME_RESOLU FROM PROJET")) {
        qDebug() << "PROJET table contents:";
        while (testQuery.next()) {
            qDebug() << "ID:" << testQuery.value(0).toInt()
            << "Problem:" << testQuery.value(1).toString();
        }
    } else {
        qDebug() << "PROJET query failed:" << testQuery.lastError().text();
    }

    // Configure the model and load data
    model->setTable("SPONSOR");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    if (!model->select()) {
        QMessageBox::critical(this, "Erreur Table",
                              "Impossible de récupérer les données: " + model->lastError().text(),
                              QMessageBox::Ok);
    } else {
        loadTableData();
    }
}

tacheamine::~tacheamine()
{
    delete chatbot;
    delete model;
    delete ui;
}
void tacheamine::setupUI()
{
    // Apply stylesheet for QMessageBox
    this->setStyleSheet(
        "QMessageBox { "
        "background-color: black; "
        "color: white; "
        "font-size: 12pt; "
        "border: 2px solid white; "
        "border-radius: 10px; "
        "padding: 10px; "
        "}"
        "QMessageBox QLabel { color: white; }"
        );

    // Initialize filter options
    ui->filter->addItem("All Domains");
    ui->filter->addItem("Capacity (High to Low)");
    ui->filter->addItem("Capacity (Low to High)");
    ui->filter->addItem("Domain: Technology");
    ui->filter->addItem("Domain: Finance");
    ui->filter->addItem("Domain: Health");
    ui->filter->addItem("Domain: Retail & E-commerce");
    ui->filter->addItem("Domain: Education & Training");
    ui->filter->addItem("Domain: Media & Entertainement");
    ui->filter->addItem("Domain: Automotive");
    ui->filter->addItem("Domain: Food");
    ui->filter->addItem("Domain: Real Estate");
    ui->filter->addItem("Domain: Other");
}

void tacheamine::setupConnections()
{
    connect(ui->stat, &QPushButton::clicked, this, &tacheamine::updateDomainStatistics);
    connect(ui->add, &QPushButton::clicked, this, &tacheamine::on_add_clicked);
    connect(ui->upd, &QPushButton::clicked, this, &tacheamine::on_upd_clicked);
    connect(ui->del, &QPushButton::clicked, this, &tacheamine::on_del_clicked);
    connect(ui->load, &QPushButton::clicked, this, &tacheamine::on_load_clicked);
    connect(ui->filter, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &tacheamine::on_filter_currentIndexChanged);
    connect(ui->downloadPdf, &QPushButton::clicked, this, &tacheamine::on_downloadPdf_clicked);
    connect(ui->insert, &QPushButton::clicked, this, &tacheamine::on_insert_clicked);
    connect(ui->bot, &QPushButton::clicked, this, &tacheamine::toggleChatInterface);
}

void tacheamine::toggleChatInterface()
{
    bool isVisible = ui->ChatBot->isVisible();
    ui->ChatBot->setVisible(!isVisible);
    ui->chatdisplay->setVisible(!isVisible);
    ui->userIn->setVisible(!isVisible);
    ui->insert->setVisible(!isVisible);

    if (!isVisible) {
        // Initialize chat when first shown
        ui->chatdisplay->clear();
        displayBotMessage("how can I help you?");
        displayBotMessage("type help for more informations");
    }
}

void tacheamine::checkDatabaseConnection()
{
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Erreur de connexion",
                              "Impossible d'établir la connexion avec la base de données.",
                              QMessageBox::Ok);
        qDebug() << "Erreur BD:" << db.lastError().text();
    }
}

void tacheamine::on_insert_clicked()
{
    QString userInput = ui->userIn->text();
    if (userInput.isEmpty()) {
        return;
    }

    // Display user message
    displayUserMessage(userInput);

    // Process with chatbot and get response
    QString botResponse = chatbot->processInput(userInput);
    displayBotMessage(botResponse);

    // Clear input field
    ui->userIn->clear();
}

void tacheamine::displayBotMessage(const QString &message) {
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm");
    QString html = QString(
                       "<div style='margin: 8px; text-align: left;'>"
                       "<div style='background-color: #f0f0f0; border-radius: 18px; padding: 10px 14px;"
                       "max-width: 80%; display: inline-block; word-wrap: break-word; text-align: left;'>"
                       "%1"
                       "</div>"
                       "<div style='color: #70757a; font-size: 11px; padding: 2px 8px; text-align: left;'>"
                       "%2"
                       "</div>"
                       "</div>"
                       ).arg(message.toHtmlEscaped(), timestamp);

    ui->chatdisplay->append(html);
    scrollToBottom();
}

void tacheamine::displayUserMessage(const QString &message) {
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm");
    QString html = QString(
                       "<div style='margin: 8px; text-align: right;'>"
                       "<div style='background-color: #4285f4; color: white; border-radius: 18px; padding: 10px 14px;"
                       "max-width: 80%; display: inline-block; word-wrap: break-word; text-align: left;'>"
                       "%1"
                       "</div>"
                       "<div style='color: #70757a; font-size: 11px; padding: 2px 8px; text-align: right;'>"
                       "%2"
                       "</div>"
                       "</div>"
                       ).arg(message.toHtmlEscaped(), timestamp);

    ui->chatdisplay->append(html);
    scrollToBottom();
}

void tacheamine::scrollToBottom()
{
    QScrollBar *scrollbar = ui->chatdisplay->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
    ui->chatdisplay->repaint();
}


void tacheamine::loadTableData()
{
    // Clear the table first
    ui->data->clearContents();
    ui->data->setRowCount(0);

    // Update row count based on filtered data
    ui->data->setRowCount(model->rowCount());
    ui->data->setColumnCount(model->columnCount());

    // Set headers
    for (int col = 0; col < model->columnCount(); ++col) {
        ui->data->setHorizontalHeaderItem(col, new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString()));
    }

    // Fill the table with filtered data
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(model->index(row, col).data().toString());
            ui->data->setItem(row, col, item);
        }
    }

    ui->data->resizeColumnsToContents();
    ui->data->update(); // Force update of the table widget
}

void tacheamine::on_add_clicked()
{
    QString code_fiscal = ui->cr->text().trimmed();
    QString nom = ui->name->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString telephone = ui->phone->text().trimmed();
    QString domaine = ui->domain->currentText().trimmed();
    QString adresse = ui->address->text().trimmed();
    int annee_fondation = ui->year->text().toInt();
    QString type_sponsoring = ui->type->text().trimmed();
    QString capacite_str = ui->capacity->text().trimmed();

    // Vérification des champs obligatoires
    if (code_fiscal.isEmpty() || nom.isEmpty() || email.isEmpty() ||
        telephone.isEmpty() || adresse.isEmpty() || type_sponsoring.isEmpty()) {
        QMessageBox::warning(this, "Erreur de saisie",
                             "Les champs Code Fiscal, Nom, Email, Téléphone, Adresse et Type de sponsoring sont obligatoires.",
                             QMessageBox::Ok);
        return;
    }

    // Validation de l'email
    if (!email.contains('@') || !email.contains('.')) {
        QMessageBox::warning(this, "Email invalide",
                             "Veuillez saisir un email valide contenant '@' et '.'.",
                             QMessageBox::Ok);
        return;
    }

    // Validation du numéro de téléphone : chiffres uniquement
    QRegularExpression phoneRegex("^[0-9]+$");
    if (!phoneRegex.match(telephone).hasMatch()) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Le numéro de téléphone doit contenir uniquement des chiffres.",
                             QMessageBox::Ok);
        return;
    }

    // Validation de la capacité financière
    bool isDouble;
    double capacite_financiere = capacite_str.toDouble(&isDouble);
    if (!isDouble || capacite_financiere < 0) {
        QMessageBox::warning(this, "Capacité financière invalide",
                             "Veuillez saisir une capacité financière valide et positive.",
                             QMessageBox::Ok);
        return;
    }

    // Vérification des doublons
    if (Sponsor::exists(code_fiscal)) {
        QMessageBox::warning(this, "Doublon",
                             "Un sponsor avec ce Code Fiscal existe déjà.",
                             QMessageBox::Ok);
        return;
    }

    if (Sponsor::emailExists(email)) {
        QMessageBox::warning(this, "Doublon",
                             "Un sponsor avec cet email existe déjà.",
                             QMessageBox::Ok);
        return;
    }

    // Création de l'objet Sponsor et ajout
    Sponsor sponsor(code_fiscal, nom, email, telephone, domaine, adresse,
                    annee_fondation, type_sponsoring, capacite_financiere);

    bool success = sponsor.add();
    if (success) {
        QMessageBox::information(this, "Succès", "Sponsor ajouté avec succès.");
        loadTableData();

        // Nettoyage des champs
        ui->cr->clear();
        ui->name->clear();
        ui->email->clear();
        ui->phone->clear();
        ui->domain->setCurrentIndex(0);
        ui->address->clear();
        ui->year->clear();
        ui->type->clear();
        ui->capacity->clear();
    } else {
        QMessageBox::critical(this, "Erreur BD", "Échec de l'ajout: impossible d'ajouter le sponsor.");
    }
}


void tacheamine::on_upd_clicked()
{
    // Ensure a sponsor has been loaded by checking if loadedCodeFiscal is not empty
    if (loadedCodeFiscal.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez d'abord charger un sponsor avant de le mettre à jour.", QMessageBox::Ok);
        return;
    }

    // Ensure all the fields are filled
    QString nom = ui->name1->text().trimmed();
    QString email = ui->email1->text().trimmed();
    QString telephone = ui->phone1->text().trimmed();
    QString domaine = ui->domain1->currentText().trimmed();
    QString adresse = ui->address1->text().trimmed();
    int annee_fondation = ui->year1->date().year();
    QString type_sponsoring = ui->type1->text().trimmed();
    double capacite_financiere = ui->capacity1->text().toDouble();

    // Check if required fields are filled
    if (nom.isEmpty() || email.isEmpty() || telephone.isEmpty() || domaine.isEmpty() || adresse.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis.", QMessageBox::Ok);
        return;
    }

    // Prepare the update query
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

    // Bind the values to the query
    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":domaine", domaine);
    query.bindValue(":adresse", adresse);
    query.bindValue(":annee_fondation", annee_fondation);
    query.bindValue(":type_sponsoring", type_sponsoring);
    query.bindValue(":capacite_financiere", capacite_financiere);
    query.bindValue(":code_fiscal", loadedCodeFiscal);  // Ensure we are updating the correct sponsor

    // Execute the update query
    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Sponsor mis à jour avec succès.");
        loadTableData();  // Refresh the table data after the update
    } else {
        QMessageBox::critical(this, "Erreur BD", "Échec de la mise à jour: " + query.lastError().text());
    }
}




void tacheamine::on_load_clicked()
{
    QString code_fiscal = ui->cr1->text().trimmed();

    if (code_fiscal.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un Code Fiscal pour charger les données.");
        return;
    }

    Sponsor sponsor;
    if (sponsor.load(code_fiscal)) {
        // Set the loadedCodeFiscal to the current code_fiscal
        loadedCodeFiscal = code_fiscal;  // Make sure to set the loadedCodeFiscal

        // Fill the fields
        ui->name1->setText(sponsor.getNom());
        ui->email1->setText(sponsor.getEmail());
        ui->phone1->setText(sponsor.getTelephone());

        int index = ui->domain1->findText(sponsor.getDomaine());
        if (index >= 0) {
            ui->domain1->setCurrentIndex(index);
        }

        ui->address1->setText(sponsor.getAdresse());
        ui->year1->setDate(QDate(sponsor.getAnneeFondation(), 1, 1)); // Convert year to QDate
        ui->type1->setText(sponsor.getTypeSponsoring());
        ui->capacity1->setText(QString::number(sponsor.getCapaciteFinanciere()));

        QMessageBox::information(this, "Succès", "Données du sponsor chargées avec succès.");
    } else {
        // Clear the fields if no result is found
        ui->name1->clear();
        ui->email1->clear();
        ui->phone1->clear();
        ui->domain1->setCurrentIndex(0);
        ui->address1->clear();
        ui->year1->setDate(QDate::currentDate());
        ui->type1->clear();
        ui->capacity1->clear();

        // Clear the loadedCodeFiscal since loading failed
        loadedCodeFiscal.clear();

        QMessageBox::warning(this, "Erreur", "Aucun sponsor trouvé avec ce Code Fiscal.");
    }
}


void tacheamine::on_del_clicked()
{
    QString code_fiscal = ui->code->text().trimmed();  // Get the code fiscal input from the user

    // Check if the code fiscal is empty
    if (code_fiscal.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un Code Fiscal à supprimer.", QMessageBox::Ok);
        return;
    }

    // Check if the sponsor exists in the database
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM SPONSOR WHERE CODE_FISCAL = :code_fiscal");
    checkQuery.bindValue(":code_fiscal", code_fiscal);

    if (!checkQuery.exec()) {
        // Handle the error if the query fails
        QMessageBox::critical(this, "Erreur BD", "Erreur lors de la vérification: " + checkQuery.lastError().text(), QMessageBox::Ok);
        return;
    }

    // If no sponsor found with the given code fiscal
    if (checkQuery.next() && checkQuery.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Erreur", "Aucun sponsor trouvé avec ce Code Fiscal.", QMessageBox::Ok);
        return;
    }

    // Ask for confirmation before deleting the sponsor
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
                                                              "Voulez-vous vraiment supprimer ce sponsor ?",
                                                              QMessageBox::Yes | QMessageBox::No);

    // If the user confirms the deletion
    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM SPONSOR WHERE CODE_FISCAL = :code_fiscal");
        query.bindValue(":code_fiscal", code_fiscal);

        if (query.exec()) {
            // Successful deletion
            QMessageBox::information(this, "Succès", "Sponsor supprimé avec succès.");
            loadTableData(); // Refresh the table after deletion
        } else {
            // If the deletion query fails
            QMessageBox::critical(this, "Erreur BD", "Échec de la suppression: " + query.lastError().text());
        }
    }
}


void tacheamine::on_filter_currentIndexChanged(int index)
{
    QString filterText = ui->filter->currentText();

    // Clear any existing filters
    model->setFilter("");

    // Handle capacity sorting options
    if (filterText == "Capacity (High to Low)") {
        model->setSort(model->fieldIndex("CAPACITE_FINANCIERE"), Qt::DescendingOrder);
    } else if (filterText == "Capacity (Low to High)") {
        model->setSort(model->fieldIndex("CAPACITE_FINANCIERE"), Qt::AscendingOrder);
    }
    // Handle domain filter options
    else if (filterText.startsWith("Domain: ")) {
        QString domain = filterText.mid(8); // Remove "Domain: " prefix
        model->setFilter(QString("DOMAINE = '%1'").arg(domain));
        // Default sort for domain filters
        model->setSort(model->fieldIndex("NOM"), Qt::AscendingOrder);
    }
    // All domains (no filter)
    else if (filterText == "All Domains") {
        // No filter, just use default sorting
        model->setSort(model->fieldIndex("NOM"), Qt::AscendingOrder);
    }

    // Refresh the table
    model->select();
    loadTableData();
}

void tacheamine::on_downloadPdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "sponsors.pdf", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) return;

    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    // Get the absolute path to the logo image
    QString logoPath = QDir::current().absoluteFilePath("image4.png");

    QTextDocument doc;
    QString htmlContent = R"(
    <html>
    <head>
    <style>
        body { font-family: Arial, sans-serif; }
        .header { display: flex; justify-content: space-between; align-items: center; margin-bottom: 20px; }
        .logo { height: 80px; } /* Adjust height as needed */
        h1 { color: #3a539b; text-align: center; margin: 0; flex-grow: 1; }
        .subtitle { text-align: right; color: #666; margin-bottom: 30px; }
        table { width: 100%; border-collapse: collapse; margin-top: 20px; }
        th { background-color: #3a539b; color: white; padding: 10px; text-align: center; }
        td { padding: 8px; border: 1px solid #ddd; text-align: left; }
        tr:nth-child(even) { background-color: #f2f2f2; }
        .footer { text-align: center; margin-top: 30px; color: #666; font-size: 0.8em; }
        .capacity { text-align: right; }
    </style>
    </head>
    <body>
    <div class="header">
        <img class="logo" src=")" + logoPath + R"(" />
        <h1>Sponsors Report</h1>
        <div style="width: 80px;"></div> <!-- Empty div for balance -->
    </div>
    <div class="subtitle">ON The: )" + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm") + R"(</div>
    <table>
        <tr>
            <th>Code</th>
            <th>Name</th>
            <th>Email</th>
            <th>Phone</th>
            <th>Domain</th>
            <th>Address</th>
            <th>Year</th>
            <th>Type</th>
            <th>Capacity</th>
        </tr>
    )";

    // Add sponsor data rows
    for (int row = 0; row < ui->data->rowCount(); ++row) {
        htmlContent += "<tr>";
        for (int col = 0; col < ui->data->columnCount(); ++col) {
            QString text = ui->data->item(row, col) ? ui->data->item(row, col)->text() : "";

            // Special formatting for capacity column (right-aligned)
            if (col == 8) { // Assuming capacity is the 9th column (0-based index 8)
                htmlContent += QString("<td class='capacity'>$%1</td>").arg(text);
            } else {
                htmlContent += QString("<td>%1</td>").arg(text);
            }
        }
        htmlContent += "</tr>";
    }

    htmlContent += R"(
    </table>
    <div class="footer">© )" + QDate::currentDate().toString("yyyy") + R"( BY NOVA UP</div>
    </body>
    </html>
    )";

    doc.setHtml(htmlContent);
    doc.setPageSize(printer.pageRect(QPrinter::Point).size());

    // Print to PDF
    doc.print(&printer);

    // Open the PDF automatically
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));

    QMessageBox::information(this, "Success", "Sponsors PDF exported successfully");
}

PieChartWidget::PieChartWidget(const QVector<QPair<QString, double>>& data,
                               const QVector<QColor>& colors,
                               QWidget* parent)
    : QWidget(parent), m_data(data), m_colors(colors) {
    setMinimumSize(500, 400);
}

void PieChartWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int padding = 50;
    int w = width() - 2 * padding;
    int h = height() - 2 * padding;
    int pieSize = qMin(w, h);
    QRect pieRect(padding + (w - pieSize) / 2, padding + (h - pieSize) / 2, pieSize, pieSize);

    double startAngle = 0;

    for (int i = 0; i < m_data.size(); ++i) {
        double value = m_data[i].second;
        QString label = QString("%1 (%2%)").arg(m_data[i].first).arg(value, 0, 'f', 1);

        double spanAngle = value * 3.6;
        painter.setBrush(m_colors[i]);
        painter.setPen(Qt::white);
        painter.drawPie(pieRect, startAngle * 16, spanAngle * 16);

        // Label positioning
        double angleRad = (startAngle + spanAngle / 2) * M_PI / 180.0;
        QPointF center = pieRect.center();
        double radius = pieRect.width() / 2.5;
        QPointF labelPos = center + QPointF(qCos(angleRad) * radius, -qSin(angleRad) * radius);

        painter.setPen(Qt::black);
        painter.drawText(labelPos, label);

        startAngle += spanAngle;
    }
}

// ---------- updateDomainStatistics() ----------
void tacheamine::updateDomainStatistics() {
    int totalSponsors = Sponsor::getTotalCount();
    if (totalSponsors == 0) {
        QMessageBox::warning(this, "Statistiques", "Aucun sponsor dans la base de données.");
        return;
    }

    QStringList domains = {
        "Technology", "Finance", "Health", "Retail & E-commerce",
        "Education & Training", "Media & Entertainement", "Automotive",
        "Food", "Real Estate", "Other"
    };

    QMap<QString, int> domainPercentages;
    for (const QString& domain : domains) {
        int count = Sponsor::getDomainCount(domain);
        int percentage = (count * 100) / totalSponsors;
        if (percentage > 0) {
            domainPercentages[domain] = percentage;
        }
    }

    QVector<QPair<QString, double>> pieData;
    QVector<QColor> colors = {
        QColor(41, 128, 185), QColor(46, 204, 170), QColor(231, 76, 125),
        QColor(149, 117, 221), QColor(243, 156, 18), QColor(231, 76, 60),
        QColor(46, 134, 193), QColor(39, 174, 96), QColor(211, 84, 0),
        QColor(142, 68, 173)
    };

    QVector<QColor> pieColors;
    int colorIndex = 0;
    for (auto it = domainPercentages.begin(); it != domainPercentages.end(); ++it) {
        pieData.append(qMakePair(it.key(), static_cast<double>(it.value())));
        pieColors.append(colors[colorIndex % colors.size()]);
        colorIndex++;
    }

    // Clear old chart if exists
    QLayout* chartLayout = ui->chartPlaceholder->layout();
    if (!chartLayout) {
        chartLayout = new QVBoxLayout(ui->chartPlaceholder);
        ui->chartPlaceholder->setLayout(chartLayout);
    }

    QLayoutItem* item;
    while ((item = chartLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    PieChartWidget* pieWidget = new PieChartWidget(pieData, pieColors, ui->chartPlaceholder);
    chartLayout->addWidget(pieWidget);

    QMessageBox::information(this, "Succès", "Statistiques mises à jour avec succès.");
}
