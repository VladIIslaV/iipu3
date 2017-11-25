#include "window.h"

/*
 * Refresh information about current type of connection,
 * current capacity and time left to full charge(if conection Type == AC)
 * or time to full recharge(if connection Type == DC)
 *
*/
void Window::RefreshInfo()
{
    int time_left;
    char connection_type[3],
            capacity[3];

    strcpy(connection_type, b.getStatus());
    time_left = b.getTimeLeft();
    strcpy(capacity, b.getLevel());

    QString msg = QString("Type of connection: ") +
            QString(connection_type);
    status->setText(msg);       //AC/Battery

    msg = QString("Current capacity: ") +
            QString(capacity) +
            QString("%");
    level->setText(msg);        //current capacity

    if(strstr(capacity, "~"))
    {
        msg = QString("There is no battery");
    }
    else{
        if(strstr(connection_type, "AC")){
            time_left = 180 - time_left;
            msg = QString("To full charge left: ") +
                    QString(time_left/60 + '0') +
                    QString('h') +
                    QString(time_left%60/10 + '0') +
                    QString(time_left%60%10 + '0') +
                    QString('m');
        }
        else{
            msg = QString("Time left: ") +
                    QString(time_left/60 + '0') +
                    QString('h') +
                    QString(time_left%60/10 + '0') +
                    QString(time_left%60%10 + '0') +
                    QString('m');
        }
    }

    time->setText(msg);         //time left work from battery

    if(strstr(b.getStatus(), "AC") && isPS)
        emit Powersaving();
}

/*
 * Enable/disable laptop powersaving mode_t
*/
void Window::Powersaving()
{
    QString str = QString("xset dpms ");

    if(!isPS){
        default_standby = b.getStandbyTime();
        cout << "Default standby: " << default_standby << endl;
        //cout << endl << default_standby << endl;
        //usleep(10000000);
        str += timeout->text();
        system(str.toStdString().c_str());
        system("xset +dpms");
        isPS = true;
    }
    else{
        str += QString(default_standby);
        cout << str.toStdString().c_str() << endl;
        system(str.toStdString().c_str());
        system("xset -dpms");
        isPS = false;
    }
}

/*
 * Exit with disable powersaving mode
*/
void Window::SafeExit()
{
    isPS = true;
    emit Powersaving();
    emit close();
}

/*
 * Emit refresh information every 0.5s
*/
void Window::Timer(Window* parent)
{
    while(true){
        emit parent->RefreshInfo();
        sleep(0.5);
    }
}

Window::Window(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(300);
    this->setFixedWidth(600);
    status = new QLabel(this);
    status->setText("There you'll see your PC connection type.");
    level = new QLabel(this);
    level->setText("There you'll see your PC level of energy.");
    time = new QLabel(this);
    time->setText("There you'll see your PC timeout.");

    quit = new QPushButton(this);
    quit->setText("Quit");
    connect(quit, SIGNAL(clicked(bool)), this, SLOT(SafeExit()));
    powsaving = new QPushButton(this);
    powsaving->setText("On/off powersaving");
    connect(powsaving, SIGNAL(clicked(bool)), this, SLOT(Powersaving()));

    timeout = new QLineEdit(this);
    timeout->setText("Type timeout for powersaving mode");

    grid = new QGridLayout(this);
    grid->addWidget(status, 0,0);
    grid->addWidget(level, 1,0);
    grid->addWidget(time, 2,0);
    grid->addWidget(quit, 3, 4);
    grid->addWidget(powsaving, 1, 4);
    grid->addWidget(timeout, 0, 4);

    QtConcurrent::run(Timer, this);
    isPS = false;
    default_standby = new char[5];
}

