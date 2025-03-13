// ChartWidget.cpp
#include "ChartWidget.h"

ChartWidget::ChartWidget(QWidget *parent) : QWidget(parent), m_filledCells(0), m_totalCells(1)
{
    setFixedSize(200, 200);
    setStyleSheet("background-color: white;");
    setAutoFillBackground(true);
}

void ChartWidget::setFilledCells(int filledCells, int totalCells)
{
    m_filledCells = filledCells;
    m_totalCells = totalCells;
    update();  // Demande une nouvelle mise à jour du widget
}

void ChartWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int totalCells = m_totalCells;
    int filledCells = m_filledCells;

    int filledAngle = 360 * filledCells / totalCells;
    int emptyAngle = 360 - filledAngle;

    // Dessiner la portion remplie
    painter.setBrush(QBrush(Qt::green));
    painter.drawPie(10, 10, 180, 180, 90 * 16, -filledAngle * 16);

    // Dessiner la portion vide
    painter.setBrush(QBrush(Qt::red));
    painter.drawPie(10, 10, 180, 180, (90 + filledAngle) * 16, -emptyAngle * 16);
}
