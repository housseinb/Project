#include "sign_in.h"
#include "ui_sign_in.h"
#include "sign_up.h"
#include "mainwindow.h"
#include <QMainWindow>

Sign_in::Sign_in(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sign_in)
{
    ui->setupUi(this);
}

Sign_in::~Sign_in()
{
    delete ui;
}

void Sign_in::on_pushButton_2_clicked()
{
    // Récupérer le QMainWindow parent
    QMainWindow *mainWindow = qobject_cast<QMainWindow *>(this->window());

    if (mainWindow) {
        // Remplacer Sign_in par Sign_Up
        Sign_Up *signupPage = new Sign_Up(mainWindow);
        mainWindow->setCentralWidget(signupPage);
        delete this;  // Facultatif : Supprimer Sign_in pour éviter une fuite mémoire
    } else {
        qDebug() << "Erreur: Impossible de trouver le QMainWindow";
    }
}
