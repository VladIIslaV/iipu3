#include <QApplication>
#include "window.h"
//#include <thread>

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    Window win;
    win.show();

//    cout << "@@@ Allright @@@" << endl;
    return app.exec();
}
