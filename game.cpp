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
        QGraphicsTextItem * infoText = makeDefaultText(fileText.readAll(), this->height() / 40, QColor(107, 142, 35));
        file.close();

        infoText->setPos(this->width()/2 - infoText->boundingRect().width()/2, this->height()/2.5 - infoText->boundingRect().height()/2);
        infoText->setZValue(1);
        scene->addItem(infoText);
    }
}

void Game::displayMainMenu()
{
    scene->clear();

    QGraphicsTextItem * title = makeDefaultText(QString("EndlesSnake"), this->width()/15, QColor(107, 142, 35));
    title->setPos(this->width()/2 - title->boundingRect().width()/2, this->height()/16);
    scene->addItem(title);

    int buttonWidth =  this->width() / 5;
    int buttonHeight = this->height() / 18;
    int buttonFontSize = this->width() / 50;
    int buttonX = this->width() / 2 - buttonWidth / 2;
    int buttonY = this->height() / 3;

    Button * playButton = makeDefaultButton(buttonX, buttonY, buttonWidth, buttonHeight, QString("Play"), buttonFontSize);
    connect(playButton, SIGNAL(clicked()), this, SLOT(displayUsernameGettingScreen()));

    Button * scoresButton = makeDefaultButton(buttonX, buttonY + this->height()/10, buttonWidth, buttonHeight, QString("Hall of fame"), buttonFontSize);
    connect(scoresButton, SIGNAL(clicked()), this, SLOT(displayHallOfFame()));

    Button * quitButton = makeDefaultButton(buttonX, buttonY + this->height()/10 * 2, buttonWidth, buttonHeight, QString("Quit Game"), buttonFontSize);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QGraphicsTextItem * author = makeDefaultText(QString("Author: Bartłomiej Wójtowicz"), this->height()/50, QColor(107, 142, 35));
    author->setPos(this->width() - author->boundingRect().width(), this->height() - author->boundingRect().height());
    scene->addItem(author);
}

void Game::displayHallOfFame()
{
    scene->clear();

    QGraphicsTextItem * title = makeDefaultText(QString("Hall of fame"), this->height()/15, QColor(107, 142, 35));
    title->setPos(this->width()/2 - title->boundingRect().width()/2, this->height()/20);
    scene->addItem(title);

    int textX = this->width()/6;
    int textY = this->height()/4;
    int textGap = this->height() / 20;
    int textSize = this->height() / 25;

    QList< QPair<QString, int> > bestScores = readBestScoresFromFile();
    for(int i=0; i<bestScores.size(); i++)
    {
        QGraphicsTextItem * placeAndName = makeDefaultText(QString::number(i+1) + QString(". ") + bestScores[i].first, textSize, QColor(107,142,35));
        placeAndName->setPos(textX, textY + textGap * i);
        scene->addItem(placeAndName);

        QGraphicsTextItem * score = makeDefaultText(QString::number(bestScores[i].second), textSize, QColor(107,142,35));
        score->setPos(this->width() - this->width()/5, textY + textGap * i);
        scene->addItem(score);
    }

    for(int i=bestScores.size(); i<10; i++)
    {
        QGraphicsTextItem * place = makeDefaultText(QString::number(i+1) + QString(". "), textSize,QColor(107,142,35));
        place->setPos(textX, textY + textGap * i);
        scene->addItem(place);
    }

    int buttonWidth = this->width() / 4;
    int buttonHeight = this->height() / 15;
    int buttonX = this->width()/2 - buttonWidth/2;
    int buttonY = this->height() - this->height()/10;
    int buttonTextSize = buttonHeight/2;

    Button * backButton = makeDefaultButton(buttonX, buttonY, buttonWidth, buttonHeight, QString("Back"), buttonTextSize);
    connect(backButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
}

void Game::displayUsernameGettingScreen()
{
    scene->clear();

    QGraphicsTextItem * typeInText = makeDefaultText(QString("Type in your nickname"), this->width()/30, QColor(107,142,35));
    typeInText->setPos(this->width()/2 - typeInText->boundingRect().width()/2, this->height()/2 - typeInText->boundingRect().height()/2 - this->height() / 5);
    scene->addItem(typeInText);

    QLineEdit * nicknameLine = new QLineEdit();
    int lineWidth = this->width() / 3;
    int lineHeight = this->height() / 15;
    nicknameLine->setGeometry(this->width()/2 - lineWidth/2, this->height()/2 - lineHeight/2, lineWidth, lineHeight);
    nicknameLine->setMaxLength(15);
    nicknameLine->setPlaceholderText(QString("Nickname"));

    QFont nicknameLineFont("times new roman", this->width()/50);
    nicknameLine->setFont(nicknameLineFont);
    scene->addWidget(nicknameLine);

    int buttonWidth = this->width() / 5;
    int buttonHeight = this->height() / 15;
    int buttonX = this->width()/2;
    int buttonY = this->height()/2 + this->height()/6;
    int buttonTextSize = buttonHeight/2;

    Button * backButton = makeDefaultButton(buttonX - buttonWidth -1, buttonY, buttonWidth, buttonHeight, QString("Back"), buttonTextSize);
    connect(backButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));

    Button * startButton = makeDefaultButton(buttonX+1, buttonY, buttonWidth, buttonHeight, QString("I'm ready!"), buttonTextSize);
    connect(startButton, &Button::clicked, this, [=]{startGame(nicknameLine->text()); } );
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

    QGraphicsTextItem * whatToDo = makeDefaultText(QString("What do you want to do?"), this->width()/40, QColor(107,142,35));
    whatToDo->setPos(this->width()/2 - whatToDo->boundingRect().width()/2, this->height()/2 - whatToDo->boundingRect().height()/2 - this->height() / 6);
    scene->addItem(whatToDo);

    int buttonWidth = this->width() / 5;
    int buttonHeight = this->height() / 15;
    int buttonX = this->width() / 2 - buttonWidth / 2;
    int buttonY = this->height() / 2 - buttonHeight / 2;
    int buttonTextSize = buttonHeight/2;

    Button * resumeButton = makeDefaultButton(buttonX, buttonY - this->height() / 15, buttonWidth, buttonHeight, QString("Resume"), buttonTextSize);
    connect(resumeButton, SIGNAL(clicked()), this, SLOT(clearAndResume()));

    Button * mainMenuButton = makeDefaultButton(buttonX, buttonY + this->height() / 30, buttonWidth, buttonHeight, QString("Main menu"), buttonTextSize);
    connect(mainMenuButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
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
    QGraphicsTextItem * scoreText = makeDefaultText(QString("Your score: ") + QString::number(player->getScore()), scoreTextFontSize, QColor(107,142,35) );
    int scoreTextX = windowX + windowWidth/2 - scoreText->boundingRect().width() / 2;
    scoreText->setPos(scoreTextX , windowY);
    scoreText->setZValue(1);
    scene->addItem(scoreText);

    int buttonWidth = windowWidth / 2;
    int buttonHeight = windowHeight / 8;
    int buttonMiddleX = this->width() / 2 - buttonWidth / 2;
    int buttonMiddleY = windowY + windowY / 1.5;
    int buttonTextSize = windowWidth / 30;

    Button * playAgainButton = makeDefaultButton(buttonMiddleX, buttonMiddleY, buttonWidth, buttonHeight, QString("Just one more time!"), buttonTextSize);
    connect(playAgainButton, &Button::clicked, this, [=]{startGame(player->getPlayerName()); } );

    Button * mainMenuButton = makeDefaultButton(buttonMiddleX, buttonMiddleY + windowHeight/5, buttonWidth, buttonHeight, QString("Back to main menu"), buttonTextSize);
    connect(mainMenuButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
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
                bestScores.removeLast();
                break;
            }
        }
    }

    selectionSortForListOfPairs(bestScores);
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

void Game::writeBestScoresToFile( QList<QPair<QString, int> > & list) const
{
    QFile inputFile("scrs/scores.dat");
    if(inputFile.open(QIODevice::WriteOnly))
    {
       QDataStream scores(&inputFile);

       for(int i=0; i<list.size(); i++)
           scores << list[i].first << list[i].second;

       inputFile.close();
    }
}

void Game::selectionSortForListOfPairs(QList<QPair<QString, int> > & list)
{
    for(int i=0; i<list.size(); i++)
    {
        int min = i;

        for(int j=i+1; j<list.size(); j++)
        {
            if(list[j].second < list[min].second)
                min = j;
        }
        QPair<QString, int> helpingVar = list[i];
        list[i] = list[min];
        list[min] = helpingVar;
    }
}

Button * Game::makeDefaultButton(int x, int y, int width, int height, QString text, int fontSize)
{
    Button * button = new Button(text, width, height, fontSize);
    button->setPos(x, y);
    button->setButtonColor(QColor(67, 139, 60));
    button->setHoverButtonColor(QColor(92, 165, 94));
    button->setFontColor(QColor(0, 50, 0));
    scene->addItem(button);
    return button;
}

QGraphicsTextItem * Game::makeDefaultText(QString text, int fontSize, QColor color)
{
    QGraphicsTextItem * defaultText = new QGraphicsTextItem(text);

    QFont defaultTextFont("times new roman", fontSize);
    defaultText->setFont(defaultTextFont);
    defaultText->setDefaultTextColor(color);

    return defaultText;
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
