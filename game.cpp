#include "game.h"

Game::Game(int width, int height, QWidget * /*parent*/)
{
    horizontalScrollBar()->setEnabled(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalScrollBar()->setEnabled(false);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedSize(width,height);
    setSceneRect(0, 0, width, height);
    showFullScreen();

    qsrand(QTime::currentTime().msec());

    initScene(0, 0, width, height);

    screenWidth = width;
    screenHeight = height;
    gamePaused = false;
    changingPauseStatusAllowed = true;
}

void Game::initScene(int x, int y, int width, int height)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(x,y,width,height);
    QBrush backgroundColor(QColor(174, 204, 118));
    scene->setBackgroundBrush(backgroundColor);
    setScene(scene);
}

void Game::displayMainMenu()
{
    scene->clear();
    makeSceneRectSmallerToPreventScrollingEffect();

    QGraphicsTextItem * title = new QGraphicsTextItem(QString("EndlesSnake"));
    QFont titleFont("times new roman", this->width()/15);
    title->setFont(titleFont);
    title->setDefaultTextColor(QColor(107, 142, 35));
    title->setPos(this->width()/2 - title->boundingRect().width()/2, this->height()/16);
    scene->addItem(title);

    Button * playButton = new Button(QString("Play"), this->width()/5, this->height()/18, this->width()/50);
    playButton->setPos(this->width() / 2 - playButton->boundingRect().width()/2 , this->height()/3);
    playButton->setButtonColor(QColor(67, 139, 60));
    playButton->setHoverButtonColor(QColor(92, 165, 94));
    playButton->setFontColor(QColor(0, 50, 0));
    connect(playButton, SIGNAL(clicked()), this, SLOT(startGame()));
    scene->addItem(playButton);

    Button * scoresButton = new Button(QString("Scores"), this->width()/5, this->height()/18, this->width()/50);
    scoresButton->setPos(this->width() / 2 - scoresButton->boundingRect().width()/2 , this->height()/3 + this->height()/10);
    scoresButton->setButtonColor(QColor(67, 139, 60));
    scoresButton->setHoverButtonColor(QColor(92, 165, 94));
    scoresButton->setFontColor(QColor(0, 50, 0));
    //connect(scoresButton, SIGNAL(), this, SLOT());
    scene->addItem(scoresButton);

    Button * quitButton = new Button(QString("Quit Game"), this->width()/5, this->height()/18, this->width()/50);
    quitButton->setPos(this->width() / 2 - quitButton->boundingRect().width()/2 , this->height()/3 + this->height()/10 * 2);
    quitButton->setButtonColor(QColor(67, 139, 60));
    quitButton->setHoverButtonColor(QColor(92, 165, 94));
    quitButton->setFontColor(QColor(0, 50, 0));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

    QGraphicsTextItem * author = new QGraphicsTextItem(QString("Author: Bartłomiej Wójtowicz"));
    QFont authorFont("calibri", 15);
    author->setFont(authorFont);
    author->setDefaultTextColor(QColor(107,142,35));
    author->setPos(this->width() - author->boundingRect().width(), this->height() - author->boundingRect().height());
    scene->addItem(author);
}

void Game::startGame()
{
    scene->clear();
    restoreAppropriateSceneRectSize();
    changingPauseStatusAllowed = true;

    setPlayer();
    connect(player, SIGNAL(escapeClicked()), this, SLOT(close())); //temporary
    connect(player, SIGNAL(pauseClicked()), this, SLOT(pauseOrResumeGame()));
    connect(player->getPlayerCharacter(), SIGNAL(defeated()), this, SLOT(displayGameOverWindow()));

    playingField = new PlayingField(this->width(), this->height(), player);
    scene->addItem(playingField);
    playingField->startMovingAndSpawningObjects();
}

void Game::setPlayer()
{
    player = new Player(this->width(), this->height());

    int speed = 25;
    int size = this->height() / 15;
    int x = this->width() / 2 - size / 2;
    int y = this->height()- size - 10;
    QColor color(0, 30, 100);

    player->setPlayerCharacter(speed, size, x, y, color);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setZValue(1);
    scene->addItem(player);
}

void Game::pauseOrResumeGame()
{
    if(changingPauseStatusAllowed)
    {
        if(gamePaused)
            resumeGame();
        else
            pauseGame();
    }
}

void Game::displayGameOverWindow()
{
    pauseGame();
    changingPauseStatusAllowed = false;
    drawPanel(0, 0, this->width(), this->height(), QColor("black"), 0.9);

    int windowWidth = this->width() / 2;
    int windowHeight = this->height() / 2;
    int windowX = this->width()/2 - windowWidth/2;
    int windowY = this->height()/2 - windowHeight/2;
    drawPanel(windowX, windowY, windowWidth, windowHeight, QColor("green"), 0.7);

    int scoreTextFontSize = windowWidth / 20;
    QGraphicsTextItem * scoreText = new QGraphicsTextItem(QString("Your score: ") + QString::number(player->getScore() ) );
    int scoreTextX = (windowWidth + windowX) / 2 + scoreText->boundingRect().width() / 2;
    QFont scoreFont("times new roman", scoreTextFontSize);
    scoreText->setFont(scoreFont);
    scoreText->setDefaultTextColor(QColor("black"));
    scoreText->setPos(scoreTextX , windowY);
    scoreText->setZValue(1);
    scene->addItem(scoreText);

    int buttonWidth = windowWidth / 2;
    int buttonHeight = windowHeight / 8;
    int buttonMiddleX = this->width() / 2 - buttonWidth / 2;
    int buttonMiddleY = windowY + windowY / 1.5;

    Button * playAgainButton = new Button(QString("Just one more time!"), buttonWidth, buttonHeight, windowWidth / 30);
    playAgainButton->setPos(buttonMiddleX , buttonMiddleY);
    playAgainButton->setButtonColor(QColor(67, 139, 60));
    playAgainButton->setHoverButtonColor(QColor(92, 165, 94));
    playAgainButton->setFontColor(QColor(0, 50, 0));
    connect(playAgainButton, SIGNAL(clicked()), this, SLOT(startGame()));
    scene->addItem(playAgainButton);

    Button * mainMenuButton = new Button(QString("Back to main menu"), buttonWidth, buttonHeight, windowWidth / 30);
    mainMenuButton->setPos(buttonMiddleX , buttonMiddleY + windowHeight / 5);
    mainMenuButton->setButtonColor(QColor(67, 139, 60));
    mainMenuButton->setHoverButtonColor(QColor(92, 165, 94));
    mainMenuButton->setFontColor(QColor(0, 50, 0));
    connect(mainMenuButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(mainMenuButton);
}

void Game::pauseGame()
{
    playingField->pause();
    player->getPlayerCharacter()->changeMovingAllowed();
    gamePaused = true;
}

void Game::resumeGame()
{
    playingField->resume();
    player->getPlayerCharacter()->changeMovingAllowed();
    gamePaused = false;
}

void Game::makeSceneRectSmallerToPreventScrollingEffect()
{
    setSceneRect(0, 0, screenWidth - 5, screenHeight - 5);
}

void Game::restoreAppropriateSceneRectSize()
{
    setSceneRect(0, 0, screenWidth + 5, screenHeight + 5);
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    QGraphicsRectItem * panel = new QGraphicsRectItem(x, y, width, height);
    QBrush panelColor(color, Qt::SolidPattern);
    panel->setBrush(panelColor);
    panel->setOpacity(opacity);
    panel->setZValue(1);
    scene->addItem(panel);
}
