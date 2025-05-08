#ifndef TACHEAMINE_H
#define TACHEAMINE_H
#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QTableWidgetItem>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include "sponsor.h"
#include "chatbot.h"
#include <QVector>
#include <QPair>
#include <QColor>
#include <QWidget>
#include <QPainter>
#include <QVBoxLayout>
#include <QPaintEvent>
#include "arduino.h"
#include <QTimer>
#include <QWidget>

namespace Ui {
class tacheamine;
}

class tacheamine : public QWidget
{
    Q_OBJECT

public:
    explicit tacheamine(QWidget *parent = nullptr);
    ~tacheamine();
private slots:
    void toggleChatInterface();
    void on_add_clicked();
    void on_upd_clicked();
    void on_del_clicked();
    void on_load_clicked();
    void on_insert_clicked();
    void on_downloadPdf_clicked();
    void on_filter_currentIndexChanged(int index);
    void updateDomainStatistics();
    void displayBotMessage(const QString &message);
    void displayUserMessage(const QString &message);
private:
    Ui::tacheamine *ui;
    QSqlTableModel *model;
    void loadTableData();
    QSqlDatabase db;  // Add this
    Chatbot *chatbot;
    void setupUI();
    void setupConnections();
    void checkDatabaseConnection();
    QString loadedCodeFiscal;
    void scrollToBottom();
};
class PieChartWidget : public QWidget {
    Q_OBJECT
public:
    PieChartWidget(const QVector<QPair<QString, double>>& data,
                   const QVector<QColor>& colors,
                   QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<QPair<QString, double>> m_data;
    QVector<QColor> m_colors;
};

#endif // TACHEAMINE_H
