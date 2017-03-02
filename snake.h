#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QKeyEvent>

class Snake : public QGraphicsRectItem
{
private:
    void keyPressEvent(QKeyEvent * event = nullptr);

public:
    Snake(QGraphicsItem * parent = nullptr);

};

#endif // SNAKE_H
