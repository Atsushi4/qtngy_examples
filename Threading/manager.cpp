#include "manager.h"
#include <QDebug>

Manager::Manager(QObject *parent) :
    QObject(parent)
{
    for (int i = 0; i < WorkerCount; ++i) {
        auto w = new Worker(this);
        connect(w, SIGNAL(progressChanged(int)), SLOT(hearProgress(int)));
        connect(this, SIGNAL(pauseWorker()), w, SLOT(stop()), Qt::DirectConnection);
        workers_ << w;
    }
}


void Manager::start(Manager::RunMode mode)
{
    stop_ = false;
    finished_ = 0;
    for (auto w : workers_)
        w->reset();
    run(mode);
}

void Manager::pause()
{
    stop_ = true;
    emit pauseWorker();
    wait();
    emit workPaused();
}

void Manager::resume(Manager::RunMode mode)
{
    stop_ = false;
    for (auto w : workers_)
        w->resume();
    run(mode);
}

void Manager::cancel()
{
    stop_ = true;
    emit pauseWorker();
    wait();
    emit workCanceled();
}

void Manager::hearProgress(int done)
{
    emit progressChanged(workers_.indexOf(qobject_cast<Worker*>(sender())), done);
}
