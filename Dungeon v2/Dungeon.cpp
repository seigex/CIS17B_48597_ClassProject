//RPG DUNGEON HELP PAGE
//=======================================================================================//
// design considerations, notes, etc
//=======================================================================================//
//
//List of page elements
  /*
  control list with pictures of keys
  unordered list of stats and their meaning
  objective
  good luck
  back button
  */
//
//
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv); //begin application window

//=======================================================================================//
// Base Creation
//=======================================================================================//

   //creation of base page
   QWidget *helpWindow = new QWidget;
   helpWindow->setWindowTitle("Help");

   //creation of labels
   QLabel *controls  = newQlabel("Use WASD or Arrow Keys to move. Use -undetermined- to attack. Access items with -undetermined-"); //add key pictures later
   QLabel *stats     = newQlabel("<p>Player Stats:"
                                 "<ul>"
                                 "<li><h3><font color = red  >hp </font></h3>: &nbsp &nbsp Health      : &nbsp Point value determining how much damage you are able to withstand before dying.</li>"
                                 "<li><h3><font color = blue >mp </font></h3>: &nbsp &nbsp Mana        : &nbsp Point value determining your reserve power for special abilities and magic.</li>"
                                 "<li><h3><font color = Green>lck</font></h3>: &nbsp &nbsp Luck        : &nbsp With higher luck, you score critical hits more often and take critical damage less often.</li>"
                                 "<li><h3><font color = red  >str</font></h3>: &nbsp &nbsp Strength    : &nbsp Strength determines your ability to deal raw base damage and to wield heavy equipment.</li>"
                                 "<li><h3><font color = Green>spd</font></h3>: &nbsp &nbsp Speed       : &nbsp Determines your speed relative to an enemy, affecting the timing of your attacks as well as how easily you can evade enemy attacks.</li>"
                                 "<li><h3><font color = red  >def</font></h3>: &nbsp &nbsp Defence     : &nbsp Higher defence allows you to withstand stronger attacks while taking less core damage.</li>"
                                 "<li><h3><font color = blue >itl</font></h3>: &nbsp &nbsp Intelligence: &nbsp Intelligence allows you to utilize your magics effectively, increasing their effectiveness.</li>"
                                 "<li><h3><font color = Green>dex</font></h3>: &nbsp &nbsp Dexterity   : &nbsp Relates to nimble and agile movements of the body, allowing you to wield complex weapons more effectively, and to dodge simple enemy attacks.</li>"
                                 "<li><h3><font color = gold >exp</font></h3>: &nbsp &nbsp Experience  : &nbsp Represents your combat history. With each fight you gain more experience, and with more experience you grow a stronger and more learned opponent.</li>"
                                 "</ul></p>");

   QLabel *objective = newQlabel("Your objective is to safely navigate the level and to escape with your life...and as much loot as you care to swipe!");
   QLabel *closing   = newQlabel("<i>good luck!</i>");

   //creation of back button
   QPushButton *back = new QPushButton("Back");

   //creation of layout handler
   QVBoxLayout *layout = new QVBoxLayout;

//=======================================================================================//
// Processing/Function
//=======================================================================================//

   //adding functionality
   QObject::connect(back, SIGNAL(clicked()), &app, SLOT(quit())); //(calling object,causal event,affected object,effect delivered). currently this is ("button","when clicked","application overall","quit") should be ("button,"when clicked","this window","close") or (...,...,"application","back to playthrough window")

   //setting page layout
   layout->addWidget(controls);
   layout->addWidget(stats);
   layout->addWidget(objective);
   layout->addWidget(closing);
   layout->addWidget(back);
   window->setLayout(layout);

   helpWindow->show(); //make window visible
   return app.exec(); //return from application
}
