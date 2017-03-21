#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointer>
#include <QGraphicsRectItem>
#include <button.h>
#include <QScrollBar>
#include <playingfield.h>
#include <player.h>
#include <snake.h>
#include <QTime>

class Game : public QGraphicsView
{
    Q_OBJECT

private:
    int screenWidth;
    int screenHeight;

    QGraphicsScene * scene;
    PlayingField * playingField;
    Player * player;

    bool gamePaused;
    bool changingPauseStatusAllowed;

    void initScene(int x, int y, int width, int height);
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity = 1.0);
    void setPlayer();

    void pauseGame();
    void resumeGame();

    void makeSceneRectSmallerToPreventScrollingEffect();
    void restoreAppropriateSceneRectSize();

public:
    Game(int width = 1024, int height = 768, QWidget * /*parent*/ = nullptr);
    ~Game() {}

private slots:
    void startGame();
    void pauseOrResumeGame();
    void displayGameOverWindow();

public slots:
    void displayMainMenu();

};
#endif // GAME_H
