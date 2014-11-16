/********************************************************************************
** Form generated from reading UI file 'titlescreen.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TITLESCREEN_H
#define UI_TITLESCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TitleScreen
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label;

    void setupUi(QDialog *TitleScreen)
    {
        if (TitleScreen->objectName().isEmpty())
            TitleScreen->setObjectName(QString::fromUtf8("TitleScreen"));
        TitleScreen->resize(533, 300);
        TitleScreen->setMinimumSize(QSize(533, 300));
        TitleScreen->setMaximumSize(QSize(533, 300));
        pushButton = new QPushButton(TitleScreen);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(220, 230, 75, 23));
        pushButton_2 = new QPushButton(TitleScreen);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 260, 75, 23));
        pushButton_3 = new QPushButton(TitleScreen);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(440, 260, 75, 23));
        label = new QLabel(TitleScreen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 491, 211));
        label->setPixmap(QPixmap(QString::fromUtf8("../../../Pictures/GameTitle.jpg")));
        label->setScaledContents(true);

        retranslateUi(TitleScreen);

        QMetaObject::connectSlotsByName(TitleScreen);
    } // setupUi

    void retranslateUi(QDialog *TitleScreen)
    {
        TitleScreen->setWindowTitle(QApplication::translate("TitleScreen", "RPG", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("TitleScreen", "NEW GAME", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("TitleScreen", "QUIT", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("TitleScreen", "OPTIONS", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TitleScreen: public Ui_TitleScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TITLESCREEN_H
