#ifndef DASHBORED_H
#define DASHBORED_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QColor>

namespace Ui {
class dashbored;
}

class dashbored : public QWidget
{
    Q_OBJECT

public:
    explicit dashbored(QWidget *parent = nullptr);
    ~dashbored();
    void afficher_user_dashbored(QString nom, QString email, QString post, QString pwd);
    void populateEmployeeTable();

    // New methods for pie chart
    void setEmployeeCounts(int agricultureCount, int itCount);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_pushButton_8_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_9_clicked();
    void on_sort_clicked();
    void on_find_textChanged(const QString &arg1);
    void on_tabWidget_currentChanged(int index);
    void on_mic1_clicked();
    void updateSpeechText();
    void on_b1_2_clicked();
    void on_pwd2_textChanged(const QString &arg1);
    void on_pwd_textChanged(const QString &arg1);
    void on_b1_4_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pdf_clicked();
    void on_pushButton_2_clicked();
    void on_b1_3_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_b1_5_clicked();

    void on_b1_6_clicked();

    void on_b1_7_clicked();

    void on_b1_8_clicked();

    void on_b1_9_clicked();

    void on_b1_10_clicked();

private:
    Ui::dashbored *ui;

    // New member variables for counts
    int agricultureCount;
    int itCount;
};

#endif // DASHBORED_H
