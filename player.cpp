#include "player.h"

Player::Player(int screenWidth, int screenHeight, QGraphicsItem * parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, screenWidth, screenHeight);
    setPen(Qt::NoPen);

    playerName = QString("I'm the best");
    playerCharacter = nullptr;
    score = 0;
}

void Player::setPlayerCharacter(int movementSpeed, int characterSize, int x, int y, QColor characterColor)
{
    playerCharacter = new Snake(movementSpeed, characterSize, x, y, characterColor, this);
}

void Player::setPlayerName(QString name)
{
    playerName = name;
}

void Player::increaseScore(int increase)
{
    score += increase;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
        playerCharacter->keyPressEvent(event);

    else if(event->key() == Qt::Key_Escape)
        emit escapeClicked();
}

