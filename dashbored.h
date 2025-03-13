#ifndef DASHBORED_H
#define DASHBORED_H

#include <QWidget>

namespace Ui {
class dashbored;
}

class dashbored : public QWidget
{
    Q_OBJECT

public:
    explicit dashbored(QWidget *parent = nullptr);
    ~dashbored();
    void afficher_user_dashbored(QString nom , QString email , QString post , QString pwd);
    void populateEmployeeTable();

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

private:
    Ui::dashbored *ui;
};


#endif // DASHBORED_H
