#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <QGraphicsRectItem>
#include <wall.h>
#include <QPen>
#include <QBrush>

class PlayingField : public QGraphicsRectItem
{
private:
    Wall * leftWall;
    QGraphicsRectItem * mainField;
    Wall * rightWall;

    void setMainField(int width, int height, QColor color);
    void setWalls(int width, int height, QColor wallColor);

public:
    PlayingField(int screenWidth, int screenHeight, QGraphicsItem * parent = nullptr);
    ~PlayingField() {}
};

#endif // PLAYINGFIELD_H
