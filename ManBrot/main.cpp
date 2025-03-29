#include "mainwindow.h"
#include<QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Fractal b;
    b.show();
    return a.exec();
}
