#ifndef TAXHEDEMAYSSOUN_H
#define TAXHEDEMAYSSOUN_H

#include <QWidget>

namespace Ui {
class taxhedemayssoun;
}

class taxhedemayssoun : public QWidget
{
    Q_OBJECT

public:
    explicit taxhedemayssoun(QWidget *parent = nullptr);
    ~taxhedemayssoun();

private slots:
    void on_b3_2_clicked();

    void on_b1_2_clicked();

    void on_b2_2_clicked();

    void on_b22_2_clicked();

    void on_b11_2_clicked();

    void on_pushButton_17_clicked();

    void on_b2_6_clicked();

    void on_b1_4_clicked();

    void on_b2_8_clicked();

    void on_b3_4_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pdf_2_clicked();

    void on_btrie_2_clicked();

    void on_re_2_cursorPositionChanged(int arg1, int arg2);

    void on_b2_7_clicked();

    void on_gen_3_clicked();

    void on_gen_4_clicked();

private:
    void loadProjects();
    bool triAscendant = true;
    Ui::taxhedemayssoun *ui;
};

#endif // TAXHEDEMAYSSOUN_H
