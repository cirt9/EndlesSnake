#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QKeyEvent>
#include <QList>
#include <typeinfo>
#include <wall.h>

class Snake : public QGraphicsRectItem
{
private:
    int speed;

    void keyPressEvent(QKeyEvent * event = nullptr);
    void handleCollisionWithWallWhenMovingLeft();
    void handleCollisionWithWallWhenMovingRight();

public:
    Snake(int movementSpeed = 10, QGraphicsItem * parent = nullptr);

};

#endif // SNAKE_H
