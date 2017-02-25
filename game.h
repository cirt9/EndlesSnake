#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointer>
#include <QGraphicsRectItem>
#include <button.h>

class Game : public QGraphicsView
{
    Q_OBJECT

private:
    QGraphicsScene * scene;

    void initScene(int x, int y, int width, int height);
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity = 1.0);

public:
    Game(int width = 1024, int height = 768, QWidget * /*parent*/ = nullptr);
    ~Game() {}

public slots:
    void displayMainMenu();

};
#endif // GAME_H
