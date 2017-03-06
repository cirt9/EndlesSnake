#include "playingfield.h"

PlayingField::PlayingField(int screenWidth, int screenHeight, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, screenWidth, screenHeight);
    setPen(Qt::NoPen);

    setMainField(screenWidth, screenHeight, QColor(56, 122, 54));
    setWalls(screenWidth, screenHeight, QColor(0, 70, 0));
}

void PlayingField::setMainField(int width, int height, QColor color)
{
    int mainFieldWidth = width/3;
    int mainFieldHeight = height;
    int mainFieldPositionX = width/2 - mainFieldWidth/2;

    mainField = new QGraphicsRectItem(mainFieldPositionX, 0, mainFieldWidth, mainFieldHeight, this);

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
