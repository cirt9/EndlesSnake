#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QTimer>
#include <QList>
#include <typeinfo>
#include <snake.h>

class Obstacle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    QTimer * moveTimer;
    int moveSpeed;
    int screenWidth;
    int screenHeight;

    void handleCollisionWithPlayer();

private slots:
    void move();

public:
    Obstacle(int obstacleWidth, int obstacleHeight, int speed, int screenW, int screenH, QColor color, QTimer * timer, QGraphicsItem * parent = nullptr);
    Obstacle() {}
};

#endif // OBSTACLE_H
