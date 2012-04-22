#include "runmanager.h"

#include <QtConcurrentRun>
#include <QFutureSynchronizer>

/**
 * 処理の呼び出しをほぼそのまま書けるので
 * 同じクラスの別のメソッドだけを別スレッドで実行したい時なんかに便利かも？
 *
 * キャンセルや同期などにはrunの戻り値のQFutureを使う。
 */

RunManager::RunManager(QObject *parent) :
    Manager(parent)
{
}

RunManager::~RunManager()
{
}

void RunManager::run(Manager::RunMode mode)
{
    // なぜか直に書いたらundefined reference. minGWのバグ！？
    constexpr int workercount = WorkerCount;

    if (mode == RunSeries) {
        QtConcurrent::run(this, &RunManager::doWork, 0, workercount);
    } else {
        for (int i = 0; i < ThreadCount; ++i) {
            const int numPerThread = workercount / ThreadCount;
            QtConcurrent::run(this, &RunManager::doWork, numPerThread * i, numPerThread * (i + 1));
        }
    }
}

void RunManager::doWork(int begin, int end)
{
    for (int i = begin; i < end; ++i)
        workers().at(i)->doWork();
}
