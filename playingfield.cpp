#include "playingfield.h"

PlayingField::PlayingField(int screenW, int screenH, Player * playerAddress, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, screenW, screenHeight);
    setPen(Qt::NoPen);

    player = playerAddress;
    screenWidth = screenW;
    screenHeight  = screenH;

    moveTimer = new QTimer(this);
    moveTimer->start(3);

    setMainField(screenW, screenHeight, QColor(56, 122, 54));
    setWalls(screenW, screenHeight, QColor(0, 70, 0));
}

void PlayingField::setMainField(int width, int height, QColor color)
{
    int mainFieldWidth = width/3;
    int mainFieldHeight = height;
    int mainFieldPositionX = width/2 - mainFieldWidth/2;
    int mainFieldPositionY = 0;

    mainField = new QGraphicsRectItem(0, 0, mainFieldWidth, mainFieldHeight, this);
    mainField->setPos(mainFieldPositionX, mainFieldPositionY);

    mainField->setPen(Qt::NoPen);
    QBrush mainFieldColor(color);
    mainField->setBrush(mainFieldColor);
}

void PlayingField::setWalls(int width, int height, QColor wallColor)
{
    int wallWidth = width / 3;
    int rightWallX = width - wallWidth;

    leftWall = new Wall(0, 0, wallWidth, height, wallColor, this);
    rightWall = new Wall(rightWallX, 0, wallWidth, height, wallColor, this);
}

void PlayingField::spawnFood()
{
    int foodSize = 30;
    int foodSpeed = 1;
    Food * newFood = new Food(foodSize, foodSize, foodSpeed, screenWidth, screenHeight, QColor(255, 255, 0), moveTimer, this);

    setPositionOfFood(newFood);
}

void PlayingField::setPositionOfFood(Food * food)
{
    int positionX = screenWidth / 2;
    int positionY = 0;

    food->setPos(positionX, positionY);
}

void PlayingField::spawnObstacle()
{
    int obstacleWidth = 100;
    int obstacleHeight = 30;
    int obstacleSpeed = 1;
    Obstacle * newObstacle = new Obstacle(obstacleWidth, obstacleHeight, obstacleSpeed, screenWidth, screenHeight, QColor(153, 0, 0), moveTimer, this);

    setPositionOfObstacle(newObstacle);
}

void PlayingField::setPositionOfObstacle(Obstacle *obstacle)
{
    int randomRange = mainField->rect().width() - obstacle->rect().width();
    int positionX = mainField->x() + rand() % randomRange;
    int positionY = 0;

    obstacle->setPos(positionX, positionY);
}
