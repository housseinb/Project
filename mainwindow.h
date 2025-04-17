#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sign_up.h"  // Ensure this header exists and is correct

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);  // Constructor
    ~MainWindow();  // Destructor

private slots:
    void on_pushButton_2_clicked();  // Button to display SignUp page
    void on_b1_clicked();  // Logic for button 1 click
    void on_b1_2_clicked();  // Logic for button 2 click

    void on_pwd_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;  // Pointer to the UI class
    Sign_Up *signupPage;  // Pointer to the SignUp page class
};

#endif // MAINWINDOW_H
