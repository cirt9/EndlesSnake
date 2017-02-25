#include <QApplication>
#include <game.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QPointer<Game> game(new Game(1024,768));
    //game->show();
    //game->displayMainMenu();

    return a.exec();
}
