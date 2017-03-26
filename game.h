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
#include <QPen>
#include <QFile>
#include <QTextStream>
#include <QUrl>

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
    void getRidOfButtonsAndText();

    void makeSceneRectSmallerToPreventScrollingEffect();
    void restoreAppropriateSceneRectSize();

public:
    Game(int width = 1024, int height = 768, QWidget * /*parent*/ = nullptr);
    ~Game() {}

private slots:
    void displayMainMenu();
    void startGame();
    void pauseOrResumeGame();
    void displayEscapeWindow();
    void displayGameOverWindow();
    void clearAndResume();

public slots:
    void displayInformationWindow();

};
#endif // GAME_H
