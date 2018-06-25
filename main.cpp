#include "citystatmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CityStatMainWindow w;
    w.show();

    return a.exec();
}
