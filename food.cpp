#include "food.h"

Food::Food(int foodWidth, int foodHeight, int speed, int screenW, int screenH, QColor color,  QTimer * timer, QGraphicsItem * parent) : QGraphicsRectItem(parent)
{
    moveSpeed = speed;
    moveTimer = timer;
    screenWidth = screenW;
    screenHeight = screenH;

    setRect(0, 0, foodWidth, foodHeight);

    setBrush(QBrush(color));
    setPen(Qt::NoPen);

    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
}

void Food::move()
{
    setPos(x(), y() + moveSpeed);
    handleCollisionWithPlayer();

    if(y() > screenHeight)
        this->deleteLater();
}

void Food::handleCollisionWithPlayer()
{
    QList<QGraphicsItem *> collidesWith = collidingItems();

    for(auto collidingItem : collidesWith)
    {
        if(typeid(*collidingItem) == typeid(Snake))
        {
            Snake * collidingPlayer = dynamic_cast<Snake *>(collidingItem);

            collidingPlayer->grow();

            this->deleteLater();
            break;
        }
    }
}
