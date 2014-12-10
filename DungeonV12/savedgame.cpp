#include "savedgame.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QStringList>

SavedGame::SavedGame()
{
}

bool SavedGame::Load(QString const& configPath, QString const& configFileName)
{
    QDir qDir;
    IsLoaded = false;

    configFile = new QFile(configPath + configFileName);
    if (!configFile->exists()) {
        QDir qDir;
        if (!qDir.exists(configPath))
            qDir.mkpath(configPath);

        if (!configFile->open(QIODevice::ReadWrite)) {
            qDebug() << "Cannot open file: " << qPrintable(configFile->errorString()) << endl;
        } else {
            IsLoaded = true;
            configFile->close();
        }

    } else {
        if (!configFile->open(QIODevice::ReadOnly)) {
            qDebug() << "Cannot open file: " << qPrintable(configFile->errorString()) << endl;
        } else {
            QTextStream in(configFile);
        while (!in.atEnd()) {
            QString inLine = in.readLine();
            this->savedGames.append(inLine.trimmed());
        }
        configFile->close();
        qDebug() << this->savedGames.count();
        IsLoaded = true;
        }
    }
}

QStringList SavedGame::GetSavedGameList() {
    return this->savedGames;
}

QString SavedGame::GetSavedGame(int gameNumber) {
    return this->savedGames.at(gameNumber);
}

int SavedGame::GetSavedGameCount() {
    return this->savedGames.count();
}

bool SavedGame::GetIsLoaded()
{
    return this->IsLoaded;
}

void SavedGame::AddGame(int x, int y, int experience) {
    QString savedGameString("%1:%2:%3");
    savedGameString = savedGameString.arg(x).arg(y).arg(experience);
    this->savedGames.append(savedGameString.trimmed());
    this->SaveGamesToFile();
}

bool SavedGame::SaveGamesToFile() {

    qDebug() << "Entering SaveGamesToFile()";
    //QDir qDir;

    //if (!qDir.exists(this->configFile->configPath))
    //    qDir.mkpath(configPath);
    if (!configFile->open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file: " << qPrintable(configFile->errorString()) << endl;
        return false;
    }
    QTextStream out(this->configFile);
    for (int i = 0; i < this->savedGames.count(); i++) {
        out << this->savedGames.at(i) << "\r\n";
    }
    out.flush();
    configFile->close();
    qDebug() << this->savedGames.count();
    return true;
}
