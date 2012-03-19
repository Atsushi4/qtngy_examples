#include <QtGui/QApplication>
#include "multithreadapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MultiThreadApp w;
    w.show();
    return a.exec();
}
