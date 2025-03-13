/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *l1;
    QPushButton *b1;
    QLabel *label_4;
    QLabel *img2;
    QLabel *label_3;
    QLineEdit *email;
    QPushButton *pushButton_2;
    QLabel *img;
    QLabel *label_8;
    QLineEdit *pwd;
    QLabel *label_5;
    QLabel *label_2;
    QPushButton *pushButton_3;
    QPushButton *b1_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1293, 771);
        MainWindow->setBaseSize(QSize(0, 0));
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
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
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        l1 = new QLabel(centralwidget);
        l1->setObjectName("l1");
        l1->setGeometry(QRect(860, 110, 71, 31));
        l1->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        b1 = new QPushButton(centralwidget);
        b1->setObjectName("b1");
        b1->setGeometry(QRect(730, 360, 371, 41));
        b1->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
"\n"
""));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(800, 450, 171, 31));
        label_4->setStyleSheet(QString::fromUtf8("	color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        img2 = new QLabel(centralwidget);
        img2->setObjectName("img2");
        img2->setGeometry(QRect(1180, 20, 81, 71));
        img2->setStyleSheet(QString::fromUtf8("\n"
"    border-radius: 5px;\n"
"    padding: 5px 10px;"));
        img2->setPixmap(QPixmap(QString::fromUtf8("../../../../Downloads/pngegg (1).png")));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(730, 260, 171, 21));
        label_3->setStyleSheet(QString::fromUtf8("color: #1E293B;"));
        email = new QLineEdit(centralwidget);
        email->setObjectName("email");
        email->setGeometry(QRect(730, 200, 371, 41));
        email->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(960, 440, 81, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 9pt \"Arial\";\n"
"    background-color: rgb(219, 232, 235);\n"
"color: #2563EB;\n"
""));
        img = new QLabel(centralwidget);
        img->setObjectName("img");
        img->setGeometry(QRect(0, -20, 541, 771));
        img->setPixmap(QPixmap(QString::fromUtf8("../../Projet c++/revision qt/template/image.png")));
        img->setScaledContents(true);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(790, 710, 301, 31));
        label_8->setStyleSheet(QString::fromUtf8("color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        pwd = new QLineEdit(centralwidget);
        pwd->setObjectName("pwd");
        pwd->setGeometry(QRect(730, 290, 371, 41));
        pwd->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(800, 480, 171, 31));
        label_5->setStyleSheet(QString::fromUtf8("color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(730, 170, 191, 21));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(960, 480, 71, 31));
        pushButton_3->setStyleSheet(QString::fromUtf8("font: 9pt \"Body\";\n"
" background-color: rgb(219, 232, 235);\n"
"color: #2563EB;\n"
""));
        b1_2 = new QPushButton(centralwidget);
        b1_2->setObjectName("b1_2");
        b1_2->setGeometry(QRect(1180, 90, 81, 41));
        b1_2->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"font: 9pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
"\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1293, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        l1->setText(QCoreApplication::translate("MainWindow", "Sign in", nullptr));
        b1->setText(QCoreApplication::translate("MainWindow", "Sign in", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Don't have an account ?", nullptr));
        img2->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Your password:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Sign up", nullptr));
        img->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "\302\251 2025 Acme, Inc. All rights reserved.", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Forget your password ?", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Your email adress:", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        b1_2->setText(QCoreApplication::translate("MainWindow", "Sign in", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
