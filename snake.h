#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QKeyEvent>
#include <QList>
#include <typeinfo>
#include <wall.h>
#include <QPen>

class Snake : public QGraphicsRectItem
{
private:
    int speed;

    void keyPressEvent(QKeyEvent * event = nullptr);
    void handleCollisionWithWallWhenMovingLeft();
    void handleCollisionWithWallWhenMovingRight();

public:
    Snake(int movementSpeed = 10, int snakeSize = 50, int x = 0, int y = 0,  QColor snakeColor = QColor(0,0,0), QGraphicsItem * parent = nullptr);
    ~Snake() {}

};

#endif // SNAKE_H
