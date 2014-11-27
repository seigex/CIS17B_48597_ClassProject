#ifndef ITEM_SCREEN_H
#define ITEM_SCREEN_H

#include <QDialog>

namespace Ui {
class Item_screen;
}

class Item_screen : public QDialog
{
    Q_OBJECT

public:
    explicit Item_screen(QWidget *parent = 0);
    ~Item_screen();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::Item_screen *ui;
};

#endif // ITEM_SCREEN_H
