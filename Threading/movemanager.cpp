#include "movemanager.h"

/**
 * moveToThreadする。
 *
 * QThreadインスタンスを作ってstartし，QObjectをmoveToThreadしておくと
 * このQObjectは新しいスレッドに属する。
 *
 * QtのQThreadクラスをそのまま使える上にQObject側を何も変える必要が無い。
 *
 *
 * ワーカスレッドでイベントループが回るので少し重い。
 *
 * 同じスレッド内でしたQObjectの親子関係を作れない。
 */

MoveManager::MoveManager(QObject *parent) :
    Manager(parent)
{
    for (auto w : workers())
        connect(this, SIGNAL(go()), w, SLOT(doWork()));

    for (QThread &t : threads_)
        t.start();
}

MoveManager::~MoveManager()
{
    for (QThread &t : threads_) {
        t.quit();
        t.wait();
    }
}

void MoveManager::run(Manager::RunMode mode)
{
    for (int i = 0; i < WorkerCount; ++i) {
        workers().at(i)->setParent(0);
        workers().at(i)->moveToThread(&threads_[mode == RunSeries ? 0 : (i % ThreadCount)]);
    }

    emit go();
}


