#include "nour.h"
#include "ui_nour.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QRegularExpression>
#include <QSqlError>
#include "client.h"
#include <QPrinter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QGroupBox>
#include <QScrollArea>
#include <QTableWidget>
#include <QHeaderView>
#include <QFileDialog>
#include <QStandardPaths>
#include <QProcess>
#include <QLabel>
#include <QMovie>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>


extern const QMap<QString, QString> diplomaMap;
extern const QMap<QString, QString> domainMap;
extern const QMap<QString, QString> skillsMap;


Nour::Nour(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Nour)
{
    qDebug() << "👉 Nour constructor called"; // ✅ Step 1
    ui->setupUi(this);
    qDebug() << "✅ Nour UI setup complete"; // ✅ Step 2

    displayClients(); // Might crash → we’ll check it
    qDebug() << "✅ Clients displayed";      // ✅ Step 3

    /*showClientsByDiplomeChart();
    showClientsByDomaineChart();
    showClientsByAgeGroupChart();*/
    qDebug() << "✅ Statistics displayed";   // ✅ Step 4
    this->setFocusPolicy(Qt::StrongFocus);
    setFocusPolicy(Qt::StrongFocus);         // Make window focusable
    setFocus();                              // Grab initial focus
    QMovie* movie = new QMovie("C:/Cpp/build/spinner.gif"); // or full path like "C:/.../spinner.gif"
    movie->setScaledSize(QSize(32, 32));
    ui->spinner->setFixedSize(32, 32);
    ui->spinner->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->spinner->setMovie(movie);
    movie->start();
    ui->spinner->setVisible(false);
    //galleryLayout = new QGridLayout(ui->logoScrollArea->widget());
    //loadGallery();

    // Populate ComboBoxes with options in English
    ui->diplomaCombo->addItems({"Technician", "Master", "Engineer"});
    ui->domainCombo->addItems({"Software Engineering", "Embedded Systems", "Data Science", "Business Intelligence"});

    ui->skillsListWidget->addItems({
        "Digital Marketing",
        "Multimedia Design",
        "C/C++",
        "Python",
        "Frontend",
        "Backend",
        "Full Stack MERN",
        "Full Stack JS",
        "Mobile",
        "Security"
    });

    ui->skillsListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->pdfPathEdit->setPlaceholderText("Select a CV PDF...");

    connect(ui->searchButton, &QPushButton::clicked, this, &Nour::on_pushButton_search_clicked);
    connect(ui->addButton, &QPushButton::clicked, this, &Nour::on_pushButton_add_clicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &Nour::on_pushButton_delete_clicked);
    connect(ui->updateButton, &QPushButton::clicked, this, &Nour::on_pushButton_update_clicked);
    connect(ui->clientsTable, &QTableWidget::itemSelectionChanged, this, &Nour::on_clientsTable_itemSelectionChanged);
    connect(ui->pushButton_exportPDF, &QPushButton::clicked, this, &Nour::on_pushButton_exportPDF_clicked);
    /*
    connect(ui->pushButton_generate, &QPushButton::clicked, this, &Nour::generateLogo);
    connect(ui->btnRegenerate, &QPushButton::clicked, this, &Nour::onRegenerateClicked);*/

    connect(ui->comboBox_sort, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Nour::on_comboBox_sort_currentIndexChanged);


    /////
    /*connect(ui->extractSkillsButton, &QPushButton::clicked,
            this, &Nour::on_extractSkillsButton_clicked);*/
    /*connect(ui->browsePdfButton, &QPushButton::clicked,
            this, &Nour::on_browsePdfButton_clicked);*/
    displayClients();

    showClientsByDiplomeChart();
    showClientsByDomaineChart();
    showClientsByAgeGroupChart();
    /*
    int ret = A.connect_arduino();  // connect to Arduino
    switch(ret){
    case 0: qDebug() << "Arduino connected on:" << A.getarduino_port_name(); break;
    case 1: qDebug() << "Arduino port found but not opened"; break;
    case -1: qDebug() << "Arduino not available"; break;
    }
    QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(updateArduinoStatus()));*/

}
Nour::~Nour()
{
    delete ui;
}

bool Nour::validateClientForm()
{
    if (ui->firstNameLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "First name cannot be empty.");
        ui->firstNameLineEdit->setFocus();
        return false;
    }

    if (ui->lastNameLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Last name cannot be empty.");
        ui->lastNameLineEdit->setFocus();
        return false;
    }

    if (ui->emailLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Email cannot be empty.");
        ui->emailLineEdit->setFocus();
        return false;
    }

    if (ui->addressEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Address cannot be empty.");
        ui->addressEdit->setFocus();
        return false;
    }

    if (ui->phoneEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Phone number cannot be empty.");
        ui->phoneEdit->setFocus();
        return false;
    }

    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    QRegularExpressionMatch match = emailRegex.match(ui->emailLineEdit->text().trimmed());
    if (!match.hasMatch()) {
        QMessageBox::warning(this, "Validation Error", "Invalid email format.");
        ui->emailLineEdit->setFocus();
        return false;
    }

    QDate currentDate = QDate::currentDate();
    QDate birthDate = ui->dateOfBirthEdit->date();

    if (birthDate > currentDate) {
        QMessageBox::warning(this, "Validation Error", "Date of birth cannot be in the future.");
        ui->dateOfBirthEdit->setFocus();
        return false;
    }

    int age = birthDate.daysTo(currentDate) / 365;
    if (age < 18) {
        QMessageBox::warning(this, "Validation Error", "Client must be at least 18 years old.");
        ui->dateOfBirthEdit->setFocus();
        return false;
    }

    QString phoneNumber = ui->phoneEdit->text().trimmed();
    QString digitsOnly = phoneNumber;
    digitsOnly.remove(QRegularExpression("[^0-9]"));

    if (digitsOnly.length() < 8) {
        QMessageBox::warning(this, "Validation Error", "Phone number must have at least 8 digits.");
        ui->phoneEdit->setFocus();
        return false;
    }

    /*if (ui->skillsListWidget->selectedItems().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please select at least one skill.");
        ui->skillsListWidget->setFocus();
        return false;
    }*/

    return true;
}

void Nour::on_pushButton_add_clicked()
{
    if (!validateClientForm()) {
        return; // Exit if validation fails
    }

    QString firstName = ui->firstNameLineEdit->text();
    QString lastName = ui->lastNameLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QDate dateOfBirth = ui->dateOfBirthEdit->date();
    QString address = ui->addressEdit->text();
    QString phone = ui->phoneEdit->text();
    QString diploma = ui->diplomaCombo->currentText();
    QString domain = ui->domainCombo->currentText();

    QStringList selectedSkills;
    for (QListWidgetItem* item : ui->skillsListWidget->selectedItems()) {
        selectedSkills.append(item->text());
    }

    QStringList extractedSkills = ui->skillsEdit->toPlainText().split(",", Qt::SkipEmptyParts);
    for (QString& skill : extractedSkills) {
        skill = skill.trimmed();
    }

    QStringList finalSkills = selectedSkills + extractedSkills;
    finalSkills.removeDuplicates(); // optional

    Client newClient(firstName, lastName, email, dateOfBirth, address, phone, diploma, domain, finalSkills);

    if (newClient.addClient()) {
        QMessageBox::information(this, "Success", "Client added successfully!");
        clearInputFields();
        displayClients(); // Refresh the table
    } else {
        QMessageBox::warning(this, "Error", "Failed to add client.");
    }
}

void Nour::on_pushButton_update_clicked()
{
    QModelIndex index = ui->clientsTable->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a client to update.");
        return;
    }

    // Get the selected client's ID from the first column
    int idClient = ui->clientsTable->model()->index(index.row(), 0).data().toInt();

    // Get updated values from the input fields
    QString firstName = ui->firstNameLineEdit->text();
    QString lastName = ui->lastNameLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QDate dateOfBirth = ui->dateOfBirthEdit->date();
    QString address = ui->addressEdit->text();
    QString phone = ui->phoneEdit->text();
    QString diploma = ui->diplomaCombo->currentText();
    QString domain = ui->domainCombo->currentText();

    QStringList skills;
    for (QListWidgetItem* item : ui->skillsListWidget->selectedItems()) {
        skills.append(item->text());
    }

    // Validate the form
    if (!validateClientForm()) {
        return;
    }

    // Update the client
    Client client;
    if (client.updateClient(idClient, firstName, lastName, email, dateOfBirth, address, phone, diploma, domain, skills)) {
        QMessageBox::information(this, "Success", "Client updated successfully!");
        displayClients(); // Refresh the table
    } else {
        QMessageBox::warning(this, "Error", "Failed to update client.");
    }
}
void Nour::on_pushButton_delete_clicked()
{
    QModelIndex index = ui->clientsTable->currentIndex();
    if (index.isValid()) {
        int idClient = ui->clientsTable->model()->index(index.row(), 0).data().toInt(); // Get ID from first column
        Client client;
        if (client.deleteClient(idClient)) {
            QMessageBox::information(this, "Success", "Client deleted successfully!");
            displayClients(); // Refresh the table
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete client.");
        }
    } else {
        QMessageBox::warning(this, "Selection Error", "Please select a client to delete.");
    }
}

void Nour::clearInputFields()
{
    ui->firstNameLineEdit->clear();
    ui->lastNameLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->addressEdit->clear();
    ui->phoneEdit->clear();
    ui->dateOfBirthEdit->setDate(QDate(2000, 1, 1)); // Reset to default date
    ui->diplomaCombo->setCurrentIndex(0); // Reset ComboBox
    ui->domainCombo->setCurrentIndex(0); // Reset ComboBox
    ui->skillsListWidget->clearSelection(); // Reset List Widget
    ui->searchEdit->clear(); // Clear search box
}

void Nour::displayClients()
{
    if (!ui || !ui->clientsTable) {
        qDebug() << "⚠️ clientsTable is not ready";
        return;
    }

    Client client;
    QList<Client> clients = client.getAllClients(); // Fetch data

    // Get current sort selection
    int sortIndex = ui->comboBox_sort->currentIndex();

    // Sort based on selection
    switch(sortIndex) {
    case 0: // ID Ascending
        std::sort(clients.begin(), clients.end(), [](const Client &a, const Client &b) {
            return a.getIdClient() < b.getIdClient();
        });
        break;
    case 1: // ID Descending
        std::sort(clients.begin(), clients.end(), [](const Client &a, const Client &b) {
            return a.getIdClient() > b.getIdClient();
        });
        break;
    // Other cases remain unchanged
    default:
        break;
    }

    ui->clientsTable->setRowCount(0); // Clear existing data
    for (const Client &client : clients) {
        int rowCount = ui->clientsTable->rowCount();
        ui->clientsTable->insertRow(rowCount); // Add a new row

        // Populate the table with client data
        ui->clientsTable->setItem(rowCount, 0, new QTableWidgetItem(QString::number(client.getIdClient()))); // ID
        ui->clientsTable->setItem(rowCount, 1, new QTableWidgetItem(client.getFirstName())); // First Name
        ui->clientsTable->setItem(rowCount, 2, new QTableWidgetItem(client.getLastName())); // Last Name
        ui->clientsTable->setItem(rowCount, 3, new QTableWidgetItem(client.getEmail())); // Email
        ui->clientsTable->setItem(rowCount, 4, new QTableWidgetItem(client.getDateOfBirth().toString("yyyy-MM-dd"))); // Date of Birth
        ui->clientsTable->setItem(rowCount, 5, new QTableWidgetItem(client.getAddress())); // Address
        ui->clientsTable->setItem(rowCount, 6, new QTableWidgetItem(client.getPhone())); // Phone Number

        // Handle empty values for Diploma, Domain, and Skills
        QString diploma = client.getDiploma().isEmpty() ? "null" : client.getDiploma();
        QString domain = client.getDomain().isEmpty() ? "null" : client.getDomain();
        QString skills = client.getSkills().isEmpty() ? "null" : client.getSkills().join(", ");

        ui->clientsTable->setItem(rowCount, 7, new QTableWidgetItem(diploma)); // Degree
        ui->clientsTable->setItem(rowCount, 8, new QTableWidgetItem(domain)); // Field of Study
        ui->clientsTable->setItem(rowCount, 9, new QTableWidgetItem(skills)); // Skills
    }
}

void Nour::on_pushButton_search_clicked()
{
    QString searchText = ui->searchEdit->text();
    Client client;
    QSqlQueryModel* model = client.search(searchText);

    ui->clientsTable->setRowCount(0); // Clear the table

    for (int i = 0; i < model->rowCount(); ++i) {
        ui->clientsTable->insertRow(i);

        // Populate the table with search results
        ui->clientsTable->setItem(i, 0, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
        ui->clientsTable->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 1)).toString()));
        ui->clientsTable->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 2)).toString()));
        ui->clientsTable->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 3)).toString()));
        ui->clientsTable->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 4)).toDate().toString("yyyy-MM-dd")));
        ui->clientsTable->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 5)).toString()));
        ui->clientsTable->setItem(i, 6, new QTableWidgetItem(model->data(model->index(i, 6)).toString()));
        ui->clientsTable->setItem(i, 7, new QTableWidgetItem(model->data(model->index(i, 7)).toString()));
        ui->clientsTable->setItem(i, 8, new QTableWidgetItem(model->data(model->index(i, 8)).toString()));
        ui->clientsTable->setItem(i, 9, new QTableWidgetItem(model->data(model->index(i, 9)).toString()));
    }

    delete model; // Free the memory allocated for the model
}
void Nour::on_clientsTable_itemSelectionChanged()
{
    QModelIndex index = ui->clientsTable->currentIndex();
    if (index.isValid()) {
        // Get the selected client's data
        QString firstName = ui->clientsTable->model()->index(index.row(), 1).data().toString();
        QString lastName = ui->clientsTable->model()->index(index.row(), 2).data().toString();
        QString email = ui->clientsTable->model()->index(index.row(), 3).data().toString();
        QDate dateOfBirth = QDate::fromString(ui->clientsTable->model()->index(index.row(), 4).data().toString(), "yyyy-MM-dd");
        QString address = ui->clientsTable->model()->index(index.row(), 5).data().toString();
        QString phone = ui->clientsTable->model()->index(index.row(), 6).data().toString();
        QString diploma = ui->clientsTable->model()->index(index.row(), 7).data().toString();
        QString domain = ui->clientsTable->model()->index(index.row(), 8).data().toString();
        QString skills = ui->clientsTable->model()->index(index.row(), 9).data().toString();

        // Populate the input fields
        ui->firstNameLineEdit->setText(firstName);
        ui->lastNameLineEdit->setText(lastName);
        ui->emailLineEdit->setText(email);
        ui->dateOfBirthEdit->setDate(dateOfBirth);
        ui->addressEdit->setText(address);
        ui->phoneEdit->setText(phone);
        ui->diplomaCombo->setCurrentText(diploma);
        ui->domainCombo->setCurrentText(domain);

        // Select skills in the list widget
        ui->skillsListWidget->clearSelection();
        QStringList skillsList = skills.split(", ");
        for (int i = 0; i < ui->skillsListWidget->count(); ++i) {
            QListWidgetItem* item = ui->skillsListWidget->item(i);
            if (skillsList.contains(item->text())) {
                item->setSelected(true);
            }
        }
    }
}
void Nour::exportToPDF(const QString &fileName, const QList<Client> &clients)
{
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPageSize::A4);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    QTextDocument doc;

    QString htmlContent = "<html>"
                          "<body>"
                          "<h1>Client List</h1>"
                          "<table border='1' cellspacing='5' width='100%' cellpadding='10'>"
                          "<tr>"
                          "<th>ID</th>"
                          "<th>First Name</th>"
                          "<th>Last Name</th>"
                          "<th>Email</th>"
                          "<th>Date of Birth</th>"
                          "<th>Address</th>"
                          "<th>Phone</th>"
                          "<th>Diploma</th>"
                          "<th>Domain</th>"
                          "<th>Skills</th>"
                          "</tr>";

    for (const auto& client : clients)
    {
        htmlContent += "<tr>"
                       "<td align='center'>" + QString::number(client.getIdClient()) + "</td>"
                                                                 "<td align='center'>" + client.getFirstName() + "</td>"
                                                 "<td align='center'>" + client.getLastName() + "</td>"
                                                "<td align='center'>" + client.getEmail() + "</td>"
                                             "<td align='center'>" + client.getDateOfBirth().toString("dd/MM/yyyy") + "</td>"
                                                                          "<td align='center'>" + client.getAddress() + "</td>"
                                               "<td align='center'>" + client.getPhone() + "</td>"
                                             "<td align='center'>" + client.getDiploma() + "</td>"
                                               "<td align='center'>" + client.getDomain() + "</td>"
                                              "<td align='center'>" + client.getSkills().join(", ") + "</td>"
                                                         "</tr>";
    }

    htmlContent += "</table>"
                   "</body>"
                   "</html>";

    doc.setHtml(htmlContent);
    doc.setPageSize(printer.pageRect(QPrinter::Point).size()); // Fix: Pass QPrinter::Point as the unit
    doc.print(&printer);

    // Open the PDF file after creation
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}
void Nour::on_pushButton_exportPDF_clicked()
{
    Client client;
    QList<Client> clients = client.getAllClients(); // Fetch all clients
    exportToPDF("clients.pdf", clients); // Export to PDF
}
///////
/// charts
void Nour::showClientsByDiplomeChart()
{
    QSqlQuery query;
    QMap<QString, int> diplomaCounts;

    if (!query.exec("SELECT diplome, COUNT(*) FROM client GROUP BY diplome")) {
        qDebug() << "Diplome query failed:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        diplomaCounts[query.value(0).toString()] = query.value(1).toInt();
    }

    QBarSet *barSet = new QBarSet("Clients");
    QStringList categories;
    for (auto it = diplomaCounts.begin(); it != diplomaCounts.end(); ++it) {
        categories << it.key();
        *barSet << it.value();
    }

    QBarSeries *series = new QBarSeries();
    series->append(barSet);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par diplôme");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget *container = this->findChild<QWidget *>("chartContainer_4");
    if (!container) return;

    if (container->layout()) delete container->layout();

    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->addWidget(chartView);
}

void Nour::showClientsByDomaineChart()
{
    QSqlQuery query;
    QMap<QString, int> domaineCounts;

    if (!query.exec("SELECT Domaine_Etude, COUNT(*) FROM client GROUP BY Domaine_Etude")) {
        qDebug() << "Domaine query failed:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        domaineCounts[query.value(0).toString()] = query.value(1).toInt();
    }

    QBarSet *barSet = new QBarSet("Clients");
    QStringList categories;
    for (auto it = domaineCounts.begin(); it != domaineCounts.end(); ++it) {
        categories << it.key();
        *barSet << it.value();
    }

    QBarSeries *series = new QBarSeries();
    series->append(barSet);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par domaine d'étude");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget *container = this->findChild<QWidget *>("chartContainer_5");
    if (!container) return;

    if (container->layout()) delete container->layout();

    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->addWidget(chartView);
}
void Nour::showClientsByAgeGroupChart()
{
    QSqlQuery query;
    QMap<QString, int> ageGroups{
        {"≤ 25", 0},
        {"26–35", 0},
        {"36–45", 0},
        {"> 45", 0}
    };

    if (!query.exec("SELECT DATE_NAISSANCE FROM client WHERE DATE_NAISSANCE IS NOT NULL")) {
        qDebug() << "Age group query failed:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QDate birthDate = query.value(0).toDate();
        int age = birthDate.daysTo(QDate::currentDate()) / 365;

        if (age <= 25)
            ageGroups["≤ 25"]++;
        else if (age <= 35)
            ageGroups["26–35"]++;
        else if (age <= 45)
            ageGroups["36–45"]++;
        else
            ageGroups["> 45"]++;
    }

    QPieSeries *series = new QPieSeries();
    for (auto it = ageGroups.begin(); it != ageGroups.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par tranche d’âge");
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget *container = this->findChild<QWidget *>("chartContainer_6");
    if (!container) return;

    if (container->layout()) delete container->layout();

    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->addWidget(chartView);
}

/*
void Nour::showClientsByDiplomeChart()
{
    QSqlQuery query;
    QMap<QString, int> diplomaCounts;

    // Run the query
    if (query.exec("SELECT diplome, COUNT(*) FROM client GROUP BY diplome")) {
        while (query.next()) {
            QString diplome = query.value(0).toString();
            int count = query.value(1).toInt();
            diplomaCounts[diplome] = count;
        }
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    // Create the bar set and fill with actual data
    QBarSet *set = new QBarSet("Clients");
    QStringList categories;

    for (auto it = diplomaCounts.begin(); it != diplomaCounts.end(); ++it) {
        categories << it.key();
        *set << it.value();
    }

    // Build chart same way as before
    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Clients by Diplôme");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget *container = this->findChild<QWidget *>("chartContainer");
    QLayout *oldLayout = container->layout();
    if (oldLayout)
        delete oldLayout;

    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->addWidget(chartView);
}

void Nour::showClientsByDomaineChart()
{
    QSqlQuery query;
    QMap<QString, int> domaineCounts;

    if (query.exec("SELECT Domaine_Etude, COUNT(*) FROM client GROUP BY Domaine_Etude")) {
        while (query.next()) {
            QString domaine = query.value(0).toString();
            int count = query.value(1).toInt();
            domaineCounts[domaine] = count;
        }
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    QBarSet *set = new QBarSet("Clients");
    QStringList categories;

    for (auto it = domaineCounts.begin(); it != domaineCounts.end(); ++it) {
        categories << it.key();
        *set << it.value();
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Clients by Domaine d’Étude");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget *container = this->findChild<QWidget *>("chartContainer_2");
    QLayout *oldLayout = container->layout();
    if (oldLayout)
        delete oldLayout;

    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->addWidget(chartView);
}

void Nour::showClientsByAgeGroupChart()
{
    QSqlQuery query;
    QMap<QString, int> ageGroups;

    // Init all groups to 0
    ageGroups["≤ 25"] = 0;
    ageGroups["26–35"] = 0;
    ageGroups["36–45"] = 0;
    ageGroups["> 45"] = 0;

    if (query.exec("SELECT DATE_NAISSANCE FROM client WHERE DATE_NAISSANCE IS NOT NULL")) {
        while (query.next()) {
            QDate birthDate = query.value(0).toDate();
            int age = birthDate.daysTo(QDate::currentDate()) / 365;

            if (age <= 25)
                ageGroups["≤ 25"]++;
            else if (age <= 35)
                ageGroups["26–35"]++;
            else if (age <= 45)
                ageGroups["36–45"]++;
            else
                ageGroups["> 45"]++;
        }
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    QPieSeries *series = new QPieSeries();
    for (auto it = ageGroups.begin(); it != ageGroups.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Clients by Age Group");
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget *container = this->findChild<QWidget *>("chartContainer_3");
    QLayout *oldLayout = container->layout();
    if (oldLayout)
        delete oldLayout;

    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->addWidget(chartView);
}
*/

/// tri
void Nour::on_comboBox_sort_currentIndexChanged(int index)
{
    // Get all clients
    Client client;
    QList<Client> clients = client.getAllClients();

    // Sort based on selection
    switch(index) {
    case 0: // ID Ascending
        std::sort(clients.begin(), clients.end(), [](const Client &a, const Client &b) {
            return a.getIdClient() < b.getIdClient();
        });
        break;
    case 1: // ID Descending
        std::sort(clients.begin(), clients.end(), [](const Client &a, const Client &b) {
            return a.getIdClient() > b.getIdClient();
        });
        break;
    // Other cases remain unchanged
    default:
        break;
    }

    // Update the table with sorted data
    ui->clientsTable->setRowCount(0);
    for (const Client &client : clients) {
        int rowCount = ui->clientsTable->rowCount();
        ui->clientsTable->insertRow(rowCount);

        ui->clientsTable->setItem(rowCount, 0, new QTableWidgetItem(QString::number(client.getIdClient())));
        ui->clientsTable->setItem(rowCount, 1, new QTableWidgetItem(client.getFirstName()));
        ui->clientsTable->setItem(rowCount, 2, new QTableWidgetItem(client.getLastName()));
        ui->clientsTable->setItem(rowCount, 3, new QTableWidgetItem(client.getEmail()));
        ui->clientsTable->setItem(rowCount, 4, new QTableWidgetItem(client.getDateOfBirth().toString("yyyy-MM-dd")));
        ui->clientsTable->setItem(rowCount, 5, new QTableWidgetItem(client.getAddress()));
        ui->clientsTable->setItem(rowCount, 6, new QTableWidgetItem(client.getPhone()));

        QString diploma = client.getDiploma().isEmpty() ? "null" : client.getDiploma();
        QString domain = client.getDomain().isEmpty() ? "null" : client.getDomain();
        QString skills = client.getSkills().isEmpty() ? "null" : client.getSkills().join(", ");

        ui->clientsTable->setItem(rowCount, 7, new QTableWidgetItem(diploma));
        ui->clientsTable->setItem(rowCount, 8, new QTableWidgetItem(domain));
        ui->clientsTable->setItem(rowCount, 9, new QTableWidgetItem(skills));
    }
}
///
///
///skills
/*
void Nour::on_extractSkillsButton_clicked()
{
    QString pdfPath = ui->pdfPathEdit->text();

    if (pdfPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a PDF file.");
        return;
    }

    // Show the loading bar
    ui->progressBar->setVisible(true);

    ExtractWorker *worker = new ExtractWorker;
    worker->pdfPath = pdfPath;

    QThread *thread = new QThread;
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &ExtractWorker::process);
    connect(worker, &ExtractWorker::finished, this, [=]() {
        thread->quit();
        thread->wait();

        ui->progressBar->setVisible(false);

        if (!worker->error.isEmpty()) {
            QMessageBox::critical(this, "Python Error", worker->error);
        } else {
            ui->skillsEdit->setText(worker->result);
        }

        worker->deleteLater();
        thread->deleteLater();
    });

    thread->start();
}


void Nour::on_browsePdfButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select CV PDF", "", "PDF Files (*.pdf)");
    if (!fileName.isEmpty()) {
        ui->pdfPathEdit->setText(fileName);
    }
}
*/
/////
///  logo
/*
void Nour::generateLogo() {
    QString name = ui->lineEdit_name->text();
    QString industry = ui->lineEdit_industry->text();
    QString style = ui->comboBox_style->currentText();
    QString symbol = ui->lineEdit_symbol->text();
    QString color = ui->colorEdit->text();
    QString font = ui->fontEdit->text();

    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString outputDir = QCoreApplication::applicationDirPath() + "/generated_logos";
    QDir().mkpath(outputDir);
    QString logoPath = outputDir + "/" + name + "_" + timestamp + ".png";

    qDebug() << "Logo will be saved to:" << logoPath;


    ui->spinner->show();

    QProcess *process = new QProcess(this);
    QString pythonExe = "C:/Python312/python.exe";  // or wherever your working Python is
    QString scriptPath = "C:/Users/ce pc/Documents/Cpp/generate_logo.py";  // full absolute path

    QStringList args = {
        scriptPath,
        name,
        industry,
        style,
        symbol,
        color,
        font,
        logoPath
    };



    qDebug() << "Starting logo generation...";
    qDebug() << "Python:" << pythonExe;
    qDebug() << "Args:" << args;

    process->setWorkingDirectory("C:/Cpp");  // Same folder as the script

    connect(process, &QProcess::readyReadStandardOutput, [=]() {
        QString output = process->readAllStandardOutput();
        qDebug() << "STDOUT:" << output;
    });

    connect(process, &QProcess::readyReadStandardError, [=]() {
        QString error = process->readAllStandardError();
        qDebug() << "STDERR:" << error;
    });

    connect(process, &QProcess::finished, this, [=](int exitCode) {
        ui->spinner->hide();
        qDebug() << "Process finished with exit code:" << exitCode;

        if (exitCode == 0 && QFile::exists(logoPath)) {
            showGeneratedLogo(logoPath);

            QSqlQuery query;
            query.prepare("INSERT INTO logos (startup, industry, style, icon, color, font, path) "
                          "VALUES (?, ?, ?, ?, ?, ?, ?)");
            query.addBindValue(name);
            query.addBindValue(industry);
            query.addBindValue(style);
            query.addBindValue(symbol);
            query.addBindValue(color);
            query.addBindValue(font);
            query.addBindValue(logoPath);
            query.exec();

            loadGallery();
        } else {
            QMessageBox::critical(this, "Error", "Failed to generate logo.");
        }

        process->deleteLater();
    });

    process->start(pythonExe, args);
}




void Nour::loadGallery() {
    // Clear previous widgets
    QLayoutItem* child;
    while ((child = galleryLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QDir dir(QCoreApplication::applicationDirPath() + "/generated_logos");
    QStringList filters;
    filters << "*.png" << "*.jpg";
    dir.setNameFilters(filters);
    QFileInfoList fileList = dir.entryInfoList(QDir::Files, QDir::Time);

    int row = 0, col = 0;
    for (const QFileInfo& fileInfo : fileList) {
        QLabel* imgLabel = new QLabel;
        QPixmap pix(fileInfo.absoluteFilePath());
        imgLabel->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imgLabel->setFixedSize(110, 110);
        imgLabel->setStyleSheet("border: 1px solid gray; padding: 5px;");
        galleryLayout->addWidget(imgLabel, row, col);

        if (++col >= 4) { col = 0; ++row; }
    }

}

void Nour::showGeneratedLogo(const QString& logoPath) {
    QPixmap logo(logoPath);
    if (!logo.isNull()) {
        ui->logoLabel->setPixmap(logo.scaled(ui->logoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        qDebug() << "Failed to load logo:" << logoPath;
        ui->logoLabel->setText("Failed to load logo");
    }
}

void Nour::on_generateButton_clicked() {
    QString name = ui->lineEdit_name->text();
    QString industry = ui->lineEdit_industry->text();
    QString style = ui->comboBox_style->currentText();
    QString symbol = ui->lineEdit_symbol->text();
    QString color = ui->colorEdit->text();
    QString font = ui->fontEdit->text();

    ui->spinner->show();

    QProcess *process = new QProcess(this);
    QString pythonExe = "C:/Python312/python.exe";  // Only define once!
    QStringList arguments = {
        QCoreApplication::applicationDirPath() + "/generate_logo.py",
        name, industry, style, symbol, color, font
    };

    process->setWorkingDirectory(QCoreApplication::applicationDirPath());  // Important!

    process->start(pythonExe, arguments);
    process->waitForFinished();  // Wait for Python to finish

    QString output = process->readAllStandardOutput().trimmed();
    QString error = process->readAllStandardError().trimmed();
    qDebug() << "Python Output:" << output;
    qDebug() << "Python Error:" << error;

    if (output.contains("generated_logos")) {
        showGeneratedLogo(output);
        loadGallery();
    } else {
        QMessageBox::critical(this, "Error", "Failed to generate logo.\n" + error);
    }
}



void Nour::regenerate() {
    QString name = ui->lineEdit_name->text();
    QString industry = ui->lineEdit_industry->text();
    QString style = ui->comboBox_style->currentText();
    QString symbol = ui->lineEdit_symbol->text();
    QString color = ui->colorEdit->text();
    QString font = ui->fontEdit->text();

    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString outputDir = "C:/Cpp/generated_logos";
    QDir().mkpath(outputDir);
    QString logoPath = outputDir + "/" + name + "_" + timestamp + ".png";

    QProcess *process = new QProcess(this);
    QString pythonExe = "C:/Python312/python.exe";
    QString scriptPath = "C:/Cpp/generate_logo.py";

    QStringList args = {
        scriptPath,
        name,
        industry,
        style,
        symbol,
        color,
        font,
        logoPath
    };

    ui->spinner->show();

    connect(process, &QProcess::readyReadStandardOutput, [=]() {
        QString output = process->readAllStandardOutput();
        qDebug() << "STDOUT:" << output;
    });

    connect(process, &QProcess::readyReadStandardError, [=]() {
        QString error = process->readAllStandardError();
        qDebug() << "STDERR:" << error;
    });

    connect(process, &QProcess::finished, this, [=](int exitCode) {
        ui->spinner->hide();
        if (exitCode == 0 && QFile::exists(logoPath)) {
            showGeneratedLogo(logoPath);

            QSqlQuery query;
            query.prepare("INSERT INTO logos (startup, industry, style, icon, color, font, path) "
                          "VALUES (?, ?, ?, ?, ?, ?, ?)");
            query.addBindValue(name);
            query.addBindValue(industry);
            query.addBindValue(style);
            query.addBindValue(symbol);
            query.addBindValue(color);
            query.addBindValue(font);
            query.addBindValue(logoPath);
            query.exec();


            loadGallery();
        } else {
            QMessageBox::critical(this, "Error", "Failed to regenerate logo.");
        }

        process->deleteLater();
    });

    process->start(pythonExe, args);
}



void Nour::onRegenerateClicked() {
    QString name = ui->lineEdit_name->text();
    QString industry = ui->lineEdit_industry->text();
    QString style = ui->comboBox_style->currentText();
    QString symbol = ui->lineEdit_symbol->text();
    QString color = ui->colorEdit->text();
    QString font = ui->fontEdit->text();

    if (name.isEmpty() || industry.isEmpty() || style.isEmpty() || symbol.isEmpty() || color.isEmpty()) {
        QMessageBox::warning(this, "Missing Data", "Please fill in all the fields.");
        return;
    }

    regenerate();
}
*/

/// arduino
/*
void Nour::updateArduinoStatus()
{
    data = A.read_from_arduino();

    if (data.contains("ARRIVED")) {
        log("🟢 Arduino button triggered ARRIVED");

        // 1. Mark current client as 'arrived'
        if (currentGuidingClientId != -1) {
            QSqlQuery update;
            update.prepare("UPDATE CLIENT SET POSITION = 'arrived' WHERE ID_CLIENT = :id");
            update.bindValue(":id", currentGuidingClientId);
            if (update.exec()) {
                log(QString("✅ Client %1 marked as arrived.").arg(currentGuidingClientId));
                ui->guidingNameLabel->clear();
                ui->guidingPositionLabel->clear();
                currentGuidingClientId = -1;
            } else {
                log("❌ Failed to mark client as arrived: " + update.lastError().text());
            }
        } else {
            log("⚠️ No client was being guided — skipping arrival update.");
        }

        // 2. Assign next client — only if available
        QSqlQuery query;
        query.prepare("SELECT ID_CLIENT FROM (SELECT * FROM CLIENT WHERE POSITION = 'waiting' ORDER BY ID_CLIENT ASC) WHERE ROWNUM = 1");
        if (query.exec()) {
            if (query.next()) {
                currentGuidingClientId = query.value(0).toInt();
                QSqlQuery update;
                update.prepare("UPDATE CLIENT SET POSITION = 'guiding' WHERE ID_CLIENT = :id");
                update.bindValue(":id", currentGuidingClientId);
                if (update.exec()) {
                    log(QString("🚶 Client %1 is now guiding").arg(currentGuidingClientId));
                    showCurrentGuidingClient(currentGuidingClientId);
                } else {
                    log("❌ Failed to set new client to guiding: " + update.lastError().text());
                }
            } else {
                log("⚠️ No more waiting clients.");
                currentGuidingClientId = -1;  // Ensure no client is active
            }
        } else {
            log("❌ Query failed: " + query.lastError().text());
        }
    }
}

void Nour::updateClientPosition(int clientId, const QString& newPosition)
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET POSITION = :pos WHERE ID_CLIENT = :id");
    query.bindValue(":pos", newPosition);
    query.bindValue(":id", clientId);
    if (!query.exec()) {
        qDebug() << "Failed to update position:" << query.lastError().text();
    }
}

int Nour::assignNextClient()
{
    QSqlQuery query;
    if (query.exec("SELECT ID_CLIENT FROM CLIENT WHERE POSITION = 'waiting' ORDER BY ID_CLIENT ASC FETCH FIRST 1 ROWS ONLY")) {
        if (query.next()) {
            int nextClientId = query.value(0).toInt();
            updateClientPosition(nextClientId, "guiding");
            qDebug() << "Assigned robot to client ID:" << nextClientId;
            return nextClientId;
        }
    } else {
        qDebug() << "Failed to fetch next waiting client:" << query.lastError().text();
    }
    return -1;
}

void Nour::log(const QString& message)
{
    QString timestamp = QTime::currentTime().toString("hh:mm:ss");
    ui->logOutput->append("[" + timestamp + "] > " + message);
}
void Nour::showCurrentGuidingClient(int clientId)
{
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM, POSITION FROM CLIENT WHERE ID_CLIENT = :id");
    query.bindValue(":id", clientId);
    if (query.exec() && query.next()) {
        QString nom = query.value(0).toString();
        QString prenom = query.value(1).toString();
        QString position = query.value(2).toString();

        ui->guidingNameLabel->setText(nom + " " + prenom);
        ui->guidingPositionLabel->setText(position);


    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString command;

    // ✅ ENTER key: mark current client as "arrived" and assign next one
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        if (currentGuidingClientId != -1) {
            QSqlQuery update;
            update.prepare("UPDATE CLIENT SET POSITION = 'arrived' WHERE ID_CLIENT = :id");
            update.bindValue(":id", currentGuidingClientId);
            if (update.exec()) {
                log(QString("✅ Client %1 marked as arrived.").arg(currentGuidingClientId));

                // Clear label UI
                ui->guidingNameLabel->clear();
                ui->guidingPositionLabel->clear();

                currentGuidingClientId = -1;
            } else {
                log("❌ Failed to mark client as arrived: " + update.lastError().text());
            }
        }

        // 👉 Assign the next waiting client
        QSqlQuery query;
        query.prepare("SELECT ID_CLIENT FROM (SELECT * FROM CLIENT WHERE POSITION = 'waiting' ORDER BY ID_CLIENT ASC) WHERE ROWNUM = 1");
        if (query.exec() && query.next()) {
            currentGuidingClientId = query.value(0).toInt();
            QSqlQuery update;
            update.prepare("UPDATE CLIENT SET POSITION = 'guiding' WHERE ID_CLIENT = :id");
            update.bindValue(":id", currentGuidingClientId);
            if (update.exec()) {
                log(QString("🚶 Client %1 is now guiding").arg(currentGuidingClientId));
                showCurrentGuidingClient(currentGuidingClientId); // ✅ Update label UI
            }
        } else {
            log("⚠️ No more waiting clients.");
        }

        return; // Stop here if ENTER key
    }

    // ✅ Movement keys
    switch (event->key()) {
    case Qt::Key_Up:    command = "G"; break;
    case Qt::Key_Down:  command = "B"; break;
    case Qt::Key_Left:  command = "L"; break;
    case Qt::Key_Right: command = "R"; break;
    case Qt::Key_Space: command = "S"; break;
    default:
        QMainWindow::keyPressEvent(event);
        return;
    }

    // ✅ Assign a client to guide (only once)
    if (currentGuidingClientId == -1) {
        QSqlQuery query;
        query.prepare("SELECT ID_CLIENT FROM (SELECT * FROM CLIENT WHERE POSITION = 'waiting' ORDER BY ID_CLIENT ASC) WHERE ROWNUM = 1");
        if (query.exec() && query.next()) {
            currentGuidingClientId = query.value(0).toInt();
            QSqlQuery update;
            update.prepare("UPDATE CLIENT SET POSITION = 'guiding' WHERE ID_CLIENT = :id");
            update.bindValue(":id", currentGuidingClientId);
            if (update.exec()) {
                log(QString("🟢 Client %1 set to guiding").arg(currentGuidingClientId));
                showCurrentGuidingClient(currentGuidingClientId); // ✅ Update label UI
            }
        } else {
            log("⚠️ No waiting client found.");
        }
    }

    // ✅ Send movement command to Arduino
    A.write_to_arduino(command.toUtf8());
    log("➡️ Command sent: " + command);
}
*/
