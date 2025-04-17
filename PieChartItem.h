#ifndef PIECHARTITEM_H
#define PIECHARTITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class PieChartItem : public QGraphicsItem {
public:
    PieChartItem(int agriculture, int it, QGraphicsItem *parent = nullptr)
        : QGraphicsItem(parent), agricultureCount(agriculture), itCount(it) {}

    QRectF boundingRect() const override {
        return QRectF(-100, -100, 200, 200); // Size of the pie chart
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        painter->setRenderHint(QPainter::Antialiasing);

        int total = agricultureCount + itCount;
        int agricultureAngle = (total > 0) ? static_cast<int>(360.0 * agricultureCount / total) : 0;
        int itAngle = (total > 0) ? static_cast<int>(360.0 * itCount / total) : 0;

        // Draw segments
        painter->setBrush(QColor(0, 128, 0)); // Agriculture color
        painter->drawPie(-100, -100, 200, 200, 90 * 16, -agricultureAngle * 16);

        painter->setBrush(QColor(0, 0, 255)); // IT color
        painter->drawPie(-100, -100, 200, 200, (90 - agricultureAngle) * 16, -itAngle * 16);

        // Draw labels (you may want to calculate positions based on angles)
        painter->setPen(QColor(0, 0, 0)); // Black color for labels
        painter->drawText(0, 0, "Agriculture: " + QString::number(agricultureCount));
        painter->drawText(50, -50, "IT: " + QString::number(itCount));
    }

private:
    int agricultureCount;
    int itCount;
};

#endif // PIECHARTITEM_H
