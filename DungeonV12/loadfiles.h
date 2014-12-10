#ifndef LOADFILES_H
#define LOADFILES_H

#include <QDialog>
#include <QStringList>
#include <QListWidgetItem>

namespace Ui {
class LoadFiles;
}

class LoadFiles : public QDialog
{
    Q_OBJECT

public:
    explicit LoadFiles(int savedGameCount, QWidget *parent = 0);
    ~LoadFiles();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::LoadFiles *ui;
};

#endif // LOADFILES_H
