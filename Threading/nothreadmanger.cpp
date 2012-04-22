#include "nothreadmanger.h"
#include <QApplication>

NoThreadManger::NoThreadManger(QObject *parent) :
    Manager(parent)
{
}

/**
 * スレッドを使用しない。
 *
 * modeがRunParallelの時は
 * ワーカ切り替え時のみイベント処理を回す。
 */
void NoThreadManger::run(RunMode mode)
{
    for (auto w : workers()) {
        if (stop()) break;

        w->doWork();

        if (mode == RunParallel)
            qApp->processEvents();
    }
}
