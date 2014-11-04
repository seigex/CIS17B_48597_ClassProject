#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include <QDialog>
#include <QPushButton>
#include "combat_screen.h"

namespace Ui {
class Win_Screen;
}

class Win_Screen : public QDialog
{
    Q_OBJECT

public:
    explicit Win_Screen(QWidget *parent = 0);
    ~Win_Screen();

private:
    Ui::Win_Screen *ui;
    QPushButton *close_button;
private slots:
    void finish();

};

#endif // WIN_SCREEN_H
