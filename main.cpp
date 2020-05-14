#include <iostream>
#include <QApplication>
#include <src/ui/window/mainwindow/MainWindow.h>

int main(int argc, char*argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
