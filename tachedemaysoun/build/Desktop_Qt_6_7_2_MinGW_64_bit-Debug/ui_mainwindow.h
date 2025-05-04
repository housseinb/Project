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
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1293, 771);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
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
"}\n"
"\n"
"table {\n"
"    width: 100%;\n"
"    border-collapse: collapse;\n"
"    background-color: #ffffff;\n"
"    border-radius: 8px;\n"
"    overflow: hidden;\n"
"    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);\n"
"}\n"
"\n"
"th, td {\n"
"    padding: 12px;\n"
"    text-align: left;\n"
"    border-bottom: 1px solid #ddd;\n"
"}\n"
"\n"
"th {\n"
"    background-color: #007bff;\n"
"    "
                        "color: white;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"tr:hover {\n"
"    background-color: #f1f1f1;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(330, 130, 361, 101));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1293, 18));
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
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
