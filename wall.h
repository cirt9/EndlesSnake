#ifndef WALL_H
#define WALL_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

class Wall : public QGraphicsRectItem
{
private:
    int x;
    int y;
    int width;
    int height;

public:
    Wall(int wallX, int wallY, int wallWidth, int wallHeight, QColor color, QGraphicsItem * parent = nullptr);
    ~Wall() {}

    int getWidth() const;
    int getHeight() const;
    int getX() const;
    int getY() const;
};

#endif // WALL_H
