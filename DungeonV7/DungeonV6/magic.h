#ifndef MAGIC_H
#define MAGIC_H

#include <QDialog>
#include "hero.h"

namespace Ui {
class Magic;
}

class Magic : public QDialog, public Hero
{
    Q_OBJECT

public:
    explicit Magic(QWidget *parent = 0);
    ~Magic();

private:
    Ui::Magic *ui;
    QPushButton *fire_button;
    QPushButton *ice_button;
    QPushButton *close_button;
    QTimer *magic_timer;

private slots:
    void execute_fire();
    void execute_ice();
};

#endif // MAGIC_H
