/********************************************************************************
** Form generated from reading UI file 'sign_up.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_UP_H
#define UI_SIGN_UP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sign_Up
{
public:
    QLabel *label_4;
    QPushButton *pushButton_2;
    QLineEdit *email;
    QLineEdit *pwdc;
    QLineEdit *pwd;
    QLabel *img;
    QLabel *label_2;
    QLabel *label_9;
    QLabel *label_8;
    QLineEdit *nom;
    QLabel *label_6;
    QLabel *label;
    QLabel *img2;
    QLabel *label_7;
    QPushButton *b1;
    QLabel *label_3;
    QComboBox *post;
    QPushButton *b1_2;
    QLabel *pwd_2;
    QLabel *email_2;

    void setupUi(QWidget *Sign_Up)
    {
        if (Sign_Up->objectName().isEmpty())
            Sign_Up->setObjectName("Sign_Up");
        Sign_Up->resize(1320, 771);
        Sign_Up->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	font: 9pt \"Sitka\";\n"
"    background-color: rgb(219, 232, 235);\n"
"    font-family: \"Sitka\";\n"
"}\n"
"\n"
"QLabel {\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    color: #222;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    border: 2px solid #ccc;\n"
"    border-radius: 5px;\n"
"    padding: 8px;\n"
"    font-size: 16px;\n"
"    width: 250px;\n"
"}\n"
"\n"
"QPushButton {\n"
"	background-color: rgb(37, 99, 235);\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    padding: 10px 20px;\n"
"    font-size: 18px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(25, 80, 200); \n"
"    color: white; \n"
"}"));
        label_4 = new QLabel(Sign_Up);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(790, 650, 171, 31));
        label_4->setStyleSheet(QString::fromUtf8("	color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        pushButton_2 = new QPushButton(Sign_Up);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(950, 640, 81, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 9pt \"Arial\";\n"
"    background-color: rgb(219, 232, 235);\n"
"color: #2563EB;\n"
""));
        email = new QLineEdit(Sign_Up);
        email->setObjectName("email");
        email->setGeometry(QRect(720, 230, 371, 41));
        email->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pwdc = new QLineEdit(Sign_Up);
        pwdc->setObjectName("pwdc");
        pwdc->setGeometry(QRect(720, 410, 371, 41));
        pwdc->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        pwd = new QLineEdit(Sign_Up);
        pwd->setObjectName("pwd");
        pwd->setGeometry(QRect(720, 320, 371, 41));
        pwd->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        img = new QLabel(Sign_Up);
        img->setObjectName("img");
        img->setGeometry(QRect(0, 0, 541, 771));
        img->setPixmap(QPixmap(QString::fromUtf8("../../Projet c++/revision qt/template/image.png")));
        img->setScaledContents(true);
        label_2 = new QLabel(Sign_Up);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(730, 100, 301, 21));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        label_9 = new QLabel(Sign_Up);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(730, 370, 321, 21));
        label_9->setStyleSheet(QString::fromUtf8("color: #1E293B;"));
        label_8 = new QLabel(Sign_Up);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(790, 730, 301, 31));
        label_8->setStyleSheet(QString::fromUtf8("color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        nom = new QLineEdit(Sign_Up);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(720, 140, 371, 41));
        nom->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_6 = new QLabel(Sign_Up);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(730, 190, 191, 21));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        label = new QLabel(Sign_Up);
        label->setObjectName("label");
        label->setGeometry(QRect(860, 40, 71, 31));
        label->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        img2 = new QLabel(Sign_Up);
        img2->setObjectName("img2");
        img2->setGeometry(QRect(1180, 40, 81, 71));
        img2->setStyleSheet(QString::fromUtf8("\n"
"    border-radius: 5px;\n"
"    padding: 5px 10px;"));
        img2->setPixmap(QPixmap(QString::fromUtf8("../../../../Downloads/pngegg (1).png")));
        label_7 = new QLabel(Sign_Up);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(730, 280, 171, 21));
        label_7->setStyleSheet(QString::fromUtf8("color: #1E293B;"));
        b1 = new QPushButton(Sign_Up);
        b1->setObjectName("b1");
        b1->setGeometry(QRect(720, 580, 371, 41));
        b1->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
"\n"
""));
        label_3 = new QLabel(Sign_Up);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(730, 460, 171, 21));
        label_3->setStyleSheet(QString::fromUtf8("color: #1E293B;"));
        post = new QComboBox(Sign_Up);
        post->addItem(QString());
        post->addItem(QString());
        post->setObjectName("post");
        post->setGeometry(QRect(720, 500, 371, 41));
        post->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        b1_2 = new QPushButton(Sign_Up);
        b1_2->setObjectName("b1_2");
        b1_2->setGeometry(QRect(1180, 120, 81, 41));
        b1_2->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"font: 9pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
"\n"
""));
        pwd_2 = new QLabel(Sign_Up);
        pwd_2->setObjectName("pwd_2");
        pwd_2->setGeometry(QRect(1100, 280, 211, 271));
        pwd_2->setStyleSheet(QString::fromUtf8("color: #1E293B;"));
        email_2 = new QLabel(Sign_Up);
        email_2->setObjectName("email_2");
        email_2->setGeometry(QRect(1100, 230, 181, 41));
        email_2->setStyleSheet(QString::fromUtf8("color: #1E293B;"));

        retranslateUi(Sign_Up);

        QMetaObject::connectSlotsByName(Sign_Up);
    } // setupUi

    void retranslateUi(QWidget *Sign_Up)
    {
        Sign_Up->setWindowTitle(QCoreApplication::translate("Sign_Up", "Form", nullptr));
        label_4->setText(QCoreApplication::translate("Sign_Up", "Do you have an account ?", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Sign_Up", "Sign in", nullptr));
        img->setText(QString());
        label_2->setText(QCoreApplication::translate("Sign_Up", "Your name and your last name:", nullptr));
        label_9->setText(QCoreApplication::translate("Sign_Up", "Confirme your  password:", nullptr));
        label_8->setText(QCoreApplication::translate("Sign_Up", "\302\251 2025 Acme, Inc. All rights reserved.", nullptr));
        label_6->setText(QCoreApplication::translate("Sign_Up", "Your email adress:", nullptr));
        label->setText(QCoreApplication::translate("Sign_Up", "Sign up", nullptr));
        img2->setText(QString());
        label_7->setText(QCoreApplication::translate("Sign_Up", "Your password:", nullptr));
        b1->setText(QCoreApplication::translate("Sign_Up", "Sign up", nullptr));
        label_3->setText(QCoreApplication::translate("Sign_Up", "Poste:", nullptr));
        post->setItemText(0, QCoreApplication::translate("Sign_Up", "Agriculture", nullptr));
        post->setItemText(1, QCoreApplication::translate("Sign_Up", "IT", nullptr));

        b1_2->setText(QCoreApplication::translate("Sign_Up", "Sign up", nullptr));
        pwd_2->setText(QString());
        email_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Sign_Up: public Ui_Sign_Up {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_UP_H
