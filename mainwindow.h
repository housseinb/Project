#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool triAscendant = true;
private slots:

    void on_b3_clicked();
    void on_b1_clicked();
    void on_b2_clicked();
    void on_b22_clicked();
    void on_pushButton_16_clicked();
    void on_b11_clicked();
    void on_b2_3_clicked();
    void on_b1_3_clicked();
    void on_b2_5_clicked();
    void on_pushButton_18_clicked();
    void on_b22_3_clicked();
    void on_b11_3_clicked();
    void on_b3_3_clicked();
    void on_b2_4_clicked();
    void on_re_textChanged(const QString &arg1);
    void on_btrie_clicked();
    void on_btrie_2_clicked();
    void on_pdf_clicked();
    void on_gen_clicked();
    void on_pdf_2_clicked();
    void setupBMCDisplay();

    void on_gen_2_clicked();
    void on_tabWidget_tabBarClicked(int index);
};
#endif // MAINWINDOW_H
