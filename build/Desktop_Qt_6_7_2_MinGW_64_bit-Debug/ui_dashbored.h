/********************************************************************************
** Form generated from reading UI file 'dashbored.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBORED_H
#define UI_DASHBORED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dashbored
{
public:
    QLabel *label_11;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_6;
    QLabel *label_12;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_8;
    QPushButton *pushButton_8;
    QLineEdit *pwd;
    QLabel *img4;
    QLineEdit *email;
    QLineEdit *nom;
    QComboBox *post;
    QLabel *ppwd;
    QWidget *tab_2;
    QTableWidget *list;
    QLabel *label_18;
    QLineEdit *id;
    QLabel *label_19;
    QLabel *label_20;
    QPushButton *pushButton_10;
    QLabel *label_21;
    QLabel *st;
    QPushButton *sort;
    QComboBox *cb;
    QLineEdit *find;
    QLabel *label_22;
    QWidget *tab2;
    QLabel *label_13;
    QPushButton *pushButton_9;
    QComboBox *post2;
    QLabel *img2_2;
    QLineEdit *pwd2;
    QLabel *image5;
    QLineEdit *email2;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLineEdit *nom2;
    QPushButton *b1_2;
    QPushButton *mic1;
    QPushButton *b1_4;
    QPushButton *b1_6;
    QWidget *tab_3;
    QLabel *stat;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *lay;
    QLabel *label;
    QPushButton *pushButton_6;
    QPushButton *pushButton;
    QLabel *logo;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QLabel *label_3;
    QLabel *img1;
    QPushButton *pushButton_7;
    QLabel *username;

    void setupUi(QWidget *dashbored)
    {
        if (dashbored->objectName().isEmpty())
            dashbored->setObjectName("dashbored");
        dashbored->resize(1293, 771);
        dashbored->setStyleSheet(QString::fromUtf8("QWidget {\n"
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
        label_11 = new QLabel(dashbored);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(580, 730, 301, 31));
        label_11->setStyleSheet(QString::fromUtf8("color: #64748B;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    width: 200px;"));
        tabWidget = new QTabWidget(dashbored);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(180, 90, 1230, 771));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab {\n"
"    color: black; /* Texte en noir */\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    font-weight: bold; /* Met en gras l'onglet s\303\251lectionn\303\251 */\n"
"}\n"
"\n"
"QTabBar::tab:disabled {\n"
"    color: black; /* Assurez-vous que les onglets d\303\251sactiv\303\251s ont aussi le texte en noir */\n"
"}\n"
"\n"
"table {\n"
"    \n"
"	color: black;\n"
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
"    color: black;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"tr:hover {\n"
"    background-color: #f1f1f1;\n"
"}\n"
""));
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName("tab");
        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 40, 131, 31));
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
        pwd = new QLineEdit(tab);
        pwd->setObjectName("pwd");
        pwd->setGeometry(QRect(340, 500, 371, 41));
        pwd->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        img4 = new QLabel(tab);
        img4->setObjectName("img4");
        img4->setGeometry(QRect(440, 0, 141, 141));
        img4->setStyleSheet(QString::fromUtf8("background-color: #F1F5F9;"));
        img4->setPixmap(QPixmap(QString::fromUtf8("../../Projet c++/revision qt/template/image6.png")));
        email = new QLineEdit(tab);
        email->setObjectName("email");
        email->setGeometry(QRect(340, 300, 371, 41));
        email->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        nom = new QLineEdit(tab);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(340, 200, 371, 41));
        nom->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        post = new QComboBox(tab);
        post->addItem(QString());
        post->addItem(QString());
        post->setObjectName("post");
        post->setGeometry(QRect(340, 400, 371, 41));
        post->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        ppwd = new QLabel(tab);
        ppwd->setObjectName("ppwd");
        ppwd->setGeometry(QRect(740, 500, 251, 41));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        list = new QTableWidget(tab_2);
        if (list->columnCount() < 5)
            list->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        list->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        list->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        list->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        list->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        list->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        list->setObjectName("list");
        list->setGeometry(QRect(40, 100, 511, 301));
        list->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QTableWidget {\n"
"	 color: black;   \n"
"    background-color: #f0f0f0;  /* Couleur de fond */\n"
"    gridline-color: #dcdcdc;    /* Couleur des lignes de s\303\251paration */\n"
"    font-size: 14px;            /* Taille du texte */\n"
"    border: 1px solid #ccc;     /* Bordure du tableau */\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #0078D7;  /* Couleur de fond des en-t\303\252tes */\n"
"    color: white;               /* Couleur du texte des en-t\303\252tes */\n"
"    font-weight: bold;          /* Texte en gras */\n"
"    padding: 5px;\n"
"    border: 1px solid #005a9e;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 5px;               /* Espacement int\303\251rieur des cellules */\n"
"    border: 1px solid #ddd;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #3498db;  /* Couleur de s\303\251lection */\n"
"    color: white;\n"
"}\n"
"\n"
"QTableWidget::item:hover {\n"
"    background-color: #e0e0e0;  /* Effet survol */\n"
"}\n"
""));
        label_18 = new QLabel(tab_2);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(30, 40, 131, 31));
        label_18->setStyleSheet(QString::fromUtf8("color: rgb(26, 2, 45);\n"
"font: 14pt \"Sitka\";"));
        id = new QLineEdit(tab_2);
        id->setObjectName("id");
        id->setGeometry(QRect(790, 250, 113, 41));
        id->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_19 = new QLabel(tab_2);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(730, 210, 131, 31));
        label_19->setStyleSheet(QString::fromUtf8("color: rgb(26, 2, 45);\n"
"font: 14pt \"Sitka\";"));
        label_20 = new QLabel(tab_2);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(730, 260, 51, 31));
        label_20->setStyleSheet(QString::fromUtf8("color: rgb(26, 2, 45);\n"
"font: 14pt \"Sitka\";"));
        pushButton_10 = new QPushButton(tab_2);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(920, 250, 141, 41));
        pushButton_10->setStyleSheet(QString::fromUtf8("font: 12pt \"Sitka\";\n"
"color: rgb(218, 221, 239);\n"
"background-color: rgb(170, 0, 0);\n"
""));
        label_21 = new QLabel(tab_2);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(730, 160, 51, 31));
        label_21->setStyleSheet(QString::fromUtf8("color: rgb(26, 2, 45);\n"
"font: 14pt \"Sitka\";"));
        st = new QLabel(tab_2);
        st->setObjectName("st");
        st->setGeometry(QRect(730, 110, 241, 31));
        st->setStyleSheet(QString::fromUtf8("color: rgb(26, 2, 45);\n"
"font: 14pt \"Sitka\";"));
        sort = new QPushButton(tab_2);
        sort->setObjectName("sort");
        sort->setGeometry(QRect(920, 150, 141, 41));
        sort->setStyleSheet(QString::fromUtf8("font: 12pt \"Sitka\";\n"
"color: rgb(218, 221, 239);\n"
"background-color: rgb(0, 170, 0);\n"
""));
        cb = new QComboBox(tab_2);
        cb->addItem(QString());
        cb->addItem(QString());
        cb->addItem(QString());
        cb->setObjectName("cb");
        cb->setGeometry(QRect(780, 150, 131, 41));
        cb->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        find = new QLineEdit(tab_2);
        find->setObjectName("find");
        find->setGeometry(QRect(280, 40, 171, 41));
        find->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_22 = new QLabel(tab_2);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(190, 40, 81, 31));
        label_22->setStyleSheet(QString::fromUtf8("color: rgb(26, 2, 45);\n"
"font: 14pt \"Sitka\";"));
        tabWidget->addTab(tab_2, QString());
        tab2 = new QWidget();
        tab2->setObjectName("tab2");
        label_13 = new QLabel(tab2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(20, 40, 131, 31));
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(26, 2, 45);\n"
"font: 14pt \"Sitka\";"));
        pushButton_9 = new QPushButton(tab2);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(340, 570, 371, 41));
        pushButton_9->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
""));
        post2 = new QComboBox(tab2);
        post2->addItem(QString());
        post2->addItem(QString());
        post2->setObjectName("post2");
        post2->setGeometry(QRect(340, 410, 371, 41));
        post2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        img2_2 = new QLabel(tab2);
        img2_2->setObjectName("img2_2");
        img2_2->setGeometry(QRect(910, 20, 81, 71));
        img2_2->setStyleSheet(QString::fromUtf8("\n"
"    border-radius: 5px;\n"
"    padding: 5px 10px;"));
        img2_2->setPixmap(QPixmap(QString::fromUtf8("../../../../Downloads/pngegg (1).png")));
        pwd2 = new QLineEdit(tab2);
        pwd2->setObjectName("pwd2");
        pwd2->setGeometry(QRect(340, 510, 371, 41));
        pwd2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        image5 = new QLabel(tab2);
        image5->setObjectName("image5");
        image5->setGeometry(QRect(440, 10, 141, 141));
        image5->setStyleSheet(QString::fromUtf8("background-color: #F1F5F9;"));
        image5->setPixmap(QPixmap(QString::fromUtf8("../../Projet c++/revision qt/template/image6.png")));
        email2 = new QLineEdit(tab2);
        email2->setObjectName("email2");
        email2->setGeometry(QRect(340, 310, 371, 41));
        email2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_14 = new QLabel(tab2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(340, 170, 191, 21));
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        label_15 = new QLabel(tab2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(340, 270, 191, 21));
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        label_16 = new QLabel(tab2);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(340, 470, 171, 21));
        label_16->setStyleSheet(QString::fromUtf8("color: #1E293B;"));
        label_17 = new QLabel(tab2);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(340, 370, 191, 21));
        label_17->setStyleSheet(QString::fromUtf8("color: rgb(30, 41, 59);\n"
""));
        nom2 = new QLineEdit(tab2);
        nom2->setObjectName("nom2");
        nom2->setGeometry(QRect(340, 210, 371, 41));
        nom2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        b1_2 = new QPushButton(tab2);
        b1_2->setObjectName("b1_2");
        b1_2->setGeometry(QRect(910, 100, 81, 41));
        b1_2->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"font: 9pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
"\n"
""));
        mic1 = new QPushButton(tab2);
        mic1->setObjectName("mic1");
        mic1->setGeometry(QRect(750, 210, 61, 41));
        mic1->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"font: 9pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
"\n"
""));
        b1_4 = new QPushButton(tab2);
        b1_4->setObjectName("b1_4");
        b1_4->setGeometry(QRect(750, 310, 61, 41));
        b1_4->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"font: 9pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
"\n"
""));
        b1_6 = new QPushButton(tab2);
        b1_6->setObjectName("b1_6");
        b1_6->setGeometry(QRect(750, 510, 61, 41));
        b1_6->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"font: 9pt \"Segoe UI\";\n"
"background-color: rgb(37, 99, 235);\n"
"\n"
""));
        tabWidget->addTab(tab2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        stat = new QLabel(tab_3);
        stat->setObjectName("stat");
        stat->setGeometry(QRect(110, 60, 481, 371));
        verticalLayoutWidget = new QWidget(tab_3);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(690, 50, 321, 371));
        lay = new QVBoxLayout(verticalLayoutWidget);
        lay->setObjectName("lay");
        lay->setContentsMargins(0, 0, 0, 0);
        tabWidget->addTab(tab_3, QString());
        label = new QLabel(dashbored);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 161, 751));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"border-radius: 15px;"));
        pushButton_6 = new QPushButton(dashbored);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(20, 500, 141, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"font: 12pt \"Sitka\";\n"
"border-color: rgb(37, 99, 235);\n"
"color: rgb(218, 221, 239);"));
        pushButton = new QPushButton(dashbored);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 210, 141, 41));
        pushButton->setStyleSheet(QString::fromUtf8("font: 12pt \"Sitka\";\n"
"color: rgb(218, 221, 239);\n"
"border-color: rgb(37, 99, 235);\n"
""));
        logo = new QLabel(dashbored);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(30, 60, 141, 121));
        logo->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);"));
        logo->setPixmap(QPixmap(QString::fromUtf8("../../Projet c++/revision qt/template/image4.png")));
        pushButton_4 = new QPushButton(dashbored);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(20, 360, 141, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);font: 12pt \"Sitka\";\n"
"border-color: rgb(37, 99, 235);\n"
"color: rgb(218, 221, 239);"));
        pushButton_3 = new QPushButton(dashbored);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(20, 290, 141, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"font: 12pt \"Sitka\";\n"
"border-color: rgb(37, 99, 235);\n"
"color: rgb(218, 221, 239);"));
        pushButton_5 = new QPushButton(dashbored);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(20, 430, 141, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"font: 12pt \"Sitka\";\n"
"border-color: rgb(37, 99, 235);\n"
"color: rgb(218, 221, 239);"));
        label_3 = new QLabel(dashbored);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(140, 10, 1141, 71));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"border-radius: 15px;"));
        img1 = new QLabel(dashbored);
        img1->setObjectName("img1");
        img1->setGeometry(QRect(1210, 20, 51, 51));
        img1->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);"));
        img1->setPixmap(QPixmap(QString::fromUtf8("../../Projet c++/revision qt/template/image5.png")));
        pushButton_7 = new QPushButton(dashbored);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(480, 20, 461, 51));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 23, 42);\n"
"border-color: rgb(37, 99, 235);\n"
"font: 18pt \"Sitka\";\n"
"color: rgb(218, 221, 239);\n"
""));
        username = new QLabel(dashbored);
        username->setObjectName("username");
        username->setGeometry(QRect(1060, 30, 151, 31));
        username->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(15, 23, 42);\n"
"font: 12pt \"Sitka\";\n"
"color: rgb(218, 221, 239);"));

        retranslateUi(dashbored);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(dashbored);
    } // setupUi

    void retranslateUi(QWidget *dashbored)
    {
        dashbored->setWindowTitle(QCoreApplication::translate("dashbored", "Form", nullptr));
        label_11->setText(QCoreApplication::translate("dashbored", "\302\251 2025 Acme, Inc. All rights reserved.", nullptr));
        label_6->setText(QCoreApplication::translate("dashbored", "Profile", nullptr));
        label_12->setText(QCoreApplication::translate("dashbored", "Your name:", nullptr));
        label_9->setText(QCoreApplication::translate("dashbored", "Your email:", nullptr));
        label_10->setText(QCoreApplication::translate("dashbored", "Your poste:", nullptr));
        label_8->setText(QCoreApplication::translate("dashbored", "Your password:", nullptr));
        pushButton_8->setText(QCoreApplication::translate("dashbored", "Update your account", nullptr));
        pwd->setText(QCoreApplication::translate("dashbored", "User password", nullptr));
        img4->setText(QString());
        email->setText(QCoreApplication::translate("dashbored", "User last name", nullptr));
        nom->setText(QCoreApplication::translate("dashbored", "User first name", nullptr));
        post->setItemText(0, QCoreApplication::translate("dashbored", "Agriculture", nullptr));
        post->setItemText(1, QCoreApplication::translate("dashbored", "IT", nullptr));

        ppwd->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("dashbored", "Profile", nullptr));
        QTableWidgetItem *___qtablewidgetitem = list->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("dashbored", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = list->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("dashbored", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = list->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("dashbored", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = list->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("dashbored", "poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = list->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("dashbored", "password", nullptr));
        label_18->setText(QCoreApplication::translate("dashbored", "All Worker", nullptr));
        label_19->setText(QCoreApplication::translate("dashbored", "Delete Worker", nullptr));
        label_20->setText(QCoreApplication::translate("dashbored", "Id", nullptr));
        pushButton_10->setText(QCoreApplication::translate("dashbored", "Delete", nullptr));
        label_21->setText(QCoreApplication::translate("dashbored", "Id", nullptr));
        st->setText(QCoreApplication::translate("dashbored", "Sort", nullptr));
        sort->setText(QCoreApplication::translate("dashbored", "Sort", nullptr));
        cb->setItemText(0, QCoreApplication::translate("dashbored", "ID_EMP", nullptr));
        cb->setItemText(1, QCoreApplication::translate("dashbored", "EMAIL", nullptr));
        cb->setItemText(2, QCoreApplication::translate("dashbored", "NOM", nullptr));

        label_22->setText(QCoreApplication::translate("dashbored", "Search :", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("dashbored", "All Worker", nullptr));
        label_13->setText(QCoreApplication::translate("dashbored", "Add Worker", nullptr));
        pushButton_9->setText(QCoreApplication::translate("dashbored", "Add worker", nullptr));
        post2->setItemText(0, QCoreApplication::translate("dashbored", "Agriculture", nullptr));
        post2->setItemText(1, QCoreApplication::translate("dashbored", "IT", nullptr));

        img2_2->setText(QString());
        pwd2->setText(QString());
        image5->setText(QString());
        email2->setText(QString());
        label_14->setText(QCoreApplication::translate("dashbored", "Worker name:", nullptr));
        label_15->setText(QCoreApplication::translate("dashbored", "Worker email:", nullptr));
        label_16->setText(QCoreApplication::translate("dashbored", "Worker password:", nullptr));
        label_17->setText(QCoreApplication::translate("dashbored", "Worker poste:", nullptr));
        nom2->setText(QString());
        b1_2->setText(QCoreApplication::translate("dashbored", "Sign up", nullptr));
        mic1->setText(QCoreApplication::translate("dashbored", "Mic", nullptr));
        b1_4->setText(QCoreApplication::translate("dashbored", "Mic", nullptr));
        b1_6->setText(QCoreApplication::translate("dashbored", "Mic", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QCoreApplication::translate("dashbored", "Add Worker", nullptr));
        stat->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("dashbored", "Statistic", nullptr));
        label->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("dashbored", "Project", nullptr));
        pushButton->setText(QCoreApplication::translate("dashbored", "Account", nullptr));
        logo->setText(QString());
        pushButton_4->setText(QCoreApplication::translate("dashbored", "Reservation", nullptr));
        pushButton_3->setText(QCoreApplication::translate("dashbored", "Client", nullptr));
        pushButton_5->setText(QCoreApplication::translate("dashbored", "Sponcor", nullptr));
        label_3->setText(QString());
        img1->setText(QString());
        pushButton_7->setText(QCoreApplication::translate("dashbored", "Account", nullptr));
        username->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class dashbored: public Ui_dashbored {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBORED_H
