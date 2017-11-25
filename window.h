#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtWidgets>
#include "battery.h"
#include <stdafx.h>
#include <QtConcurrent/QtConcurrent>
//#include <QThread>
class Window : public QWidget
{
    Q_OBJECT

    QLabel *status,
        *level,
        *time;
    QGridLayout *grid;
    QPushButton *quit,
        *powsaving;
    QLineEdit *timeout;
    Battery b;

    bool isPS;
    char* default_standby;
    static void Timer(Window* parent);


public:
    explicit Window(QWidget *parent = 0);


signals:

public slots:
    void RefreshInfo();
    void Powersaving();
    void SafeExit();
};

#endif // WINDOW_H
