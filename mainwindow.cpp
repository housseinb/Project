#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tacheamine.h"
#include "ui_tacheamine.h"
#include "sponsor.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDebug>
#include <QMarginsF>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <cmath>
#include <QDateTime>
#include <QScrollBar>
#include "chatbot.h"
#include <QPrinter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QPageSize>
#include <QPageLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QSqlTableModel(this)),
    tacheamineWindow(nullptr) // initialize pointer
{
    ui->setupUi(this);

    // Connect button to open tacheamine window
    connect(ui->go, &QPushButton::clicked, this, [this]() {
        tacheamineWindow = new tacheamine(); // Create the window
        tacheamineWindow->show();            // Show the new window
        this->hide();                        // Hide the main window (optional)
    });
}

MainWindow::~MainWindow()
{
    delete model;
    delete ui;
    if (tacheamineWindow) delete tacheamineWindow;
}

void MainWindow::setupUI()
{
    // Your UI setup code here
}

void MainWindow::loadTableData()
{
    // Your data loading code here
}

void MainWindow::setupConnections()
{
    // Your connections setup here
}

void MainWindow::checkDatabaseConnection()
{
    // Your DB checking code here
}

void MainWindow::scrollToBottom()
{
    // Your scroll code here
}
