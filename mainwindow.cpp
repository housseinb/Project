#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sponsor.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDebug>
#include <QMarginsF>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QSqlTableModel(this))
{
    ui->setupUi(this);

    // Initialize the UI
    setupUI();

    // Check database connection
    checkDatabaseConnection();

    // Setup connections
    setupConnections();

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

MainWindow::~MainWindow()
{
    delete model;
    delete ui;
}

void MainWindow::setupUI()
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
    ui->filter->addItem("All Domains"); // Default option to show all
    ui->filter->addItem("Capacity (High to Low)");
    ui->filter->addItem("Capacity (Low to High)");

    // Add domain filters
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

void MainWindow::setupConnections()
{
    connect(ui->stat, &QPushButton::clicked, this, &MainWindow::updateDomainStatistics);
    connect(ui->add, &QPushButton::clicked, this, &MainWindow::on_add_clicked);
    connect(ui->upd, &QPushButton::clicked, this, &MainWindow::on_upd_clicked);
    connect(ui->del, &QPushButton::clicked, this, &MainWindow::on_del_clicked);
    connect(ui->load, &QPushButton::clicked, this, &MainWindow::on_load_clicked);
    connect(ui->filter, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_filter_currentIndexChanged);
    connect(ui->downloadPdf, &QPushButton::clicked, this, &MainWindow::on_downloadPdf_clicked);
}

void MainWindow::checkDatabaseConnection()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Erreur de connexion",
                              "Impossible d'établir la connexion avec la base de données.",
                              QMessageBox::Ok);
        qDebug() << "Erreur BD:" << db.lastError().text();
    }
}

void MainWindow::loadTableData()
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

void MainWindow::on_add_clicked()
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


void MainWindow::on_upd_clicked()
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




void MainWindow::on_load_clicked()
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


void MainWindow::on_del_clicked()
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


void MainWindow::on_filter_currentIndexChanged(int index)
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

void MainWindow::on_downloadPdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier", "", "PDF Files (*.pdf)");

    if (filePath.isEmpty()) {
        return;  // User canceled
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);
    pdfWriter.setPageMargins(QMarginsF(10, 10, 10, 10));

    QPainter painter(&pdfWriter);

    int margin = 15;
    int yPosition = margin;

    // Draw title at top center
    QFont titleFont("Arial", 14, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(QRect(margin, yPosition, pdfWriter.width() - 2*margin, 30),
                     Qt::AlignHCenter | Qt::AlignTop, "Liste des Sponsors");

    yPosition += 40;  // Space after title

    // Use smaller fonts
    QFont headerFont("Arial", 8, QFont::Bold);
    QFont dataFont("Arial", 7);

    // Set column names and widths
    QStringList columnNames = {
        "CODE", "NOM", "EMAIL", "TEL", "DOMAINE",
        "ADRESSE", "ANNEE", "TYPE", "CAPACITE"
    };

    // Define optimized width percentages
    QVector<double> widthRatios = {
        0.10,  // CODE
        0.12,  // NOM
        0.15,  // EMAIL
        0.08,  // TEL
        0.12,  // DOMAINE
        0.15,  // ADRESSE
        0.08,  // ANNEE
        0.10,  // TYPE
        0.10   // CAPACITE
    };

    int totalWidth = pdfWriter.width() - 2*margin;
    QVector<int> columnWidths(columnNames.size());

    // Calculate pixel widths based on percentages
    for (int i = 0; i < columnNames.size(); ++i) {
        columnWidths[i] = static_cast<int>(totalWidth * widthRatios[i]);
    }

    // Adjust row height for better readability
    int rowHeight = 25;

    // Draw table header with background
    QColor headerColor(220, 220, 220);
    painter.fillRect(margin, yPosition, totalWidth, rowHeight, headerColor);

    // Draw column headers
    painter.setFont(headerFont);
    int xPosition = margin;
    for (int i = 0; i < columnNames.size(); ++i) {
        QRect headerRect(xPosition, yPosition, columnWidths[i], rowHeight);
        painter.drawRect(headerRect);
        painter.drawText(headerRect, Qt::AlignCenter, columnNames[i]);
        xPosition += columnWidths[i];
    }

    yPosition += rowHeight;

    // Draw table data
    painter.setFont(dataFont);
    int rowCount = ui->data->rowCount();
    int colCount = qMin(ui->data->columnCount(), columnNames.size());

    for (int row = 0; row < rowCount; ++row) {
        // Alternate row colors
        if (row % 2 == 0) {
            painter.fillRect(margin, yPosition, totalWidth, rowHeight, QColor(245, 245, 245));
        }

        xPosition = margin;
        for (int col = 0; col < colCount; ++col) {
            QTableWidgetItem *item = ui->data->item(row, col);
            QString cellText = item ? item->text() : "";

            // Truncate long text
            if (cellText.length() > 30) {
                cellText = cellText.left(27) + "...";
            }

            QRect cellRect(xPosition, yPosition, columnWidths[col], rowHeight);
            painter.drawRect(cellRect);

            // Use different alignment based on column type
            Qt::Alignment alignment;
            if (col == 0 || col == 3 || col == 6 || col == 8) {  // Code, Tel, Annee, Capacite
                alignment = Qt::AlignCenter;
            } else {
                alignment = Qt::AlignLeft | Qt::AlignVCenter;
            }

            // Add padding for text
            QRect textRect = cellRect.adjusted(3, 0, -3, 0);
            painter.drawText(textRect, alignment, cellText);

            xPosition += columnWidths[col];
        }

        yPosition += rowHeight;

        // Check if we need a new page
        if (yPosition > pdfWriter.height() - margin && row < rowCount - 1) {
            painter.end();
            pdfWriter.newPage();
            painter.begin(&pdfWriter);

            // Add page header
            yPosition = margin;
            painter.setFont(titleFont);
            painter.drawText(QRect(margin, yPosition, pdfWriter.width() - 2*margin, 30),
                             Qt::AlignHCenter | Qt::AlignTop, "Liste des Sponsors (Suite)");

            yPosition += 40;

            // Redraw table header
            painter.setFont(headerFont);
            painter.fillRect(margin, yPosition, totalWidth, rowHeight, headerColor);

            xPosition = margin;
            for (int i = 0; i < columnNames.size(); ++i) {
                QRect headerRect(xPosition, yPosition, columnWidths[i], rowHeight);
                painter.drawRect(headerRect);
                painter.drawText(headerRect, Qt::AlignCenter, columnNames[i]);
                xPosition += columnWidths[i];
            }

            yPosition += rowHeight;
            painter.setFont(dataFont);
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "Le fichier PDF a été enregistré avec succès.");
}

void MainWindow::updateDomainStatistics() {
    int totalSponsors = Sponsor::getTotalCount();
    if (totalSponsors == 0) {
        QMessageBox::warning(this, "Statistiques", "Aucun sponsor dans la base de données.");
        return;
    }

    // Mapping des vrais noms de domaines à leurs barres de progression
    QMap<QString, QProgressBar*> domainToProgressBar = {
        {"Technology", ui->tech},
        {"Finance", ui->finance},
        {"Health", ui->health},
        {"Retail & E-commerce", ui->retail},
        {"Education & Training", ui->education},
        {"Media & Entertainement", ui->media},
        {"Automotive", ui->automative},
        {"Food", ui->food},
        {"Real Estate", ui->real},
        {"Other", ui->other}
    };

    for (auto it = domainToProgressBar.begin(); it != domainToProgressBar.end(); ++it) {
        QString domain = it.key();
        QProgressBar* progressBar = it.value();

        int count = Sponsor::getDomainCount(domain);
        int percentage = (count * 100) / totalSponsors;

        if (progressBar) {
            progressBar->setValue(percentage);
            progressBar->setFormat(QString("%1: %p%").arg(domain));
        }
    }

    QMessageBox::information(this, "Succès", "Statistiques mises à jour avec succès.");
}
