#ifndef NOUR_H
#define NOUR_H

#include <QWidget>
#include <QDate>
#include <QRegularExpression>
#include <QPrinter>
#include "client.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QDir>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QThread>
#include <QProcess>
#include <QtCharts/QLegend>
#include <QVBoxLayout>

namespace Ui {
class Nour;
}

class Nour : public QWidget
{
    Q_OBJECT

public:
    explicit Nour(QWidget *parent = nullptr);
    ~Nour();

private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_search_clicked();
    void on_pushButton_update_clicked();
    void on_clientsTable_itemSelectionChanged();
    void on_pushButton_exportPDF_clicked();
    void on_comboBox_sort_currentIndexChanged(int index);
    // void on_extractSkillsButton_clicked();
    //void on_browsePdfButton_clicked();
    //void on_generateButton_clicked();
    //void onRegenerateClicked();
    // void updateArduinoStatus();                      // ✅ SLOT for receiving data from Arduino
    // void updateClientPosition(int clientId, const QString &newPosition); // ✅ Updates client status
    //int assignNextClient();
    ////void on_galleryButton_clicked();  // New slot for gallery button



private:
    Ui::Nour *ui;
    QByteArray data;
    bool isGuiding = false;
    //QGridLayout* galleryLayout;
    //Arduino A;  // Arduino instance
    //int currentGuidingClientId = -1;


    void clearInputFields();
    void displayClients();
    bool validateClientForm();
    void exportToPDF(const QString &fileName, const QList<Client> &clients);
    void displayStatistics();
    void createDiplomaChart(const QMap<QString, int>& data);
    void createDomainChart(const QMap<QString, int>& data);
    void createAgeGroupChart(const QMap<QString, int>& data);
    void showClientsByDiplomeChart();
    void showClientsByDomaineChart();
    void showClientsByAgeGroupChart();
    //void showGeneratedLogo(const QString& logoPath);
    //void generateLogo();
    //void regenerate();
    //void loadGallery();              // Function to load gallery images
    //void showCurrentGuidingClient(int clientId);
    //void log(const QString& message);
    //void keyPressEvent(QKeyEvent *event);

};

class ExtractWorker : public QObject {
    Q_OBJECT
public:
    QString pdfPath;
    QString result;
    QString error;

public slots:
    void process() {
        QProcess pythonProcess;
        QString scriptPath = "C:/cpp/extract_skills.py";
        QStringList arguments;
        arguments << scriptPath << pdfPath;

        pythonProcess.start("python", arguments);
        pythonProcess.waitForFinished();

        result = pythonProcess.readAllStandardOutput().trimmed();
        error = pythonProcess.readAllStandardError().trimmed();

        emit finished();
    }

signals:
    void finished();
};

#endif // NOUR_H
