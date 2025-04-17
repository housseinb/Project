#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include "connection.h"
#include <QMessageBox>
#include<QSystemTrayIcon>
#include "connection.h"
#include <QFileDialog>
#include <QPainter>
#include <QDate>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtSql/QSqlQueryModel>
#include <QDate>
#include <QMap>
#include <QStringList>
#include <QTextToSpeech>
#include "smtp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    populateComboBox(ui->sponsor);
    markRendezvousOnCalendar(ui->calendarWidget);
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
    //r.
    //ui->sponsor->addItems();
}

MainWindow::~MainWindow()
{
    delete ui;
}
// ajouter
void MainWindow::on_pushButton_8_clicked()
{
    int clientID ;
    clientID = 1;
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
    int fiscal = ui->sponsor->currentText().toInt();

    RendezVous r(0,1,fiscal,Name,Phone,Email,Date,Time);
    bool test = r.ajouter();
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Rendez-vous ajouté\nClick to cancel"), QMessageBox::Cancel);
        sendMail();
        markRendezvousOnCalendar(ui->calendarWidget);
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

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("ranimmahouachi4@gmail.com", "dmfhmqcviljnujaq","smtp.gmail.com",465,30000);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail("Rendez vous", ui->Email->text() , "Confirmation de rendez vous" , "Bonjour cher client, vous avez recu ce mail pour confimer votre rendez-vous du "+ ui->Date->text());
}



void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
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
        markRendezvousOnCalendar(ui->calendarWidget);
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
        markRendezvousOnCalendar(ui->calendarWidget);
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

void MainWindow::on_pushButton_20_clicked()
{
    ui->tableView->setModel( r.trienom());
}


void MainWindow::on_pushButton_15_clicked()
{
    ui->tableView->setModel(r.triedate());
}


void MainWindow::on_pushButton_18_clicked()
{
    ui->tableView->setModel(r.trieheure());
}


void MainWindow::on_Search_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM rendezvous WHERE ID_RDV  LIKE'"+arg1+"%' or NOM  LIKE'"+arg1+"%' or EMAIL  LIKE'"+arg1+"%' or NUM_TEL LIKE'"+arg1+"%'");
    query->exec();
    if (query->next()) {
        model->setQuery(*query);
        ui->tableView->setModel(model);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                              QObject::tr("NO MATCH FOUND !!\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        ui->Search->clear();}
}


void MainWindow::on_pushButton_11_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/logo.png"));
    painter.drawText(900,650,"");
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000,1400,"Liste des rendez vous");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
    painter.drawRect(100,3000,9400,500);
    painter.setFont(QFont("Time New Roman", 9));
    painter.drawText(300,3300,"ID");
    painter.drawText(2000,3300,"EMAIL");
    painter.drawText(4000,3300,"NOM");
    painter.drawText(5600,3300,"DATE RDV");
    painter.drawText(7000,3300,"HEURE RDV");
    painter.drawRect(100,3000,9400,10700);
    QTextDocument previewDoc;
    QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
    QTextCursor cursor(&previewDoc);
    QSqlQuery query;
    query.prepare("select * from RENDEZVOUS");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2000,i,query.value(5).toString());
        painter.drawText(4000,i,query.value(3).toString());
        painter.drawText(5600,i,query.value(6).toString());
        painter.drawText(7000,i,query.value(7).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                        QMessageBox::Yes|QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

        painter.end();
    }
    else
    {
        painter.end();
    }
}

// speech
void MainWindow::on_pushButton_24_clicked()
{
    // Step 1: Retrieve rendezvous data (date_de_reservation)
    QSqlQuery query;
    query.prepare("SELECT date_de_reservation FROM rendezvous ");  // Query to fetch all rendezvous
    if (!query.exec()) {
        qDebug() << "Error fetching rendezvous data:" << query.lastError();
        return;
    }

    // Step 2: Mark the dates on the calendar
    while (query.next()) {
        QString date = query.value(0).toString();  // Get the date of reservation
            QTextToSpeech *speech = new QTextToSpeech();
            speech->say("Vous avez un rendez-vous au " + date);

    }
}
void  MainWindow::markRendezvousOnCalendar(QCalendarWidget *calendar) {
    // Step 1: Retrieve rendezvous data (date_de_reservation)
    QSqlQuery query;
    query.prepare("SELECT date_de_reservation FROM rendezvous ");  // Query to fetch all rendezvous
    if (!query.exec()) {
        qDebug() << "Error fetching rendezvous data:" << query.lastError();
        return;
    }

    // Step 2: Mark the dates on the calendar
    while (query.next()) {
        QDate date = query.value(0).toDate();  // Get the date of reservation
        if (date.isValid()) {
            // Create a text format to highlight the date
            QTextCharFormat format;
            format.setBackground(QBrush(QColor(Qt::yellow)));  // Highlight with a yellow background
            format.setForeground(QBrush(QColor(Qt::black)));  // Set text color to black
            // Mark this date on the calendar
            calendar->setDateTextFormat(date, format);
        }
    }
}

void MainWindow::on_pushButton_22_clicked()
{
    // Step 1: Retrieve rendezvous data from the database
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT date_de_reservation FROM rendezvous");

    // Create a map to store rendezvous count by month
    QMap<int, int> rendezvousByMonth;

    // Count rendezvous per month
    while (model->canFetchMore()) {
        model->fetchMore();
    }

    for (int i = 0; i < model->rowCount(); ++i) {
        QDate date = model->data(model->index(i, 0)).toDate();
        int month = date.month();
        rendezvousByMonth[month]++;
    }

    // Step 2: Prepare the data for the chart
    QStringList months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    QList<int> rendezvousCounts(12, 0);  // Initialize list with 12 months

    // Populate the rendezvousCounts list with data from the map
    for (int month = 1; month <= 12; ++month) {
        rendezvousCounts[month - 1] = rendezvousByMonth.value(month, 0);
    }

    // Step 3: Create the bar chart
    QBarSet *set = new QBarSet("Rendezvous");
    for (int count : rendezvousCounts) {
        *set << count;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Create a chart and set its title
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Rendezvous by Month");

    // Step 4: Set up the axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(months);  // Set months for the X-axis
    chart->setAxisX(axisX, series);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Number of Rendezvous");
    axisY->setLabelFormat("%i");
    chart->setAxisY(axisY, series);

    // Step 5: Display the chart in a view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);
    chartView->show();
}


void MainWindow::populateComboBox(QComboBox *sponsor) {

    // Query to select CODEFISCAL from SPONSOR
    QSqlQuery query("SELECT CODEFISCAL FROM SPONSOR");
    while (query.next()) {
        QString codeFiscal = query.value(0).toString();
        sponsor->addItem(codeFiscal); // Add CODEFISCAL to ComboBox
    }

}
