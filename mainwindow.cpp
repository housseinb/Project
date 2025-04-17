#include "mainwindow.h"
#include "ui_mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMovie* movie = new QMovie("C:/Cpp/build/spinner.gif"); // or full path like "C:/.../spinner.gif"
    movie->setScaledSize(QSize(32, 32));
    ui->spinner->setFixedSize(32, 32);
    ui->spinner->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->spinner->setMovie(movie);
    movie->start();
    ui->spinner->setVisible(false);
    galleryLayout = new QGridLayout(ui->logoScrollArea->widget());
    loadGallery();

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

    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_search_clicked);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_add_clicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_delete_clicked);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_update_clicked);
    connect(ui->clientsTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::on_clientsTable_itemSelectionChanged);
    connect(ui->pushButton_exportPDF, &QPushButton::clicked, this, &MainWindow::on_pushButton_exportPDF_clicked);
    connect(ui->pushButton_generate, &QPushButton::clicked, this, &MainWindow::generateLogo);
    connect(ui->btnRegenerate, &QPushButton::clicked, this, &MainWindow::onRegenerateClicked);




    /////
    connect(ui->extractSkillsButton, &QPushButton::clicked,
            this, &MainWindow::on_extractSkillsButton_clicked);
    connect(ui->browsePdfButton, &QPushButton::clicked,
            this, &MainWindow::on_browsePdfButton_clicked);
    displayClients();

    showClientsByDiplomeChart();
    showClientsByDomaineChart();
    showClientsByAgeGroupChart();

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::validateClientForm()
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

void MainWindow::on_pushButton_add_clicked()
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
void MainWindow::on_pushButton_update_clicked()
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
void MainWindow::on_pushButton_delete_clicked()
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

void MainWindow::clearInputFields()
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

void MainWindow::displayClients()
{
    Client client;
    QList<Client> clients = client.getAllClients(); // Fetch data

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
void MainWindow::on_pushButton_search_clicked()
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
void MainWindow::on_clientsTable_itemSelectionChanged()
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
void MainWindow::exportToPDF(const QString &fileName, const QList<Client> &clients)
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
void MainWindow::on_pushButton_exportPDF_clicked()
{
    Client client;
    QList<Client> clients = client.getAllClients(); // Fetch all clients
    exportToPDF("clients.pdf", clients); // Export to PDF
}
///////
/// \brief MainWindow::on_browsePdfButton_clicked
///
///
/