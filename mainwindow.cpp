#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , nourWindow(nullptr)
{
    ui->setupUi(this);

    // Connect the Client button (e.g., named pushButton_client) to the slot
    connect(ui->clientButton, &QPushButton::clicked, this, &MainWindow::showNour);
}

void MainWindow::showNour() {
    if (!nourWindow) {
        qDebug() << "Opening Nour form...";
        nourWindow = new Nour(this); // `this` will keep it in memory as child
    }
    nourWindow->show(); // Show the new form
}
MainWindow::~MainWindow()
{
    delete ui;
}
