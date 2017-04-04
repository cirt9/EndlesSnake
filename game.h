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
#include <QTextStream>
#include <QLineEdit>
#include <QPair>
#include <QDir>
#include <QList>


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
    void setPlayer(QString playerName);

    void pauseGame();
    void resumeGame();
    void getRidOfButtonsAndText();

    void makeSceneRectSmallerToPreventScrollingEffect();
    void restoreAppropriateSceneRectSize();

    void updateBestScores();
    QList< QPair<QString, int> > readBestScoresFromFile() const;
    void writeBestScoresToFile(QList< QPair<QString, int> > & list) const;
    void selectionSortForListOfPairs(QList< QPair<QString, int> > & list);

    Button * makeDefaultButton(int x, int y, int width, int height, QString text, int fontSize);
    QGraphicsTextItem * makeDefaultText(QString text, int fontSize, QColor color);

public:
    Game(int width = 1024, int height = 768, QWidget * /*parent*/ = nullptr);
    ~Game() {}

private slots:
    void displayMainMenu();
    void displayUsernameGettingScreen();
    void startGame(QString playerName = QString("\0") );
    void pauseOrResumeGame();
    void displayEscapeWindow();
    void displayGameOverWindow();
    void clearAndResume();
    void displayHallOfFame();

public slots:
    void displayInformationWindow();

};
#endif // GAME_H
