#include "poolmanager.h"

#include <QThreadPool>
#include <QRunnable>

class PoolManager::Runnable : public QRunnable
{
public:
    Runnable(Worker* worker) : worker_(worker) {}

private:
    void run() {
        worker_->doWork();
    }

    Worker* worker_;
};

PoolManager::PoolManager(QObject *parent) :
    Manager(parent)
{
}

void PoolManager::run(Manager::RunMode mode)
{
    QThreadPool::globalInstance()->setMaxThreadCount(mode == RunSeries ? 1 : ThreadCount);

    for (auto w : workers())
        QThreadPool::globalInstance()->start(new Runnable(w));
}


