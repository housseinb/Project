#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    displayClients(); // Display clients when the main window is created

    // Populate ComboBoxes with options
    ui->diplomaCombo->addItems({"Technician", "Master", "Engineer"});
    ui->domainCombo->addItems({"Software Engineering", "Embedded Systems", "Data Science", "Business Intelligence"});

    // Populate skills List Widget
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

    // Set selection mode to allow multiple selections
    ui->skillsListWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    // Connect buttons
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_search_clicked);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_add_clicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_delete_clicked);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_update_clicked); // Add the update button connection
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_add_clicked()
{
    QString firstName = ui->firstNameLineEdit->text();
    QString lastName = ui->lastNameLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QDate dateOfBirth = ui->dateOfBirthEdit->date();
    QString address = ui->addressEdit->text();
    QString phone = ui->phoneEdit->text();
    QString diploma = ui->diplomaCombo->currentText();
    QString domain = ui->domainCombo->currentText();

    // Get selected skills
    QStringList skills;
    for (QListWidgetItem* item : ui->skillsListWidget->selectedItems()) {
        skills.append(item->text());
    }

    Client newClient(firstName, lastName, email, dateOfBirth, address, phone, diploma, domain, skills);

    if (newClient.addClient()) {
        QMessageBox::information(this, "Success", "Client added successfully!");
        clearInputFields();
        displayClients(); // Refresh the table
    } else {
        QMessageBox::warning(this, "Error", "Failed to add client.");
    }
}

void MainWindow::on_pushButton_delete_clicked()
{
    QModelIndex index = ui->clientsTable->currentIndex();
    if (index.isValid()) {
        int idClient = index.data(0).toInt(); // Assuming the ID is in the first column
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

void MainWindow::on_pushButton_update_clicked()
{
    QModelIndex index = ui->clientsTable->currentIndex();
    if (index.isValid()) {
        int idClient = index.data(0).toInt(); // Assuming the ID is in the first column
        QString firstName = ui->firstNameLineEdit->text();
        QString lastName = ui->lastNameLineEdit->text();
        QString email = ui->emailLineEdit->text();
        QDate dateOfBirth = ui->dateOfBirthEdit->date();
        QString address = ui->addressEdit->text();
        QString phone = ui->phoneEdit->text();
        QString diploma = ui->diplomaCombo->currentText();
        QString domain = ui->domainCombo->currentText();

        // Get selected skills
        QStringList skills;
        for (QListWidgetItem* item : ui->skillsListWidget->selectedItems()) {
            skills.append(item->text());
        }

        Client updatedClient(idClient, firstName, lastName, email, dateOfBirth, address, phone, diploma, domain, skills);

        if (updatedClient.addClient()) {
            QMessageBox::information(this, "Success", "Client updated successfully!");
            clearInputFields();
            displayClients(); // Refresh the table
        } else {
            QMessageBox::warning(this, "Error", "Failed to update client.");
        }
    } else {
        QMessageBox::warning(this, "Selection Error", "Please select a client to update.");
    }
}

void MainWindow::clearInputFields()
{
    ui->firstNameLineEdit->clear();
    ui->lastNameLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->addressEdit->clear();
    ui->phoneEdit->clear();
    ui->diplomaCombo->setCurrentIndex(0); // Reset ComboBox
    ui->domainCombo->setCurrentIndex(0); // Reset ComboBox
    ui->skillsListWidget->clearSelection(); // Reset List Widget
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
        ui->clientsTable->setItem(rowCount, 0, new QTableWidgetItem(QString::number(client.getIdClient())));
        ui->clientsTable->setItem(rowCount, 1, new QTableWidgetItem(client.getFirstName()));
        ui->clientsTable->setItem(rowCount, 2, new QTableWidgetItem(client.getLastName()));
        ui->clientsTable->setItem(rowCount, 3, new QTableWidgetItem(client.getEmail()));
        ui->clientsTable->setItem(rowCount, 4, new QTableWidgetItem(client.getDateOfBirth().toString()));
        ui->clientsTable->setItem(rowCount, 5, new QTableWidgetItem(client.getPhone()));
        ui->clientsTable->setItem(rowCount, 6, new QTableWidgetItem(client.getDiploma())); // ComboBox field
        ui->clientsTable->setItem(rowCount, 7, new QTableWidgetItem(client.getDomain())); // ComboBox field
        ui->clientsTable->setItem(rowCount, 8, new QTableWidgetItem(client.getSkills().join(", "))); // Show skills
    }
}

void MainWindow::on_pushButton_search_clicked()
{
    QString searchText = ui->searchEdit->text(); // Assuming you have a QLineEdit named searchEdit
    Client client;
    QSqlQueryModel* model = client.search(searchText); // Implement this method in your Client class

    // Clear the table and populate it with search results
    ui->clientsTable->setRowCount(0);
    for (int i = 0; i < model->rowCount(); ++i) {
        ui->clientsTable->insertRow(i);
        for (int j = 0; j < model->columnCount(); ++j) {
            ui->clientsTable->setItem(i, j, new QTableWidgetItem(model->data(model->index(i, j)).toString()));
        }
    }
}
