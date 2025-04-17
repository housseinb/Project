#ifndef BARCHARTITEM_H
#define BARCHARTITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class BarChartItem : public QGraphicsItem {
public:
    BarChartItem(int agriculture, int it, QGraphicsItem *parent = nullptr)
        : QGraphicsItem(parent), agricultureCount(agriculture), itCount(it) {}

    QRectF boundingRect() const override {
        return QRectF(0, 0, 300, 200); // Increase the width and height for a larger chart
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        painter->setRenderHint(QPainter::Antialiasing);

        // Bar dimensions
        int barWidth = 80; // Increase bar width
        int gap = 40; // Increase gap between bars
        int maxHeight = 150; // Max height for scaling
        int agricultureHeight = static_cast<int>(static_cast<double>(agricultureCount) / (agricultureCount + itCount) * maxHeight);
        int itHeight = static_cast<int>(static_cast<double>(itCount) / (agricultureCount + itCount) * maxHeight);

        // Draw Agriculture Bar
        painter->setBrush(QColor(0, 128, 0)); // Green for Agriculture
        painter->drawRect(0, maxHeight - agricultureHeight, barWidth, agricultureHeight);

        // Draw IT Bar
        painter->setBrush(QColor(0, 0, 255)); // Blue for IT
        painter->drawRect(barWidth + gap, maxHeight - itHeight, barWidth, itHeight);

        // Draw Labels
        painter->setPen(QColor(0, 0, 0)); // Black for text
        painter->drawText(0, maxHeight + 15, "Agriculture");
        painter->drawText(barWidth + gap, maxHeight + 15, "IT");
    }

private:
    int agricultureCount;
    int itCount;
};

#endif // BARCHARTITEM_H
