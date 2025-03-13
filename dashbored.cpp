#include "dashbored.h"
#include "ui_dashbored.h"
#include "employee.h"
#include "dashbored.h"
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QPushButton>
#include <QProcess>
#include "chartwidget.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>



dashbored::dashbored(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dashbored)
{
    ui->setupUi(this);

    QPixmap pm("C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image4.png");
    ui->logo->setPixmap(pm);
    ui->logo->setScaledContents(true);
    QPixmap pm2("C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image5.png");
    ui->img1->setPixmap(pm2);
    ui->img1->setScaledContents(true);
    QString imagePath = "C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image6.png";
    QPixmap pm3(imagePath);
    QString imagePath2 = "C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image6.png";
    QPixmap pm4(imagePath);

    if (pm3.isNull()) {
        qDebug() << "Erreur : Impossible de charger l'image à l'emplacement :" << imagePath;
    } else {
        ui->img4->setPixmap(pm3);
        ui->img4->setScaledContents(true);
        ui->img4->repaint();
    }
    if (pm4.isNull()) {
        qDebug() << "Erreur : Impossible de charger l'image à l'emplacement :" << imagePath2;
    } else {
        ui->image5->setPixmap(pm4);
        ui->image5->setScaledContents(true);
        ui->image5->repaint();
    }

    QPixmap pm5("C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image5.png");
    ui->img2_2->setPixmap(pm5);
    ui->img2_2->setScaledContents(true);

    populateEmployeeTable();
}

dashbored::~dashbored()
{
    delete ui;
}

void dashbored::afficher_user_dashbored(QString nom , QString email , QString post , QString pass){
    ui->username->setText(nom);
    ui->nom->setText(nom);
    ui->email->setText(email);
    ui->post->setCurrentText(post);
    ui->pwd->setText(pass);

}

void dashbored::on_pushButton_8_clicked()
{
    QString nom = ui->nom->text();
    QString email = ui->email->text();
    QString post = ui->post->currentText();
    QString pwd = ui->pwd->text();

    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM = :nom, EMAIL = :email, POSTE = :poste, MOT_DE_PASSE = :pwd WHERE EMAIL = :email");

    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":poste", post);
    query.bindValue(":pwd", pwd);

    if (!query.exec()) {
        qDebug() << "Error updating employee data:" << query.lastError();
    } else {
        qDebug() << "Employee data updated successfully!";
    }
    populateEmployeeTable();
}


void dashbored::populateEmployeeTable() {
    QSqlQuery query;
    query.prepare("SELECT ID_EMP, NOM, EMAIL, POSTE, MOT_DE_PASSE FROM EMPLOYE");

    if (!query.exec()) {
        qDebug() << "Error fetching employees:" << query.lastError();
        return;
    }

    ui->list->clearContents();
    ui->list->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->list->insertRow(row);

        int id = query.value("ID_EMP").toInt();
        QString nom = query.value("NOM").toString();
        QString email = query.value("EMAIL").toString();
        QString poste = query.value("POSTE").toString();
        QString pwd = query.value("MOT_DE_PASSE").toString();

        ui->list->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
        ui->list->setItem(row, 1, new QTableWidgetItem(nom));
        ui->list->setItem(row, 2, new QTableWidgetItem(email));
        ui->list->setItem(row, 3, new QTableWidgetItem(poste));
        ui->list->setItem(row, 4, new QTableWidgetItem(pwd));

        row++;
    }
}

void dashbored::on_pushButton_10_clicked()
{
    QString id = ui->id->text();

    if (id.isEmpty()) {
        qDebug() << "Error: ID is empty";
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE ID_EMP = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting employee with ID:" << id << query.lastError();
    } else {
        qDebug() << "Employee with ID:" << id << "deleted successfully.";
        on_pushButton_8_clicked();
    }
    populateEmployeeTable();

}

void dashbored::on_pushButton_9_clicked()
{
    QString nom = ui->nom2->text();
    QString email = ui->email2->text();
    QString pwd = ui->pwd2->text();
    QString post = ui->post2->currentText();
    Employee e(nom, email, post, pwd);
    e.enregistre_employe_db();
    populateEmployeeTable();
}


void dashbored::on_sort_clicked() {
    int columnIndex = ui->cb->currentIndex();
    Qt::SortOrder order = Qt::AscendingOrder;

    if (ui->list->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder) {
        order = Qt::DescendingOrder;
        ui->st->setText("Sorted Descending");
    } else {
        ui->st->setText("Sorted Ascending");
    }

    ui->list->sortItems(columnIndex, order);
}


void dashbored::on_find_textChanged(const QString &arg1) {
    for (int row = 0; row < ui->list->rowCount(); ++row) {
        bool match = false;
        for (int col = 0; col < ui->list->columnCount(); ++col) {
            QTableWidgetItem *item = ui->list->item(row, col);
            if (item && item->text().contains(arg1, Qt::CaseInsensitive)) {
                item->setBackground(Qt::yellow);
                match = true;
            } else if (item) {
                item->setBackground(Qt::white);
            }
        }
        ui->list->setRowHidden(row, !match);
    }
}

void dashbored::on_tabWidget_currentChanged(int index) {
    if (index == 3) {
        int rowCount = ui->list->rowCount();
        int postColumnIndex = 2;
        int filledPosts = 0;

        for (int row = 0; row < rowCount; ++row) {
            QTableWidgetItem *item = ui->list->item(row, postColumnIndex);
            if (item && !item->text().isEmpty()) {
                ++filledPosts;
            }
        }

        double fillPercentage = (static_cast<double>(filledPosts) / rowCount) * 100.0;
        ui->stat->setText(QString("Postes remplis : %1%").arg(fillPercentage, 0, 'f', 2));

        ChartWidget *chartWidget = new ChartWidget();
        chartWidget->setFilledCells(filledPosts, rowCount);

        ui->lay->addWidget(chartWidget);
    }
}


void dashbored::on_b1_2_clicked()
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


void dashbored::on_pwd2_textChanged(const QString &arg1)
{
    ui->pwd2->setEchoMode(QLineEdit::Password);
}


void dashbored::on_pwd_textChanged(const QString &arg1)
{
    ui->pwd->setEchoMode(QLineEdit::Password);

    QRegularExpression strongPwdRegex(R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&#])[A-Za-z\d@$!%*?&#]{8,})");

    if (strongPwdRegex.match(arg1).hasMatch()) {
        ui->ppwd->setText("(Mot de passe fort !)");
        ui->ppwd->setStyleSheet("color: green;");
    } else {
        ui->ppwd->setText("(Le mot de passe doit contenir :\n- Min 8 caractères\n- Majuscule\n- Minuscule\n- Chiffre\n- Symbole (@$!%*?&#))");
        ui->ppwd->setStyleSheet("color: red;");
    }
}


void dashbored::on_mic1_clicked()
{
    QString pythonPath = "C:\\Users\\hbarb\\AppData\\Local\\Microsoft\\WindowsApps\\python.exe";
    QString scriptPath = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\speech.py";

    QStringList arguments;
    arguments << scriptPath;

    QProcess *process = new QProcess(this);
    process->setProgram(pythonPath);
    process->setArguments(arguments);

    // Gestion des erreurs standard
    connect(process, &QProcess::errorOccurred, [this, process](QProcess::ProcessError error) {
        QString errorMessage;
        switch (error) {
        case QProcess::FailedToStart:
            errorMessage = "Failed to start. Check the Python path.";
            break;
        case QProcess::Crashed:
            errorMessage = "Python script crashed.";
            break;
        case QProcess::Timedout:
            errorMessage = "Process timed out.";
            break;
        case QProcess::WriteError:
            errorMessage = "Write error occurred.";
            break;
        case QProcess::ReadError:
            errorMessage = "Read error occurred.";
            break;
        default:
            errorMessage = "Unknown error occurred.";
        }
        ui->nom2->setText("Error: " + errorMessage);
        qDebug() << errorMessage;
        process->deleteLater();
    });

    // Capture de la sortie standard
    connect(process, &QProcess::readyReadStandardOutput, [this, process]() {
        QString output = process->readAllStandardOutput().trimmed();
        if (output.isEmpty()) {
            ui->nom2->setText("No output received from script.");
        } else {
            ui->nom2->setText(output);
        }
    });

    // Capture de la sortie d'erreurs
    connect(process, &QProcess::readyReadStandardError, [this, process]() {
        QString errorOutput = process->readAllStandardError().trimmed();
        if (!errorOutput.isEmpty()) {
            ui->nom2->setText("Script Error: " + errorOutput);
            qDebug() << "Script Error: " << errorOutput;
        }
    });

    // Nettoyage à la fin
    connect(process, &QProcess::finished, process, &QProcess::deleteLater);

    // Démarre le processus
    process->start();
    if (!process->waitForStarted()) {
        ui->nom2->setText("Failed to start process.");
    }
}


void dashbored::updateSpeechText()
{
    QString filePath = "C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/speech_output.txt";
    QFile file(filePath);

    if (!file.exists()) {
        ui->nom2->setText("File does not exist: " + filePath);
        return;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString speechText = in.readAll().trimmed();
        if (speechText.isEmpty()) {
            ui->nom2->setText("Speech output file is empty.");
        } else {
            ui->nom2->setText(speechText);
        }
        file.close();
    } else {
        ui->nom2->setText("Error reading speech output file.");
    }
}
