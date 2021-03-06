#include "playingfield.h"

PlayingField::PlayingField(int screenW, int screenH, Player * playerAddress, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, screenW, screenHeight);
    setPen(Qt::NoPen);

    player = playerAddress;
    screenWidth = screenW;
    screenHeight  = screenH;

    moveTimer = new QTimer(this);
    spawnAndScoreTimer = new QTimer(this);

    numberOfmsUntilMoveTimeout = 5;

    setMainField(screenW, screenHeight, QColor(56, 122, 54));
    setWalls(screenW, screenHeight, QColor(0, 70, 0));

    spawningGap = mainField->rect().width() / 1.9;
}

void PlayingField::setMainField(int width, int height, QColor color)
{
    int mainFieldWidth = 650;
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
    int wallWidth = (width - mainField->rect().width()) / 2;
    int rightWallX = width - wallWidth;

    leftWall = new Wall(0, 0, wallWidth, height, wallColor, this);
    rightWall = new Wall(rightWallX, 0, wallWidth, height, wallColor, this);
}

void PlayingField::startMovingAndSpawningObjects()
{
    moveTimer->start(numberOfmsUntilMoveTimeout);
    spawnAndScoreTimer->start(numberOfmsUntilSpawnTimeout);

    connect(spawnAndScoreTimer, &QTimer::timeout, this, [this]{player->increaseScore(pointsPerTimeout);} );
    connect(spawnAndScoreTimer, SIGNAL(timeout()), this, SLOT(spawner()));
}

void PlayingField::spawner()
{
    int pointsToSpawnFood = 40;
    int pointsToReduceGap = 75;
    int pointsToIncreaseSpeed = 200;
    int maxNumberOfObstacles = 3;
    int obstaclesInSpawningRange = getNumberOfObstaclesInSpawningRange();

    if(obstaclesInSpawningRange < maxNumberOfObstacles)
        spawnObstacle();

    else if(player->getScore() % pointsToSpawnFood == 0)
        spawnFood();

    if(player->getScore() % pointsToReduceGap == 0)
        decreaseSpawningGap();

    if(player->getScore() % pointsToIncreaseSpeed == 0)
        decreaseNumberOfmsUntilMoveTimeout();
}

int PlayingField::getNumberOfObstaclesInSpawningRange()
{
    int obstaclesInSpawningRange = 0;
    QList<QGraphicsItem *> objectsOnBoard = mainField->collidingItems();

    for(auto object : objectsOnBoard)
    {
        if(typeid(*object) == typeid(Obstacle))
        {
            Obstacle * obstacle = dynamic_cast<Obstacle *>(object);
            if(obstacle->y() < player->getPlayerCharacter()->getSnakeLength() + spawningGap)
                obstaclesInSpawningRange++;
        }
    }
    return obstaclesInSpawningRange;
}

void PlayingField::decreaseSpawningGap()
{
    if(spawningGap > mainField->rect().width() / 1.5)
        spawningGap -= mainField->rect().width() / 21;
}

void PlayingField::decreaseNumberOfmsUntilMoveTimeout()
{
    if(numberOfmsUntilMoveTimeout > 3)
    {
        numberOfmsUntilMoveTimeout -= 1;
        moveTimer->setInterval(numberOfmsUntilMoveTimeout);
    }

    else if(player->getScore() % 800 == 0)
    {
        numberOfmsUntilMoveTimeout -= 1;
        moveTimer->setInterval(numberOfmsUntilMoveTimeout);
    }
}

void PlayingField::spawnFood()
{
    int foodSize = mainField->rect().width() / 21;
    int foodSpeed = 1;
    Food * newFood = new Food(foodSize, foodSize, foodSpeed, screenWidth, screenHeight, QColor(255, 255, 0), moveTimer, this);

    setPositionOfFood(newFood);
}

void PlayingField::setPositionOfFood(Food * food)
{
    int xRange = mainField->rect().width() - food->rect().width();
    int positionX = mainField->x() + rand() % xRange;
    int positionY = 0 - food->rect().height();

    food->setPos(positionX, positionY);

    if(food->collidesWithObstacle())
        delete food;
}

void PlayingField::spawnObstacle()
{
    int rangeLimiter = mainField->rect().height() / 3;
    int numberOfSpawnedObstacles = 3;

    int widthRange = (mainField->rect().width() - rangeLimiter) / numberOfSpawnedObstacles;
    int heightRange = mainField->rect().height() / 16;
    int minimunWidth = mainField->rect().height() / 20;
    int minimumHeight = mainField->rect().height() / 37;

    int obstacleWidth = rand() % widthRange + minimunWidth;
    int obstacleHeight = rand() % heightRange + minimumHeight;
    int obstacleSpeed = 1;
    Obstacle * newObstacle = new Obstacle(obstacleWidth, obstacleHeight, obstacleSpeed, screenWidth, screenHeight,
                                          QColor(153, 0, 0), moveTimer, this);

    setRandomPositionToObstacle(newObstacle);
}

void PlayingField::setRandomPositionToObstacle(Obstacle *obstacle)
{
    int randomRange = mainField->rect().width() - obstacle->rect().width();
    int positionX = mainField->x() + rand() % randomRange;
    int positionY = 0 - obstacle->rect().height();

    obstacle->setPos(positionX, positionY);
}

void PlayingField::pause()
{
    moveTimer->stop();
    spawnAndScoreTimer->stop();
}

void PlayingField::resume()
{
    moveTimer->start();
    spawnAndScoreTimer->start();
}
