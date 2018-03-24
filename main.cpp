#include <QApplication>

#include "startwindow.h"

using namespace std;

int main(int argc, char *argv[]){
    //RInside R(argc, argv);
    QApplication app(argc, argv);
    StartWindow startWindow;
    startWindow.show();
    return app.exec();
}
