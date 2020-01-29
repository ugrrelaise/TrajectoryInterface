#include "mainwindow.h"

#include <QApplication>

#include "lib_ballistic.h"

#include "ui_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Lib_Ballistic libb;

    libb.Test();


    return a.exec();
}
