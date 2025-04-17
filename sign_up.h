#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QWidget>

namespace Ui {
class Sign_Up;
}

class Sign_Up : public QWidget
{
    Q_OBJECT

public:
    explicit Sign_Up(QWidget *parent = nullptr);
    ~Sign_Up();

private slots:
    void on_pushButton_2_clicked();

    void on_b1_clicked();

    void on_b1_2_clicked();

    void on_pwd_textChanged(const QString &arg1);

    void on_pwdc_textChanged(const QString &arg1);

    void on_email_textChanged(const QString &arg1);

private:
    Ui::Sign_Up *ui;
};

#endif // SIGN_UP_H
