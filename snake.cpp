#include "snake.h"

Snake::Snake(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(800, 700, 70, 70);
    QBrush snakeColor(QColor(0,0,0));
    setBrush(snakeColor);
}

void Snake::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
        setPos(x()-30, y());

    else if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
        setPos(x()+30, y());
}
