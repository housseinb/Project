#include "dashbored.h"
#include "ui_dashbored.h"
#include "employee.h"
#include "dashbored.h"
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QTimer>
#include <QPushButton>
#include <QProcess>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QPrinter>
#include <QPdfWriter>
#include <QPageSize>
#include <QPainter>
#include <QPrinter>
#include "BarChartItem.h"

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
    QPixmap pm7("C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image2.png");
    ui->img2->setPixmap(pm7);
    ui->img2->setScaledContents(true);
    QPixmap pm8("C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image2.png");
    ui->img2_2->setPixmap(pm8);
    ui->img2_2->setScaledContents(true);
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



void dashbored::on_b1_2_clicked()
{
    QString pythonInterpreter = "C:\\Users\\hbarb\\AppData\\Local\\Programs\\Python\\Python310\\python.exe ";
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
    QString pythonPath = "C:\\Users\\hbarb\\AppData\\Local\\Programs\\Python\\Python310\\python.exe";
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

    connect(process, &QProcess::readyReadStandardOutput, [this, process]() {
        QString output = process->readAllStandardOutput().trimmed();
        if (output.isEmpty()) {
            ui->nom2->setText("No output received from script.");
        } else {
            ui->nom2->setText(output);
        }
    });

    connect(process, &QProcess::readyReadStandardError, [this, process]() {
        QString errorOutput = process->readAllStandardError().trimmed();
        if (!errorOutput.isEmpty()) {
            ui->nom2->setText("Script Error: " + errorOutput);
            qDebug() << "Script Error: " << errorOutput;
        }
    });

    connect(process, &QProcess::finished, process, &QProcess::deleteLater);

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

void dashbored::on_b1_4_clicked()
{
    QString pythonPath = "C:\\Users\\hbarb\\AppData\\Local\\Programs\\Python\\Python310\\python.exe";
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
        ui->email2->setText("Error: " + errorMessage);
        qDebug() << errorMessage;
        process->deleteLater();
    });

    connect(process, &QProcess::readyReadStandardOutput, [this, process]() {
        QString output = process->readAllStandardOutput().trimmed();
        if (output.isEmpty()) {
            ui->email2->setText("No output received from script.");
        } else {
            ui->email2->setText(output);
        }
    });

    connect(process, &QProcess::readyReadStandardError, [this, process]() {
        QString errorOutput = process->readAllStandardError().trimmed();
        if (!errorOutput.isEmpty()) {
            ui->email2->setText("Script Error: " + errorOutput);
            qDebug() << "Script Error: " << errorOutput;
        }
    });
    connect(process, &QProcess::finished, process, &QProcess::deleteLater);


    process->start();
    if (!process->waitForStarted()) {
        ui->email2->setText("Failed to start process.");
    }
}


void dashbored::on_pdf_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf);;All Files (*)"));
    if (fileName.isEmpty()) {
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT ID_EMP, NOM, EMAIL, POSTE FROM EMPLOYE");

    if (!query.exec()) {
        qDebug() << "Error fetching employees:" << query.lastError();
        return;
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));

    QTextDocument textDocument;
    QString htmlContent = R"(
        <html>
        <head>
            <style>
                body { font-family: Arial, sans-serif; background-color: rgb(219, 232, 235); }
                .header { display: flex; align-items: center; justify-content: center; }
                .logo { margin-right: 20px; }
                .logo img { width: 150px; }
                h1 { color: #2C3E50; }
                table { width: 100%; border-collapse: collapse; margin-top: 20px; }
                th, td { border: 1px solid #BDC3C7; padding: 10px; text-align: left; }
                th { background-color: #34495E; color: #FFFFFF; }
                tr:nth-child(even) { background-color: #ECF0F1; }
            </style>
        </head>
        <body>
            <div class="header">
                <div class="logo">
                    <h1><img src="C:/Users/hbarb/Documents/2eme/Houssein Work/Nova_Up/image4.png" alt="Logo"/>Employee List</h1>
                </div>

            </div>
            <table>
                <tr><th>ID</th><th>Name</th><th>Email</th><th>Position</th></tr>
    )";

    while (query.next()) {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString email = query.value(2).toString();
        QString position = query.value(3).toString();

        htmlContent += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td></tr>")
                           .arg(id, name, email, position);
    }
    htmlContent += R"(
                </table>
            </body>
        </html>
    )";

    textDocument.setHtml(htmlContent);

    textDocument.print(&pdfWriter);
    QMessageBox::information(this, tr("PDF Created"), tr("The PDF has been created successfully."));
}



void dashbored::on_b1_3_clicked()
{
    QString pythonInterpreter = "C:\\Users\\hbarb\\AppData\\Local\\Programs\\Thonny\\python.exe";
    QString pythonScriptPath = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\emotion.py";

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


void dashbored::setEmployeeCounts(int agricultureCount, int itCount) {
    this->agricultureCount = agricultureCount;
    this->itCount = itCount;
    update();
}

void dashbored::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    int total = agricultureCount + itCount;

    QColor agricultureColor(0, 128, 0);
    QColor itColor(0, 0, 255);
    QColor otherColor(192, 192, 192);   // Grey for others

    // Calculate angles
    int agricultureAngle = (total > 0) ? static_cast<int>(360.0 * agricultureCount / total) : 0;
    int itAngle = (total > 0) ? static_cast<int>(360.0 * itCount / total) : 0;

    // Draw the pie chart
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2 - 50); // Adjust to center vertically
    painter.setBrush(QBrush(agricultureColor));
    painter.drawPie(-100, -100, 200, 200, 90 * 16, -agricultureAngle * 16); // Agriculture

    painter.setBrush(QBrush(itColor));
    painter.drawPie(-100, -100, 200, 200, (90 - agricultureAngle) * 16, -itAngle * 16); // IT

    // Draw a section for others if needed
    if (total > agricultureCount + itCount) {
        painter.setBrush(QBrush(otherColor));
        painter.drawPie(-100, -100, 200, 200, (90 - agricultureAngle - itAngle) * 16, -(360 - agricultureAngle - itAngle) * 16);
    }
}


void dashbored::on_tabWidget_tabBarClicked(int index)
{
    qDebug() << "Tab changed to index:" << index;

    // Ensure the database connection is open
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT POSTE, COUNT(*) AS COUNT FROM EMPLOYE GROUP BY POSTE");

    if (!query.exec()) {
        qDebug() << "Error fetching employee statistics:" << query.lastError();
        return;
    }

    int agricultureCount = 0;
    int itCount = 0;
    int totalEmployees = 0;

    while (query.next()) {
        QString post = query.value(0).toString();
        int count = query.value(1).toInt();

        totalEmployees += count;
        if (post == "Agriculture") {
            agricultureCount = count;
        } else if (post == "IT") {
            itCount = count;
        }
    }
    totalEmployees--;
    qDebug() << "Employees in Agriculture:" << agricultureCount;
    qDebug() << "Employees in IT:" << itCount;

    QGraphicsScene *scene = new QGraphicsScene(this);
    BarChartItem *barChart = new BarChartItem(agricultureCount, itCount);
    scene->addItem(barChart);

    QGraphicsView *graphicsView = findChild<QGraphicsView *>("graph");
    if (graphicsView) {
        graphicsView->setScene(scene);
    } else {
        qDebug() << "GraphicsView not found!";
    }

    QString statsMessage;
    if (totalEmployees > 0) {
        double agriculturePercentage = (static_cast<double>(agricultureCount) / totalEmployees) * 100;
        double itPercentage = (static_cast<double>(itCount) / totalEmployees) * 100;
        statsMessage = QString("Total Employees: %1\n"
                               "Employees in Agriculture: %2\n"
                               "Employees in IT: %3\n"
                               "Percentage of Employees in Agriculture: %4%\n"
                               "Percentage of Employees in IT: %5%")
                           .arg(totalEmployees)
                           .arg(agricultureCount)
                           .arg(itCount)
                           .arg(QString::number(agriculturePercentage, 'f', 2))
                           .arg(QString::number(itPercentage, 'f', 2));
    } else {
        statsMessage = "No employees found.";
    }

    QLabel *labelStats = findChild<QLabel *>("stat");
    if (labelStats) {
        labelStats->setText(statsMessage);
    } else {
        qDebug() << "Label not found!";
    }
}


void dashbored::on_b1_5_clicked()
{
    QString pythonInterpreter = "C:\\Users\\hbarb\\AppData\\Local\\Programs\\Thonny\\python.exe";
    QString pythonScriptPath = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\sign_languege.py";

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


void dashbored::on_b1_6_clicked()
{
    QString pythonInterpreter = "C:\\Users\\hbarb\\AppData\\Local\\Programs\\Thonny\\python.exe";
    QString pythonScriptPath = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\draw.py";

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


void dashbored::on_b1_7_clicked()
{
    QString pythonInterpreter = "C:\\Users\\hbarb\\AppData\\Local\\Programs\\Thonny\\python.exe";
    QString pythonScriptPath = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\objet.py";

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


void dashbored::on_b1_8_clicked()
{
    QString pythonInterpreter = "C:\\Users\\hbarb\\AppData\\Local\\Programs\\Thonny\\python.exe";
    QString pythonScriptPath = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\controle.py";

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


void dashbored::on_b1_9_clicked()
{
    QString pythonInterpreter = "C:\\Users\\hbarb\\AppData\\Local\\Programs\\Thonny\\python.exe";
    QString pythonScriptPath = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\figure.py";

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


void dashbored::on_b1_10_clicked()
{
    QString pythonInterpreter = "C:\\Users\\hbarb\\AppData\\Local\\Programs\\Thonny\\python.exe";
    QString pythonScriptPath = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\security.py";

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

