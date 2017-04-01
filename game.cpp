#include "game.h"
#include <QDebug>

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

    QDir dir(QDir::currentPath() + "/scrs");
    if(!dir.exists())
        dir.mkpath(".");
}

void Game::initScene(int x, int y, int width, int height)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(x,y,width,height);
    QBrush backgroundColor(QColor(174, 204, 118));
    scene->setBackgroundBrush(backgroundColor);
    setScene(scene);
}

void Game::displayInformationWindow()
{
    makeSceneRectSmallerToPreventScrollingEffect();

    Button * goToMenuButton = new Button(QString(""), this->width(), this->height(), 0);
    goToMenuButton->setButtonColor(QColor(174, 204, 118));
    goToMenuButton->setHoverButtonColor(QColor(174, 204, 118));
    goToMenuButton->setPen(Qt::NoPen);
    connect(goToMenuButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(goToMenuButton);

    QFile file(":/info/initial_info.txt");

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream fileText(&file);
        QGraphicsTextItem * infoText = new QGraphicsTextItem(fileText.readAll());
        file.close();

        QFont infoFont("times new roman", this->height() / 40);
        infoText->setFont(infoFont);
        infoText->setDefaultTextColor(QColor(107, 142, 35));
        infoText->setPos(this->width()/2 - infoText->boundingRect().width()/2, this->height()/2.5 - infoText->boundingRect().height()/2);
        infoText->setZValue(1);
        scene->addItem(infoText);
    }
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
    connect(playButton, SIGNAL(clicked()), this, SLOT(displayUsernameGettingScreen()));
    scene->addItem(playButton);

    Button * scoresButton = new Button(QString("Scores"), this->width()/5, this->height()/18, this->width()/50);
    scoresButton->setPos(this->width() / 2 - scoresButton->boundingRect().width()/2 , this->height()/3 + this->height()/10);
    scoresButton->setButtonColor(QColor(67, 139, 60));
    scoresButton->setHoverButtonColor(QColor(92, 165, 94));
    scoresButton->setFontColor(QColor(0, 50, 0));
    connect(scoresButton, SIGNAL(clicked()), this, SLOT(displayHallOfFame()));
    scene->addItem(scoresButton);

    Button * quitButton = new Button(QString("Quit Game"), this->width()/5, this->height()/18, this->width()/50);
    quitButton->setPos(this->width() / 2 - quitButton->boundingRect().width()/2 , this->height()/3 + this->height()/10 * 2);
    quitButton->setButtonColor(QColor(67, 139, 60));
    quitButton->setHoverButtonColor(QColor(92, 165, 94));
    quitButton->setFontColor(QColor(0, 50, 0));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

    QGraphicsTextItem * author = new QGraphicsTextItem(QString("Author: Bartłomiej Wójtowicz"));
    QFont authorFont("calibri", this->height() / 50);
    author->setFont(authorFont);
    author->setDefaultTextColor(QColor(107,142,35));
    author->setPos(this->width() - author->boundingRect().width(), this->height() - author->boundingRect().height());
    scene->addItem(author);
}

void Game::displayHallOfFame()
{
    scene->clear();

    QGraphicsTextItem * title = new QGraphicsTextItem(QString("Hall of fame"));
    QFont titleFont("times new roman", this->height() / 15);
    title->setFont(titleFont);
    title->setDefaultTextColor(QColor(107,142,35));
    title->setPos(this->width()/2 - title->boundingRect().width()/2, this->height()/20);
    scene->addItem(title);

    int textX = this->width()/3;
    int textY = this->height()/4;
    int textGap = this->height() / 20;
    int textSize = this->height() / 25;

    QList< QPair<QString, int> > bestScores = readBestScoresFromFile();
    for(int i=0; i<bestScores.size(); i++)
    {
        QGraphicsTextItem * score = new QGraphicsTextItem(QString::number(i+1) + QString(". ") + bestScores[i].first + QString(" ") + QString::number(bestScores[i].second));
        QFont scoreFont("times new roman", textSize);
        score->setFont(scoreFont);
        score->setDefaultTextColor(QColor(107,142,35));
        score->setPos(textX, textY + textGap * i);
        scene->addItem(score);
    }

    int buttonWidth = this->width() / 4;
    int buttonHeight = this->height() / 15;

    Button * backButton = new Button(QString("Back"), buttonWidth, buttonHeight, buttonHeight/2);
    backButton->setPos(this->width()/2 - buttonWidth/2 , this->height() - this->height()/10);
    backButton->setButtonColor(QColor(67, 139, 60));
    backButton->setHoverButtonColor(QColor(92, 165, 94));
    backButton->setFontColor(QColor(0, 50, 0));
    connect(backButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(backButton);
}

void Game::displayUsernameGettingScreen()
{
    scene->clear();

    QGraphicsTextItem * typeInText = new QGraphicsTextItem(QString("Type in your nickname"));
    QFont typeInTextFont("times new roman", this->width()/30);
    typeInText->setFont(typeInTextFont);
    typeInText->setDefaultTextColor(QColor(0, 50, 0));
    typeInText->setPos(this->width()/2 - typeInText->boundingRect().width()/2, this->height()/2 - typeInText->boundingRect().height()/2 - this->height() / 5);
    scene->addItem(typeInText);

    QLineEdit * nicknameLine = new QLineEdit();
    int lineWidth = this->width() / 3;
    int lineHeight = this->height() / 15;
    nicknameLine->setGeometry(this->width()/2 - lineWidth/2, this->height()/2 - lineHeight/2, lineWidth, lineHeight);
    nicknameLine->setMaxLength(20);
    nicknameLine->setPlaceholderText(QString("Your Nickname"));

    QFont nicknameLineFont("times new roman", this->width()/50);
    nicknameLine->setFont(nicknameLineFont);
    scene->addWidget(nicknameLine);

    int buttonWidth = this->width() / 5;
    int buttonHeight = this->height() / 15;

    Button * backButton = new Button(QString("Back"), buttonWidth, buttonHeight, buttonHeight/2);
    backButton->setPos(this->width()/2 - buttonWidth-1, this->height()/2 + this->height()/6);
    backButton->setButtonColor(QColor(67, 139, 60));
    backButton->setHoverButtonColor(QColor(92, 165, 94));
    backButton->setFontColor(QColor(0, 50, 0));
    connect(backButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(backButton);

    Button * startButton = new Button(QString("I'm ready!"), buttonWidth, buttonHeight, buttonHeight/2);
    startButton->setPos(this->width()/2+1, this->height()/2 + this->height()/6);
    startButton->setButtonColor(QColor(67, 139, 60));
    startButton->setHoverButtonColor(QColor(92, 165, 94));
    startButton->setFontColor(QColor(0, 50, 0));
    connect(startButton, &Button::clicked, this, [=]{startGame(nicknameLine->text()); } );
    scene->addItem(startButton);
}

void Game::startGame(QString playerName)
{
    scene->clear();
    restoreAppropriateSceneRectSize();
    changingPauseStatusAllowed = true;

    setPlayer(playerName);
    connect(player, SIGNAL(escapeClicked()), this, SLOT(displayEscapeWindow()));
    connect(player, SIGNAL(pauseClicked()), this, SLOT(pauseOrResumeGame()));
    connect(player->getPlayerCharacter(), SIGNAL(defeated()), this, SLOT(displayGameOverWindow()));

    playingField = new PlayingField(this->width(), this->height(), player);
    scene->addItem(playingField);
    playingField->startMovingAndSpawningObjects();
}

void Game::setPlayer(QString playerName)
{
    player = new Player(this->width(), this->height());

    int speed = 25;
    int size = this->height() / 15;
    int x = this->width() / 2 - size / 2;
    int y = this->height()- size - 10;
    QColor color(0, 30, 100);

    player->setPlayerCharacter(speed, size, x, y, color);
    player->setPlayerName(playerName);
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

void Game::displayEscapeWindow()
{
    pauseGame();
    changingPauseStatusAllowed = false;

    QGraphicsTextItem * whatToDo = new QGraphicsTextItem(QString("What do you want to do?"));
    QFont whatToDoFont("times new roman", this->width()/40);
    whatToDo->setFont(whatToDoFont);
    whatToDo->setDefaultTextColor(QColor(0, 50, 0));
    whatToDo->setPos(this->width()/2 - whatToDo->boundingRect().width()/2, this->height()/2 - whatToDo->boundingRect().height()/2 - this->height() / 6);
    scene->addItem(whatToDo);

    int buttonWidth = this->width() / 5;
    int buttonHeight = this->height() / 15;
    int buttonX = this->width() / 2 - buttonWidth / 2;
    int buttonY = this->height() / 2 - buttonHeight / 2;

    Button * resumeButton = new Button(QString("Resume"), buttonWidth, buttonHeight, buttonHeight/2);
    resumeButton->setPos(buttonX , buttonY - this->height() / 15);
    resumeButton->setButtonColor(QColor(67, 139, 60));
    resumeButton->setHoverButtonColor(QColor(92, 165, 94));
    resumeButton->setFontColor(QColor(0, 50, 0));
    connect(resumeButton, SIGNAL(clicked()), this, SLOT(clearAndResume()));
    scene->addItem(resumeButton);

    Button * mainMenuButton = new Button(QString("Main menu"), buttonWidth, buttonHeight, buttonHeight/2);
    mainMenuButton->setPos(buttonX , buttonY + this->height() / 30);
    mainMenuButton->setButtonColor(QColor(67, 139, 60));
    mainMenuButton->setHoverButtonColor(QColor(92, 165, 94));
    mainMenuButton->setFontColor(QColor(0, 50, 0));
    connect(mainMenuButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(mainMenuButton);
}

void Game::displayGameOverWindow()
{
    updateBestScores();
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
    connect(playAgainButton, &Button::clicked, this, [=]{startGame(player->getPlayerName()); } );
    //connect(playAgainButton, SIGNAL(clicked()), this, SLOT(startGame()));
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

void Game::clearAndResume()
{
    changingPauseStatusAllowed = true;
    getRidOfButtonsAndText();
    resumeGame();
}

void Game::getRidOfButtonsAndText()
{
    QList<QGraphicsItem *> sceneItems = scene->items();

    for(auto item : sceneItems)
    {
        if(typeid(*item) == typeid(Button) || typeid(*item) == typeid(QGraphicsTextItem))
            delete item;
    }
}

void Game::makeSceneRectSmallerToPreventScrollingEffect()
{
    setSceneRect(0, 0, screenWidth - 5, screenHeight - 5);
}

void Game::restoreAppropriateSceneRectSize()
{
    setSceneRect(0, 0, screenWidth + 5, screenHeight + 5);
}

void Game::updateBestScores()
{
    QList< QPair<QString, int> > bestScores = readBestScoresFromFile();

    if(bestScores.size() < 10)
        bestScores.push_back(QPair<QString, int>(player->getPlayerName(), player->getScore()) );
    else
    {
        for(int i=0; i<bestScores.size(); i++)
        {
            if(player->getScore() > bestScores[i].second)
            {
                bestScores.insert(i, QPair<QString, int>(player->getPlayerName(), player->getScore()) );
                break;
            }
        }
        bestScores.removeLast();
    }

    selectionSortForVectorOfPairs(bestScores);
    writeBestScoresToFile(bestScores);
}

QList<QPair<QString, int> > Game::readBestScoresFromFile() const
{
    QFile inputFile("scrs/scores.dat");
    QList< QPair<QString, int> > bestScores;

    if(inputFile.open(QIODevice::ReadOnly))
    {
       QDataStream scores(&inputFile);

       while(!scores.atEnd())
       {
          QString name;
          int score;
          scores >> name >> score;
          bestScores.push_front( QPair<QString, int>(name, score) );
       }
       inputFile.close();
    }
    return bestScores;
}

void Game::writeBestScoresToFile( QList<QPair<QString, int> > & vector) const
{
    QFile inputFile("scrs/scores.dat");
    if(inputFile.open(QIODevice::WriteOnly))
    {
       QDataStream scores(&inputFile);
       QPair<QString, int> score;

       foreach(score, vector)
           scores << score.first << score.second;

       inputFile.close();
    }
}

void Game::selectionSortForVectorOfPairs(QList<QPair<QString, int> > & vector)
{
    for(int i=0; i<vector.length(); i++)
        qDebug() << vector[i].first << " " << vector[i].second;
    qDebug() << endl;

    for(int i=0; i<vector.size(); i++)
    {
        int min = i;

        for(int j=i+1; j<vector.size(); j++)
        {
            if(vector[j].second < vector[min].second)
                min = j;
        }
        QPair<QString, int> helpingVar = vector[i];
        vector[i] = vector[min];
        vector[min] = helpingVar;
    }

    for(int i=0; i<vector.length(); i++)
        qDebug() << vector[i].first << " " << vector[i].second;
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
