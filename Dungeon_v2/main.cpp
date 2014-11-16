#include "mainwindow.h"
#include "titlescreen.h"
#include "help.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // This is just to make the wireframe work, and will be redesigned in the next version to work properly in an OOP manner.
    TitleScreen *titleScreen = new TitleScreen;
    int result = titleScreen->exec();
    qDebug("%d", result);

    if (result == 1) { // Open gameboard
        MainWindow *w = new MainWindow;
        w->show();
    } else if (result == 2) { // Quit application
        qDebug("Quitting!");
        QCoreApplication::quit();
    } else if (result == 3) { // Open help screen
        Help *h = new Help;
        h->show();
    }
    return a.exec();
}
