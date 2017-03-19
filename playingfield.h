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
#include <QList>
#include <typeinfo>

class PlayingField : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    Wall * leftWall;
    QGraphicsRectItem * mainField;
    Wall * rightWall;
    Player * player;

    QTimer * moveTimer;
    QTimer * spawnAndScoreTimer;

    const int pointsPerTimeout = 1;
    const int numberOfmsUntilSpawnTimeout = 100;
    double spawningGap;
    int numberOfmsUntilMoveTimeout;

    int screenWidth;
    int screenHeight;

    void setMainField(int width, int height, QColor color);
    void setWalls(int width, int height, QColor wallColor);

    void spawnFood();
    void setPositionOfFood(Food * food);

    void spawnObstacle();
    void setRandomPositionToObstacle(Obstacle * obstacle);

    int getNumberOfObstaclesInSpawningRange();

    void decreaseSpawningGap();
    void decreaseNumberOfmsUntilMoveTimeout();

private slots:
    void spawner();

public:
    PlayingField(int screenW, int screenH, Player * playerAddress, QGraphicsItem * parent = nullptr);
    ~PlayingField() {}

    void startMovingAndSpawningObjects();

    void pause();
    void resume();
};

#endif // PLAYINGFIELD_H
