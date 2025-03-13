/********************************************************************************
** Form generated from reading UI file 'sign_in.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_IN_H
#define UI_SIGN_IN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sign_in
{
public:
    QLabel *label_8;
    QLineEdit *pwd;
    QPushButton *b1;
    QPushButton *pushButton_3;
    QLabel *label_4;
    QLabel *img;
    QLineEdit *email;
    QPushButton *pushButton_2;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *label;
    QLabel *img2;
    QLabel *label_3;

    void setupUi(QWidget *Sign_in)
    {
        if (Sign_in->objectName().isEmpty())
            Sign_in->setObjectName("Sign_in");
        Sign_in->resize(1320, 771);
        Sign_in->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	font: 9pt \"Sitka\";\n"
"    background-color: #F1F5F9;\n"
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
        label_8 = new QLabel(Sign_in);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(790, 730, 301, 31));
        label_8->setStyleSheet(QString::fromUtf8("color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        pwd = new QLineEdit(Sign_in);
        pwd->setObjectName("pwd");
        pwd->setGeometry(QRect(730, 310, 371, 41));
        pwd->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        b1 = new QPushButton(Sign_in);
        b1->setObjectName("b1");
        b1->setGeometry(QRect(730, 380, 371, 41));
        b1->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
"\n"
""));
        pushButton_3 = new QPushButton(Sign_in);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(960, 500, 71, 31));
        pushButton_3->setStyleSheet(QString::fromUtf8("font: 9pt \"Body\";\n"
"background-color: #F1F5F9;\n"
"color: #2563EB;\n"
""));
        label_4 = new QLabel(Sign_in);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(800, 470, 171, 31));
        label_4->setStyleSheet(QString::fromUtf8("	color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        img = new QLabel(Sign_in);
        img->setObjectName("img");
        img->setGeometry(QRect(0, 0, 541, 771));
        img->setPixmap(QPixmap(QString::fromUtf8("../../Projet c++/revision qt/template/image.png")));
        img->setScaledContents(true);
        email = new QLineEdit(Sign_in);
        email->setObjectName("email");
        email->setGeometry(QRect(730, 220, 371, 41));
        email->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pushButton_2 = new QPushButton(Sign_in);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(960, 460, 81, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 9pt \"Arial\";\n"
"background-color: #F1F5F9;\n"
"color: #2563EB;\n"
""));
        label_5 = new QLabel(Sign_in);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(800, 500, 171, 31));
        label_5->setStyleSheet(QString::fromUtf8("color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        label_2 = new QLabel(Sign_in);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(730, 190, 191, 21));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        label = new QLabel(Sign_in);
        label->setObjectName("label");
        label->setGeometry(QRect(860, 130, 71, 31));
        label->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        img2 = new QLabel(Sign_in);
        img2->setObjectName("img2");
        img2->setGeometry(QRect(1180, 40, 81, 71));
        img2->setStyleSheet(QString::fromUtf8("\n"
"    border-radius: 5px;\n"
"    padding: 5px 10px;"));
        img2->setPixmap(QPixmap(QString::fromUtf8("../../../../Downloads/pngegg (1).png")));
        label_3 = new QLabel(Sign_in);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(730, 280, 171, 21));
        label_3->setStyleSheet(QString::fromUtf8("color: #1E293B;"));

        retranslateUi(Sign_in);

        QMetaObject::connectSlotsByName(Sign_in);
    } // setupUi

    void retranslateUi(QWidget *Sign_in)
    {
        Sign_in->setWindowTitle(QCoreApplication::translate("Sign_in", "Form", nullptr));
        label_8->setText(QCoreApplication::translate("Sign_in", "\302\251 2025 Acme, Inc. All rights reserved.", nullptr));
        b1->setText(QCoreApplication::translate("Sign_in", "Sign in", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Sign_in", "Reset", nullptr));
        label_4->setText(QCoreApplication::translate("Sign_in", "Don't have an account ?", nullptr));
        img->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("Sign_in", "Sign up", nullptr));
        label_5->setText(QCoreApplication::translate("Sign_in", "Forget your password ?", nullptr));
        label_2->setText(QCoreApplication::translate("Sign_in", "Your email adress:", nullptr));
        label->setText(QCoreApplication::translate("Sign_in", "Sign in", nullptr));
        img2->setText(QString());
        label_3->setText(QCoreApplication::translate("Sign_in", "Your password:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sign_in: public Ui_Sign_in {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_IN_H
