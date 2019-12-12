#include "mainwindow.h"
#include "detection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    FacialLandmarkDetector::getInstance();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
