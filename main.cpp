#include <QApplication>
#include <QScreen>
#include <game.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QScopedPointer<QScreen> screen(QGuiApplication::primaryScreen());
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    if(screenWidth < 800 || screenHeight < 600)
    {
        screenWidth = 800;
        screenHeight = 600;
    }

    QPointer<Game> game(new Game(screenWidth, screenHeight));
    game->show();
    game->displayMainMenu();

    return a.exec();
}
