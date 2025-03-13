// ChartWidget.h
#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QPainter>

class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = nullptr);
    void setFilledCells(int filledCells, int totalCells);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_filledCells;
    int m_totalCells;
};

#endif // CHARTWIDGET_H
