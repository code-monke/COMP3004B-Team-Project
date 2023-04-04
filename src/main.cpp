#include "mainwindow.h"

#include <QApplication>
//#include "Section.h"
//#include "Menu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    w.initSections(&menuSection);

    w.show();
    return a.exec();
}
