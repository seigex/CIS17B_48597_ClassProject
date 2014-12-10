#ifndef SAVEDGAME_H
#define SAVEDGAME_H

#include <QString>
#include <QFile>
#include <QStringList>

class SavedGame
{
private:
    QFile *configFile;
    QStringList savedGames;
    bool SaveGamesToFile();
    bool IsLoaded;

public:
    SavedGame();
    bool Load(QString const& configPath, QString const& configFileName);
    QStringList GetSavedGameList();
    int GetSavedGameCount();
    QString GetSavedGame(int gameNumber);
    bool GetIsLoaded();

    void AddGame(int x, int y, int experience);

    bool SaveGame();
    bool DeleteGame();
    int* getGame(int gameNumber);

};

#endif // SAVEDGAME_H
