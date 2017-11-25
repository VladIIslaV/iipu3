#ifndef BATTERY_H
#define BATTERY_H
#include <QObject>
#include <fstream>
#include "stdafx.h"

class Battery : public QObject
{

    char str[20];
public:
    Battery();
    const char* getStatus();
    const char* getLevel();
    int getTimeLeft();
    char* getStandbyTime();
};

#endif // BATTERY_H
