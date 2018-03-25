#include <QApplication>

#include "startwindow.h"

using namespace std;

int main(int argc, char *argv[]){
    RInside R(argc, argv);
    QApplication app(argc, argv);
    StartWindow startWindow(R);
    startWindow.show();
    return app.exec();
}
