#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->update->setVisible(false);
    ui->tableView->setModel(r.afficher());
    QPixmap pm("C:/Users/ce pc/Documents/Cpp/image4.png");
    ui->img->setPixmap(pm);
    ui->img->setScaledContents(true);
    QPixmap pm2("C:/Users/ce pc/Documents/Cpp/image5.png");
    ui->img2->setPixmap(pm2);
    ui->img2->setScaledContents(true);
    // contrôle des entrées
    ui->Phone->setValidator(new QIntValidator(0, 999999, this));//controle de saisie
    // Champs de texte
    QRegularExpression rx("[a-zA-Z]+");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->Name->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}
// ajouter
void MainWindow::on_pushButton_8_clicked()
{
    QString Name = ui->Name->text().trimmed();
    QString Email = ui->Email->text().trimmed();
    QString Date = ui->Date->text().trimmed();
    int Phone = ui->Phone->text().toUInt();
    QString Time = ui->Time->text().trimmed();
    if (Name.isEmpty() || Phone == 0|| Email.isEmpty() || Date.isEmpty() || Time.isEmpty() ) {
        QMessageBox::warning(this, "Champ vide", "Veuillez remplir tous les champs avant d'ajouter.");
        return;
    }
    // Vérification du format de l'heure (00h00)
    QRegularExpression timeFormat(R"(^([01]\d|2[0-3])h[0-5]\d$)"); // Format HHhMM
    if (!timeFormat.match(Time).hasMatch()) {
        QMessageBox::warning(this, "Format invalide", "L'heure doit être au format 00h00 !");
        return;
    }
    // Vérification du format de l'email
    QRegularExpression emailFormat(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!emailFormat.match(Email).hasMatch()) {
        QMessageBox::warning(this, "Email invalide", "Veuillez entrer une adresse email valide !");
        return;
    }
    QDate selectedDate = ui->Date->date(); // Récupération de la date sélectionnée
    // Vérification que la date est future
    QDate today = QDate::currentDate();
    if (selectedDate <= today) {
        QMessageBox::warning(this, "Date invalide", "La date doit être supérieure à aujourd'hui !");
        return;
    }
    RendezVous r(0,0,"",Name,Phone,Email,Date,Time);
    bool test = r.ajouter();
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Rendez-vous ajouté\nClick to cancel"), QMessageBox::Cancel);
        ui->Name->clear();
        ui->Phone->clear();
        ui->Email->clear();
        ui->Date->clear();
        ui->Time->clear();
        ui->tableView->setModel(r.afficher());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"), QObject::tr("Ajout non effectué"), QMessageBox::Cancel);
    }
}
// supprimer
void MainWindow::on_pushButton_9_clicked()
{
    int id = this->id;
    if (id == 0) {
        QMessageBox::warning(this, "Champ vide", "Veuillez entrer un ID valide.");
        return;
    }

    bool test = r.supprimer(id);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Rendez-vous supprimé\nClick to cancel"), QMessageBox::Cancel);
        ui->Name->clear();
        ui->Phone->clear();
        ui->Email->clear();
        ui->Date->clear();
        ui->Time->clear();
        ui->tableView->setModel(r.afficher());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("Suppression non effectuée"), QMessageBox::Cancel);
    }
}
// tab view
void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM rendezvous WHERE id_rdv =" + val);

    if (qry.exec()) {
        while (qry.next()) {
            this->id=(qry.value(0).toInt());
            ui->Name->setText(qry.value(3).toString());
            ui->Phone->setText(qry.value(4).toString());
            ui->Email->setText(qry.value(5).toString());
            ui->Date->setDate(qry.value(6).toDate());
            ui->Time->setText(qry.value(7).toString());
        }
    }
}
// update
void MainWindow::on_pushButton_10_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->update->setVisible(true);
    ui->pushButton_8->setVisible(false);
}
void MainWindow::on_update_clicked()
{
    QString Name = ui->Name->text().trimmed();
    QString Email = ui->Email->text().trimmed();
    QString Date = ui->Date->text().trimmed();
    int Phone = ui->Phone->text().toUInt();
    QString Time = ui->Time->text().trimmed();
    // Vérification du format de l'heure (00h00)
    QRegularExpression timeFormat(R"(^([01]\d|2[0-3])h[0-5]\d$)"); // Format HHhMM
    if (!timeFormat.match(Time).hasMatch()) {
        QMessageBox::warning(this, "Format invalide", "L'heure doit être au format 00h00 !");
        return;
    }
    // Vérification du format de l'email
    QRegularExpression emailFormat(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!emailFormat.match(Email).hasMatch()) {
        QMessageBox::warning(this, "Email invalide", "Veuillez entrer une adresse email valide !");
        return;
    }
    QDate selectedDate = ui->Date->date(); // Récupération de la date sélectionnée
    // Vérification que la date est future
    QDate today = QDate::currentDate();
    if (selectedDate <= today) {
        QMessageBox::warning(this, "Date invalide", "La date doit être supérieure à aujourd'hui !");
        return;
    }
    if (Name.isEmpty() || Phone == 0|| Email.isEmpty() || Date.isEmpty() || Time.isEmpty() ) {
        QMessageBox::warning(this, "Champ vide", "Veuillez remplir tous les champs avant d'ajouter.");
        return;
    }

    bool test = r.modifier(id,0,"",Name,Phone,Email,Date,Time);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Rendez-vous modifié\nClick to cancel"), QMessageBox::Cancel);
        ui->Name->clear();
        ui->Phone->clear();
        ui->Email->clear();
        ui->Date->clear();
        ui->Time->clear();
        ui->tableView->setModel(r.afficher());
        ui->tabWidget->setCurrentIndex(1);
        ui->update->setVisible(false);
        ui->pushButton_8->setVisible(true);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"), QObject::tr("Ajout non effectué"), QMessageBox::Cancel);
    }
}
