#include "mainwindow.h"
#include <QApplication>
#include <QRect>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-w.width()) / 2;
    int y = (screenGeometry.height()-w.height()) / 2;
    qDebug() << x << ":" << y;
    w.move(x, y);
    w.show();
    return a.exec();
}
