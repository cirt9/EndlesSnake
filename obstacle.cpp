#include "obstacle.h"

Obstacle::Obstacle(int obstacleWidth, int obstacleHeight, int speed, int screenW, int screenH, QColor color, QTimer * timer, QGraphicsItem * parent) : QGraphicsRectItem(parent)
{
    moveTimer = timer;
    moveSpeed = speed;
    screenWidth = screenW;
    screenHeight = screenH;

    setRect(0, 0, obstacleWidth, obstacleHeight);

    setBrush(QBrush(color));
    setPen(Qt::NoPen);

    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
}

void Obstacle::move()
{
    setPos(x(), y() + moveSpeed);
    handleCollisionWithPlayer();

    if(y() > screenHeight)
        this->deleteLater();
}

void Obstacle::handleCollisionWithPlayer()
{
    QList<QGraphicsItem *> collidesWith = collidingItems();

    for(auto collidingItem : collidesWith)
    {
        if(typeid(*collidingItem) == typeid(Snake))
        {
            Snake * collidingPlayer = dynamic_cast<Snake *>(collidingItem);

            disconnect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
            emit collidingPlayer->defeated();

            break;
        }
    }
}
