#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QRegularExpression>
#include <QPrinter> // Include QPrinter
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
///
///
///
#include <QThread>
#include <QProcess>
///
///
///
///
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLegend>
#include <QVBoxLayout>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_search_clicked();
    void on_pushButton_update_clicked();
    void on_clientsTable_itemSelectionChanged();
    void on_pushButton_exportPDF_clicked(); // New slot for PDF export
    void on_extractSkillsButton_clicked();
    void on_browsePdfButton_clicked();
    void on_generateButton_clicked();
    void onRegenerateClicked();
    //void on_galleryButton_clicked();  // New slot for gallery button

private:
    Ui::MainWindow *ui;
    QGridLayout* galleryLayout;      // Layout for the gallery
    void clearInputFields();
    void displayClients();
    bool validateClientForm();
    void exportToPDF(const QString &fileName, const QList<Client> &clients); // New method for PDF export
    void displayStatistics();
    void createDiplomaChart(const QMap<QString, int>& data);
    void createDomainChart(const QMap<QString, int>& data);
    void createAgeGroupChart(const QMap<QString, int>& data);
    void showGeneratedLogo(const QString& logoPath);
    void generateLogo();
    void regenerate();
    void loadGallery();              // Function to load gallery images

    void showClientsByDiplomeChart();
};

////
///
///
///
///
class ExtractWorker : public QObject {
    Q_OBJECT
public:
    QString pdfPath;
    QString result;
    QString error;

public slots:
    void process() {
        QProcess pythonProcess;
        QString scriptPath = "C:/cpp/extract_skills.py";  // ⚠️ use forward slashes or escape backslashes
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

#endif // MAINWINDOW_H
