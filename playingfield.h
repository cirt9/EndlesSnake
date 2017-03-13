#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <QGraphicsRectItem>
#include <wall.h>
#include <QPen>
#include <QBrush>
#include <player.h>
#include <food.h>
#include <obstacle.h>
#include <QTimer>
#include <QTime>

class PlayingField : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    Wall * leftWall;
    QGraphicsRectItem * mainField;
    Wall * rightWall;
    Player * player;
    QTimer * moveTimer;

    int screenWidth;
    int screenHeight;

    void setMainField(int width, int height, QColor color);
    void setWalls(int width, int height, QColor wallColor);

    void setPositionOfFood(Food * food);

    void setPositionOfObstacle(Obstacle * obstacle);

public:
    PlayingField(int screenW, int screenH, Player * playerAddress, QGraphicsItem * parent = nullptr);
    ~PlayingField() {}

    void spawnFood();
    void spawnObstacle();
};

#endif // PLAYINGFIELD_H
