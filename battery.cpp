#include "battery.h"

Battery::Battery()
{

}

const char* Battery::getStatus()
{
    char* str1 = new char[20];

    ifstream status;
    status.open("//sys//class//power_supply//BAT1//status");
    if(!status)
    {
        cout << "### Error: open status file ###" << endl;
        return "AC";
    }
    status >> str1;
    if(strstr(str1, "Discharging")){
        cout << str1;
        cout << "### getStatus: Discharging  ###" << endl;
        return "DC";
    }
    cout << "### Laptop either charging or Fully-charged ###" << endl;
    status.close();
    return "AC";
}

const char *Battery::getLevel()
{
    char* str1 = new char[20];

    ifstream level;
    level.open("//sys//class//power_supply//BAT1//capacity");
    if(!level)
    {
        cout << "### Error: open status file: there is no battery ###" << endl;
        return "~";
    }
    level >> str1;
    level.close();
    return str1;
}

int Battery::getTimeLeft()
{
    int level = atoi(getLevel());
    if(level < 1 || level > 100){
        cout << "### Error: there is no battery or smth else ###" << endl;
        return 0;
    }
    return 3 * 60 * level / 100;    //3h0m with 100% capacity;
                                    //level - current capacity
}


