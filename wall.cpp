#include "wall.h"

Wall::Wall(int x, int y, int width, int height, QColor color, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(x, y, width, height);

    QBrush wallColor(color);
    setBrush(wallColor);
}
