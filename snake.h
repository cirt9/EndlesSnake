#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QKeyEvent>
#include <QList>
#include <typeinfo>
#include <wall.h>
#include <QPen>

class Snake : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    const int lengthGrowth = 30;

    int speed;
    int snakeLength;
    int snakeWidth;

    void handleCollisionWithWallWhenMovingLeft();
    void handleCollisionWithWallWhenMovingRight();

public:
    Snake(int movementSpeed = 10, int snakeSize = 50, int x = 0, int y = 0,  QColor snakeColor = QColor(0,0,0), QGraphicsItem * parent = nullptr);
    ~Snake() {}

    void grow();

    void keyPressEvent(QKeyEvent * event = nullptr);

signals:
    void defeated();
};

#endif // SNAKE_H
