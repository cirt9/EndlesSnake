#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <snake.h>
#include <QPen>

class Player :  public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    QString playerName;
    Snake * playerCharacter;
    int score;

    void keyPressEvent(QKeyEvent * event = nullptr);

public:
    Player(int screenWidth, int screenHeight, QGraphicsItem * parent = nullptr);
    ~Player() {}

    void setPlayerCharacter(int movementSpeed, int characterSize, int x, int y,  QColor characterColor);
    void setPlayerName(QString name);

    Snake * getPlayerCharacter() const;
    int getScore() const;

public slots:
    void increaseScore(int increase);

signals:
    void escapeClicked();
};

#endif // PLAYER_H
