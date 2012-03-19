#include <QtGui/QApplication>
#include "processwatcher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProcessWatcher w;
    w.show();
    return a.exec();
}
