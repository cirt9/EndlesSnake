#ifndef WALL_H
#define WALL_H

#include <QGraphicsRectItem>
#include <QBrush>

class Wall : public QGraphicsRectItem
{
public:
    Wall(int x, int y, int width, int height, QColor color, QGraphicsItem * parent = nullptr);
    ~Wall() {}
};

#endif // WALL_H
