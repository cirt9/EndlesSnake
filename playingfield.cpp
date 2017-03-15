#include "playingfield.h"

PlayingField::PlayingField(int screenW, int screenH, Player * playerAddress, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, screenW, screenHeight);
    setPen(Qt::NoPen);

    player = playerAddress;
    screenWidth = screenW;
    screenHeight  = screenH;

    moveTimer = nullptr;
    spawnAndScoreTimer = nullptr;

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

void PlayingField::startMovingAndSpawningObjects()
{
    moveTimer = new QTimer(this);
    moveTimer->start(numberOfmsUntilMoveTimeout);

    spawnAndScoreTimer = new QTimer(this);
    spawnAndScoreTimer->start(numberOfmsUntilSpawnTimeout);

    connect(spawnAndScoreTimer, &QTimer::timeout, this, [this]{player->increaseScore(pointsPerTimeout);} );
    connect(spawnAndScoreTimer, SIGNAL(timeout()), this, SLOT(spawner()));
}

void PlayingField::spawner()
{
    int pointsToSpawnMustToCatchFood = 200;

    if(player->getScore() % pointsToSpawnMustToCatchFood == 0)
        spawnMustToCatchFood();

    //spawn obstacles but player must have possibility to avoid obstacles

    //spawn bonus food but not colliding with obstacles
}

void PlayingField::spawnMustToCatchFood()
{
    spawnFood();

    int obstacleWidth = mainField->rect().width()/2 - player->getPlayerCharacter()->getSnakeWidth();
    int obstacleHeight = 50;
    int obstacleSpeed = 1;

    Obstacle * leftObstacle = new Obstacle(obstacleWidth, obstacleHeight, obstacleSpeed, screenWidth, screenHeight, QColor(153, 0, 0), moveTimer, this);
    Obstacle * rightObstacle = new Obstacle(obstacleWidth, obstacleHeight, obstacleSpeed, screenWidth, screenHeight, QColor(153, 0, 0), moveTimer, this);

    leftObstacle->setPos(mainField->x(), 0);
    rightObstacle->setPos(mainField->x() + mainField->rect().width() - obstacleWidth, 0);
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
    int positionX = mainField->x() + mainField->rect().width() / 2 - food->rect().width()/2;
    int positionY = 0;

    food->setPos(positionX, positionY);
}

void PlayingField::spawnObstacle()
{
    int obstacleWidth = 100;
    int obstacleHeight = 30;
    int obstacleSpeed = 1;
    Obstacle * newObstacle = new Obstacle(obstacleWidth, obstacleHeight, obstacleSpeed, screenWidth, screenHeight, QColor(153, 0, 0), moveTimer, this);

    setRandomPositionToObstacle(newObstacle);
}

void PlayingField::setRandomPositionToObstacle(Obstacle *obstacle)
{
    int randomRange = mainField->rect().width() - obstacle->rect().width();
    int positionX = mainField->x() + rand() % randomRange;
    int positionY = 0;

    obstacle->setPos(positionX, positionY);
}
