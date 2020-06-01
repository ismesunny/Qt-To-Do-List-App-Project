#include "mainwindow.h"
#include <QDesktopWidget>
#include <QMainWindow>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
/*
    QDesktopWidget setSize;
    int x = setSize.width()*1;
    int y = setSize.height()*.1;
    w.resize(x, y);
    //w.setFixedSize(x, y);
    */
    return a.exec();

}

