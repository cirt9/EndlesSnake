#include "backgroundpanel.h"

BackgroundPanel::BackgroundPanel(int x, int y, int width, int height, QColor color, double opacity, QGraphicsItem * parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, width, height);

    QBrush panelColor(color, Qt::SolidPattern);
    setBrush(panelColor);

    setOpacity(opacity);
    setPos(x, y);
}
