#include <QApplication>
#include <iostream>
#include "combat_screen.h"
#include "win_screen.h"
using namespace std;

int main(int argc, char *argv[]){
    QApplication app(argc,argv);
    Combat_Screen *dialog = new Combat_Screen;
    std::cout<<dialog->get_enemy_health()<<std::endl;
    dialog->show();
    return app.exec();
}
