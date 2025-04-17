#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include "dashbored.h"
#include <QProcess>
#include <QString>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pm("C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image.png");
    ui->img->setPixmap(pm);
    ui->img->setScaledContents(true);

    QPixmap pm2("C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image2.png");
    ui->img2->setPixmap(pm2);
    ui->img2->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    Sign_Up *signupPage = new Sign_Up(this);
    setCentralWidget(signupPage);
}

void MainWindow::on_b1_clicked()
{
    Employee e;
    QString email = ui->email->text();
    QString pwd = ui->pwd->text();

    bool connection = e.connection_employe_db(email, pwd);
    if (connection) {
        dashbored *dashboredPage = new dashbored(this);
        setCentralWidget(dashboredPage);

        QString nom = e.getNom();
        QString post = e.getPoste();
        dashboredPage->afficher_user_dashbored(nom, email, post, pwd);
    } else {
        QMessageBox::critical(this, "Error", "Invalid login credentials.");
    }
}

void MainWindow::on_b1_2_clicked()
{
    QString pythonInterpreter = "C:\\Users\\hbarb\\AppData\\Local\\Programs\\Python\\Python310\\python.exe ";
    QString pythonScriptPath = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\sign_in.py";

    QProcess *process = new QProcess(this);
    QStringList arguments;
    arguments << pythonScriptPath;

    process->start(pythonInterpreter, arguments);

    if (process->waitForStarted()) {
        qDebug() << "Python script started successfully.";
    } else {
        QMessageBox::critical(this, "Error", "Failed to start the Python script.");
    }

    if (process->waitForFinished()) {
        QString output = process->readAllStandardOutput();
        QString errorOutput = process->readAllStandardError();

        qDebug() << "Output from Python script: " << output;
        qDebug() << "Error output from Python script: " << errorOutput;

        if (!errorOutput.isEmpty()) {
            QMessageBox::critical(this, "Python Script Error", errorOutput);
        } else {
            QMessageBox::information(this, "Python Script Result", output);

            dashbored *dashboredPage = new dashbored(this);
            setCentralWidget(dashboredPage);
        }
    } else {
        qDebug() << "Python script failed to finish.";
    }

    process->deleteLater();
}

void MainWindow::on_pwd_textChanged(const QString &arg1)
{
    ui->pwd->setEchoMode(QLineEdit::Password);
}


