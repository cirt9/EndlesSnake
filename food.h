#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QTimer>
#include <QList>
#include <typeinfo>
#include <snake.h>
#include <obstacle.h>

class Food : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    int moveSpeed;
    int screenWidth;
    int screenHeight;

    void handleCollisionWithPlayer();

private slots:
    void move();

public:
    Food(int foodWidth, int foodHeight, int speed, int screenW, int screenH, QColor color, QTimer * timer, QGraphicsItem * parent = nullptr);
    ~Food() {}

    bool collidesWithObstacle();
};

#endif // FOOD_H
