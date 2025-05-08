#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nour.h"  // Include Nour header

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , nourWidget(nullptr) // ✅ initialize
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
    if (nourWidget) delete nourWidget;  // Cleanup
}

void MainWindow::on_pushButton_clicked()
{
    if (!nourWidget) {
        nourWidget = new Nour(this); // ✅ Create Nour window only once
        nourWidget->show();
    } else {
        nourWidget->raise();          // ✅ Bring it to front if already open
        nourWidget->activateWindow();
    }
}
