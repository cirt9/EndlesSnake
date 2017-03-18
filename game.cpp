#include "game.h"

Game::Game(int width, int height, QWidget * /*parent*/)
{
    horizontalScrollBar()->setEnabled(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalScrollBar()->setEnabled(false);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedSize(width,height);
    setSceneRect(0, 0, width-5, height-5);
    showFullScreen();

    qsrand(QTime::currentTime().msec());

    initScene(0, 0, width, height);
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

    setPlayer();
    connect(player, SIGNAL(escapeClicked()), this, SLOT(close())); //temporary

    playingField = new PlayingField(this->width(), this->height(), player);
    scene->addItem(playingField);
    playingField->startMovingAndSpawningObjects();
}

void Game::setPlayer()
{
    player = new Player(this->width(), this->height());

    int speed = this->width() / 80;
    int size = this->width() / 27;
    int x = this->width() / 2 - size / 2;
    int y = this->height()- size - 10;
    QColor color(0, 30, 100);

    player->setPlayerCharacter(speed, size, x, y, color);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setZValue(1);
    scene->addItem(player);
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    QGraphicsRectItem * panel = new QGraphicsRectItem(x, y, width, height);
    QBrush panelColor(color, Qt::SolidPattern);
    panel->setBrush(panelColor);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}
