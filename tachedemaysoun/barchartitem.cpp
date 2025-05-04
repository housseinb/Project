#ifndef BARCHARTITEM_H
#define BARCHARTITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class BarChartItem : public QGraphicsItem {
public:
    BarChartItem(int under1000, int between1000And10000, int above10000, QGraphicsItem *parent = nullptr)
        : QGraphicsItem(parent), under1000Count(under1000), between1000And10000Count(between1000And10000), above10000Count(above10000) {}

    QRectF boundingRect() const override {
        return QRectF(0, 0, 300, 200); // Increase the width and height for a larger chart
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        painter->setRenderHint(QPainter::Antialiasing);

        // Bar dimensions
        int barWidth = 80;
        int gap = 40;
        int maxHeight = 150;
        int under1000Height = static_cast<int>(static_cast<double>(under1000Count) / (under1000Count + between1000And10000Count + above10000Count) * maxHeight);
        int between1000And10000Height = static_cast<int>(static_cast<double>(between1000And10000Count) / (under1000Count + between1000And10000Count + above10000Count) * maxHeight);
        int above10000Height = static_cast<int>(static_cast<double>(above10000Count) / (under1000Count + between1000And10000Count + above10000Count) * maxHeight);

        // Draw Under 1000 Bar
        painter->setBrush(QColor(0, 128, 0)); // Green for Under 1000
        painter->drawRect(0, maxHeight - under1000Height, barWidth, under1000Height);

        // Draw 1000 to 10000 Bar
        painter->setBrush(QColor(0, 0, 255)); // Blue for 1000 to 10000
        painter->drawRect(barWidth + gap, maxHeight - between1000And10000Height, barWidth, between1000And10000Height);

        // Draw Above 10000 Bar
        painter->setBrush(QColor(255, 0, 0)); // Red for Above 10000
        painter->drawRect((barWidth + gap) * 2, maxHeight - above10000Height, barWidth, above10000Height);

        // Draw Labels
        painter->setPen(QColor(0, 0, 0)); // Black for text
        painter->drawText(0, maxHeight + 15, "Under 1000");
        painter->drawText(barWidth + gap, maxHeight + 15, "1000 to 10000");
        painter->drawText((barWidth + gap) * 2, maxHeight + 15, "Above 10000");
    }

private:
    int under1000Count;
    int between1000And10000Count;
    int above10000Count;
};

#endif // BARCHARTITEM_H
