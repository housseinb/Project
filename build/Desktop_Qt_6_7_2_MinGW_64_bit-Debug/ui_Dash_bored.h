/********************************************************************************
** Form generated from reading UI file 'Dash_bored.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASH_BORED_H
#define UI_DASH_BORED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label_11;
    QTabWidget *tabWidget;
    QWidget *tab2;
    QWidget *tab;
    QLabel *label_6;
    QLabel *label_12;
    QLabel *label_9;
    QLineEdit *lineEdit;
    QLabel *label_10;
    QLabel *label_8;
    QPushButton *pushButton_8;
    QLineEdit *lineEdit_2;
    QLabel *label_7;
    QLabel *img2;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLabel *label;
    QPushButton *pushButton_6;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton_7;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(1293, 771);
        Dialog->setBaseSize(QSize(0, 0));
        Dialog->setStyleSheet(QString::fromUtf8("QWidget {\n"
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
        label_11 = new QLabel(Dialog);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(590, 740, 301, 31));
        label_11->setStyleSheet(QString::fromUtf8("color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(200, 90, 1041, 651));
        tabWidget->setStyleSheet(QString::fromUtf8("table {\n"
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
"    color: white;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"tr:hover {\n"
"    background-color: #f1f1f1;\n"
"}\n"
""));
        tab2 = new QWidget();
        tab2->setObjectName("tab2");
        tabWidget->addTab(tab2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 30, 131, 31));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(26, 2, 45);\n"
"font: 14pt \"Sitka\";"));
        label_12 = new QLabel(tab);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(340, 160, 191, 21));
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        label_9 = new QLabel(tab);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(340, 260, 191, 21));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(340, 400, 371, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_10 = new QLabel(tab);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(340, 360, 191, 21));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        label_8 = new QLabel(tab);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(340, 460, 171, 21));
        label_8->setStyleSheet(QString::fromUtf8("color: #1E293B;"));
        pushButton_8 = new QPushButton(tab);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(340, 560, 371, 41));
        pushButton_8->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
""));
        lineEdit_2 = new QLineEdit(tab);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(340, 500, 371, 41));
        lineEdit_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        label_7 = new QLabel(tab);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(440, 0, 141, 141));
        label_7->setStyleSheet(QString::fromUtf8("background-color: #F1F5F9;"));
        label_7->setPixmap(QPixmap(QString::fromUtf8("../../Projet c++/revision qt/template/image6.png")));
        img2 = new QLabel(tab);
        img2->setObjectName("img2");
        img2->setGeometry(QRect(910, 10, 81, 71));
        img2->setStyleSheet(QString::fromUtf8("\n"
"    border-radius: 5px;\n"
"    padding: 5px 10px;"));
        img2->setPixmap(QPixmap(QString::fromUtf8("../../../../Downloads/pngegg (1).png")));
        lineEdit_4 = new QLineEdit(tab);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(340, 300, 371, 41));
        lineEdit_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_5 = new QLineEdit(tab);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(340, 200, 371, 41));
        lineEdit_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tabWidget->addTab(tab, QString());
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 161, 751));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"border-radius: 15px;"));
        pushButton_6 = new QPushButton(Dialog);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(20, 550, 141, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"font: 12pt \"Sitka\";\n"
"border-color: rgb(37, 99, 235);\n"
"color: rgb(218, 221, 239);"));
        pushButton_2 = new QPushButton(Dialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(20, 270, 141, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"border-color: rgb(37, 99, 235);\n"
"font: 12pt \"Sitka\";\n"
"color: rgb(218, 221, 239);"));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 40, 121, 131));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);"));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../Projet c++/revision qt/template/image4.png")));
        pushButton_5 = new QPushButton(Dialog);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(20, 480, 141, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"font: 12pt \"Sitka\";\n"
"border-color: rgb(37, 99, 235);\n"
"color: rgb(218, 221, 239);"));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 200, 141, 41));
        pushButton->setStyleSheet(QString::fromUtf8("font: 12pt \"Sitka\";\n"
"color: rgb(218, 221, 239);\n"
"border-color: rgb(37, 99, 235);\n"
""));
        pushButton_4 = new QPushButton(Dialog);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(20, 410, 141, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);font: 12pt \"Sitka\";\n"
"border-color: rgb(37, 99, 235);\n"
"color: rgb(218, 221, 239);"));
        pushButton_3 = new QPushButton(Dialog);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(20, 340, 141, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"font: 12pt \"Sitka\";\n"
"border-color: rgb(37, 99, 235);\n"
"color: rgb(218, 221, 239);"));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(140, 10, 1151, 71));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"border-radius: 15px;"));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(1190, 20, 51, 51));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);"));
        label_4->setPixmap(QPixmap(QString::fromUtf8("../../Projet c++/revision qt/template/image5.png")));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(1070, 30, 101, 31));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(15, 23, 42);\n"
"font: 12pt \"Sitka\";\n"
"color: rgb(218, 221, 239);"));
        pushButton_7 = new QPushButton(Dialog);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(450, 20, 461, 51));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"border-color: rgb(37, 99, 235);\n"
"font: 18pt \"Sitka\";\n"
"color: rgb(218, 221, 239);\n"
""));

        retranslateUi(Dialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label_11->setText(QCoreApplication::translate("Dialog", "\302\251 2025 Acme, Inc. All rights reserved.", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QCoreApplication::translate("Dialog", "Tab 2", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog", "Profile", nullptr));
        label_12->setText(QCoreApplication::translate("Dialog", "Your first name:", nullptr));
        label_9->setText(QCoreApplication::translate("Dialog", "Your last name:", nullptr));
        lineEdit->setText(QCoreApplication::translate("Dialog", "User email", nullptr));
        label_10->setText(QCoreApplication::translate("Dialog", "Your email adress:", nullptr));
        label_8->setText(QCoreApplication::translate("Dialog", "Your password:", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Dialog", "Update your account", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("Dialog", "User password", nullptr));
        label_7->setText(QString());
        img2->setText(QString());
        lineEdit_4->setText(QCoreApplication::translate("Dialog", "User last name", nullptr));
        lineEdit_5->setText(QCoreApplication::translate("Dialog", "User first name", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Dialog", "profile", nullptr));
        label->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("Dialog", "Project", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Dialog", "Worker", nullptr));
        label_2->setText(QString());
        pushButton_5->setText(QCoreApplication::translate("Dialog", "Sponcor", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "Account", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Dialog", "Reservation", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Dialog", "Client", nullptr));
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QCoreApplication::translate("Dialog", "User Name", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Dialog", "Account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASH_BORED_H
