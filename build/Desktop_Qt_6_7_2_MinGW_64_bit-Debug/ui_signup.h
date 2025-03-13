/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SignUp
{
public:
    QLineEdit *pwd_3;
    QPushButton *b1;
    QLabel *label_4;
    QLineEdit *email;
    QLineEdit *email_2;
    QLabel *label_2;
    QLabel *img;
    QLabel *label_3;
    QLabel *label_9;
    QLabel *label_8;
    QLineEdit *pwd;
    QLabel *label_7;
    QPushButton *pushButton_2;
    QLabel *img2;
    QLineEdit *pwd_2;
    QLabel *label_6;
    QLabel *label;

    void setupUi(QDialog *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName("SignUp");
        SignUp->resize(1293, 771);
        pwd_3 = new QLineEdit(SignUp);
        pwd_3->setObjectName("pwd_3");
        pwd_3->setGeometry(QRect(720, 500, 371, 41));
        pwd_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        b1 = new QPushButton(SignUp);
        b1->setObjectName("b1");
        b1->setGeometry(QRect(720, 580, 371, 41));
        b1->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
"\n"
""));
        label_4 = new QLabel(SignUp);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(790, 650, 171, 31));
        label_4->setStyleSheet(QString::fromUtf8("	color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        email = new QLineEdit(SignUp);
        email->setObjectName("email");
        email->setGeometry(QRect(720, 140, 371, 41));
        email->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        email_2 = new QLineEdit(SignUp);
        email_2->setObjectName("email_2");
        email_2->setGeometry(QRect(720, 320, 371, 41));
        email_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_2 = new QLabel(SignUp);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(730, 100, 191, 21));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        img = new QLabel(SignUp);
        img->setObjectName("img");
        img->setGeometry(QRect(0, 0, 541, 771));
        img->setPixmap(QPixmap(QString::fromUtf8("../../Projet c++/revision qt/template/image.png")));
        img->setScaledContents(true);
        label_3 = new QLabel(SignUp);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(730, 190, 171, 21));
        label_3->setStyleSheet(QString::fromUtf8("color: #1E293B;"));
        label_9 = new QLabel(SignUp);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(730, 460, 321, 21));
        label_9->setStyleSheet(QString::fromUtf8("color: #1E293B;"));
        label_8 = new QLabel(SignUp);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(790, 730, 301, 31));
        label_8->setStyleSheet(QString::fromUtf8("color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        pwd = new QLineEdit(SignUp);
        pwd->setObjectName("pwd");
        pwd->setGeometry(QRect(720, 230, 371, 41));
        pwd->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        label_7 = new QLabel(SignUp);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(730, 370, 171, 21));
        label_7->setStyleSheet(QString::fromUtf8("color: #1E293B;"));
        pushButton_2 = new QPushButton(SignUp);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(950, 640, 81, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 9pt \"Arial\";\n"
"background-color: #F1F5F9;\n"
"color: #2563EB;\n"
""));
        img2 = new QLabel(SignUp);
        img2->setObjectName("img2");
        img2->setGeometry(QRect(1180, 40, 81, 71));
        img2->setStyleSheet(QString::fromUtf8("\n"
"    border-radius: 5px;\n"
"    padding: 5px 10px;"));
        img2->setPixmap(QPixmap(QString::fromUtf8("../../../../Downloads/pngegg (1).png")));
        pwd_2 = new QLineEdit(SignUp);
        pwd_2->setObjectName("pwd_2");
        pwd_2->setGeometry(QRect(720, 410, 371, 41));
        pwd_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        label_6 = new QLabel(SignUp);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(730, 280, 191, 21));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        label = new QLabel(SignUp);
        label->setObjectName("label");
        label->setGeometry(QRect(860, 40, 71, 31));
        label->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));

        retranslateUi(SignUp);

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QDialog *SignUp)
    {
        SignUp->setWindowTitle(QCoreApplication::translate("SignUp", "Dialog", nullptr));
        b1->setText(QCoreApplication::translate("SignUp", "Sign up", nullptr));
        label_4->setText(QCoreApplication::translate("SignUp", "Do you have an account ?", nullptr));
        label_2->setText(QCoreApplication::translate("SignUp", "Your name:", nullptr));
        img->setText(QString());
        label_3->setText(QCoreApplication::translate("SignUp", "Your last name:", nullptr));
        label_9->setText(QCoreApplication::translate("SignUp", "Confirme your  password:", nullptr));
        label_8->setText(QCoreApplication::translate("SignUp", "\302\251 2025 Acme, Inc. All rights reserved.", nullptr));
        label_7->setText(QCoreApplication::translate("SignUp", "Your password:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SignUp", "Sign in", nullptr));
        img2->setText(QString());
        label_6->setText(QCoreApplication::translate("SignUp", "Your email adress:", nullptr));
        label->setText(QCoreApplication::translate("SignUp", "Sign up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
