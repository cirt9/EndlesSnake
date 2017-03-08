#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QTimer>
#include <QList>
#include <typeinfo>
#include <snake.h>

class Food : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    int moveSpeed;
    QTimer * moveTimer;
    int screenWidth;
    int screenHeight;

    void handleCollisionWithPlayer();

private slots:
    void move();

public:
    Food(int foodWidth, int foodHeight, int speed, int screenW, int screenH, QColor color, QTimer * timer, QGraphicsItem * parent = nullptr);
};

#endif // FOOD_H
