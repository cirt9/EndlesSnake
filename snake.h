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
    int lengthGrowth;

    int speed;
    int snakeLength;
    int snakeWidth;
    bool movingAllowed;

    void handleCollisionWithWallWhenMovingLeft();
    void handleCollisionWithWallWhenMovingRight();

public:
    Snake(int movementSpeed = 10, int snakeSize = 50, int x = 0, int y = 0,  QColor snakeColor = QColor(0,0,0), QGraphicsItem * parent = nullptr);
    ~Snake() {}

    void grow();

    int getSnakeLength() const;
    int getSnakeWidth() const;

    void keyPressEvent(QKeyEvent * event = nullptr);

    void changeMovingAllowed();

signals:
    void defeated();
};

#endif // SNAKE_H
