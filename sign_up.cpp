#include "sign_up.h"
#include "ui_sign_up.h"
#include "mainwindow.h"
#include "employee.h"
#include <QProcess>
#include <QString>
#include <QMessageBox>
#include <QRegularExpression>
#include <QPalette>
#include <QDebug>

Sign_Up::Sign_Up(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sign_Up)
{
    ui->setupUi(this);
    QPixmap pm("C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image.png");
    ui->img->setPixmap(pm);
    ui->img->setScaledContents(true);
    QPixmap pm2("C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image2.png");
    ui->img2->setPixmap(pm2);
    ui->img2->setScaledContents(true);
}

Sign_Up::~Sign_Up()
{
    delete ui;
}

void Sign_Up::on_pushButton_2_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    close();
    mainWindow->show();
}

void Sign_Up::on_b1_clicked()
{
    QString nom = ui->nom->text();
    QString email = ui->email->text();
    QString pwd = ui->pwd->text();
    QString pwdc = ui->pwdc->text();
    QString post = ui->post->currentText();

    if(pwd == pwdc){
        Employee e(nom, email, post, pwd);
        e.enregistre_employe_db();
    }
}

void Sign_Up::on_b1_2_clicked()
{
    QString pythonInterpreter = "C:\\Users\\hbarb\\AppData\\Local\\Microsoft\\WindowsApps\\python3.exe";
    QString pythonScriptPath = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\sign_up.py";

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
        }
    } else {
        qDebug() << "Python script failed to finish.";
    }

    process->deleteLater();
}

void Sign_Up::on_pwd_textChanged(const QString &arg1)
{
    ui->pwd->setEchoMode(QLineEdit::Password);

    QRegularExpression strongPwdRegex(R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&#])[A-Za-z\d@$!%*?&#]{8,})");

    if (strongPwdRegex.match(arg1).hasMatch()) {
        ui->pwd_2->setText("(Mot de passe fort !)");
        ui->pwd_2->setStyleSheet("color: green;");
    } else {
        ui->pwd_2->setText("(Le mot de passe doit contenir :\n- Min 8 caractères\n- Majuscule\n- Minuscule\n- Chiffre\n- Symbole (@$!%*?&#))");
        ui->pwd_2->setStyleSheet("color: red;");
    }
}

void Sign_Up::on_pwdc_textChanged(const QString &arg1)
{
    ui->pwdc->setEchoMode(QLineEdit::Password);
}


void Sign_Up::on_email_textChanged(const QString &arg1)
{
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (emailRegex.match(arg1).hasMatch()) {
        ui->email_2->setText("(Email valide !)");
        ui->email_2->setStyleSheet("color: green;");
    } else {
        ui->email_2->setText("(Email invalide !)");
        ui->email_2->setStyleSheet("color: red;");
    }
}

