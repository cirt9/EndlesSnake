#include "snake.h"

Snake::Snake(int movementSpeed, int snakeSize, int x, int y, QColor snakeColor, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    speed = movementSpeed;
    snakeLength = snakeSize;
    snakeWidth = snakeSize;
    lengthGrowth =  snakeWidth / 2;

    setRect(0, 0, snakeWidth, snakeLength);
    setPos(x, y);
    QBrush color(snakeColor);
    setBrush(color);
    setPen(Qt::NoPen);
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

void Snake::grow()
{
    snakeLength += lengthGrowth;

    setRect(0, 0, snakeWidth, snakeLength);
    setPos(x(), y() - lengthGrowth);
}

int Snake::getSnakeLength() const
{
    return snakeLength;
}

int Snake::getSnakeWidth() const
{
    return snakeWidth;
}


