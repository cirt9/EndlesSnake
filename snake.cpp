#include "snake.h"

Snake::Snake(int movementSpeed, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, 70, 70);
    setPos(800, 700);
    QBrush snakeColor(QColor(0,0,0));
    setBrush(snakeColor);

    speed = movementSpeed;
}

void Snake::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
    {
        setPos(x()-speed, y());
        handleCollisionWithWallWhenMovingLeft();
    }

    else if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
    {
        setPos(x()+speed, y());
        handleCollisionWithWallWhenMovingRight();
    }
}

void Snake::handleCollisionWithWallWhenMovingLeft()
{
    QList<QGraphicsItem *> collidesWith = collidingItems();

    for(auto collidingItem : collidesWith)
    {
        if(typeid(*collidingItem) == typeid(Wall))
        {
            Wall * collidingWall = dynamic_cast<Wall *>(collidingItem);

            int positionOfTheRightSideOfWall = collidingWall->getWidth();
            setPos(positionOfTheRightSideOfWall, y());

            break;
        }
    }
}

void Snake::handleCollisionWithWallWhenMovingRight()
{
    QList<QGraphicsItem *> collidesWith = collidingItems();

    for(auto collidingItem : collidesWith)
    {
        if(typeid(*collidingItem) == typeid(Wall))
        {
            Wall * collidingWall = dynamic_cast<Wall *>(collidingItem);

            int positionOfTheLeftSideOfWall = collidingWall->getX() - rect().width();
            setPos(positionOfTheLeftSideOfWall, y());

            break;
        }
    }
}


