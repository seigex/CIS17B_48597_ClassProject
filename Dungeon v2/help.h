#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class Help : public QWidget
{
    Q_OBJECT
public:
    explicit Help(QWidget *parent = 0);

signals:

public slots:
    void closeDialog();
};

#endif // HELP_H
