#include "game.h"

Game::Game(int width, int height, QWidget * /*parent*/)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(width,height);

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
    QFont titleFont("times new roman", 80);
    title->setFont(titleFont);
    title->setDefaultTextColor(QColor(107, 142, 35));
    title->setPos(this->width()/2 - title->boundingRect().width()/2, this->height()/16);
    scene->addItem(title);

    Button * playButton = new Button(QString("Play"), 350, 50, 30);
    playButton->setPos(this->width() / 2 - playButton->boundingRect().width()/2 , this->height()/3);
    playButton->setButtonColor(QColor(67, 139, 60));
    playButton->setHoverButtonColor(QColor(92, 165, 94));
    playButton->setFontColor(QColor(0, 50, 0));
    //connect(playButton, SIGNAL(clicked()), this, SLOT(turnOffCPUAndStart()));
    scene->addItem(playButton);

    Button * scoresButton = new Button(QString("Scores"), 350, 50, 30);
    scoresButton->setPos(this->width() / 2 - scoresButton->boundingRect().width()/2 , this->height()/3 + 100);
    scoresButton->setButtonColor(QColor(67, 139, 60));
    scoresButton->setHoverButtonColor(QColor(92, 165, 94));
    scoresButton->setFontColor(QColor(0, 50, 0));
    //connect(vsCPUButton, SIGNAL(clicked()), this, SLOT(turnOnCPUAndStart()));
    scene->addItem(scoresButton);

    Button * quitButton = new Button(QString("Quit Game"), 350, 50, 30);
    quitButton->setPos(this->width() / 2 - quitButton->boundingRect().width()/2 , this->height()/3 + 200);
    quitButton->setButtonColor(QColor(67, 139, 60));
    quitButton->setHoverButtonColor(QColor(92, 165, 94));
    quitButton->setFontColor(QColor(0, 50, 0));
    //connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

    QGraphicsTextItem * author = new QGraphicsTextItem(QString("Author: Bartłomiej Wójtowicz"));
    QFont authorFont("calibri", 15);
    author->setFont(authorFont);
    author->setDefaultTextColor(QColor(107,142,35));
    author->setPos(this->width() - author->boundingRect().width(), this->height() - author->boundingRect().height());
    scene->addItem(author);
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    QGraphicsRectItem * panel = new QGraphicsRectItem(x, y, width, height);
    QBrush panelColor(color, Qt::SolidPattern);
    panel->setBrush(panelColor);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}
