#include "wall.h"

Wall::Wall(int wallX, int wallY, int wallWidth, int wallHeight, QColor color, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    x = wallX;
    y = wallY;
    width = wallWidth;
    height = wallHeight;

    setRect(x, y, width, height);

    QBrush wallColor(color);
    setBrush(wallColor);
    setPen(Qt::NoPen);
}

int Wall::getWidth() const
{
    return width;
}

int Wall::getHeight() const
{
    return height;
}

int Wall::getX() const
{
    return x;
}

int Wall::getY() const
{
    return y;
}
