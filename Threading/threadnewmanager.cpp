#include "threadnewmanager.h"
#include <QThread>
#include <QDebug>

class ThreadNewManager::CustomThread : public QThread
{
    Q_OBJECT
public:
    explicit CustomThread(QObject *parent) : QThread(parent) {}
    const QList<Worker*> &workers() {return workers_;}
    void go() {emit startWork();}

signals:
    void startWork();
    void stopWork();

private:
    void run() {
        for (int i = 0; i < Manager::WorkerCount; ++i) {
            auto w = new Worker();
            connect(this, SIGNAL(startWork()), w, SLOT(doWork()));
            connect(this, SIGNAL(stopWork()), w, SLOT(stop()));
            connect(this, SIGNAL(finished()), w, SLOT(deleteLater()));
            workers_ << w;
        }

        exec();
    }

    QList<Worker*> workers_;
};


ThreadNewManager::ThreadNewManager(QObject *parent) :
    Manager(parent)
{
    for (int i = 0; i < ThreadCount; ++i) {
        auto t = new CustomThread(this);
        connect(this, SIGNAL(pauseWorker()), t, SIGNAL(stopWork()));
        t->start();
        threads_ << t;
    }
}

ThreadNewManager::~ThreadNewManager()
{
    for (auto t : threads_) {
        t->quit();
        t->wait();
    }
}

void ThreadNewManager::run(Manager::RunMode mode)
{
    // シグナルのマッピング
    if (mode == RunSeries) {
        for (int i = 0; i < WorkerCount; ++i) {
            connect(threads_.at(0)->workers().at(i), SIGNAL(progressChanged(int)), workers().at(i), SIGNAL(progressChanged(int)));
        }
        threads_.at(0)->go();
    } else {
        for (int i = 0; i < WorkerCount; ++i)
            connect(threads_.at(i % ThreadCount)->workers().at(i), SIGNAL(progressChanged(int)), workers().at(i), SIGNAL(progressChanged(int)));

        for (int i = 0; i < ThreadCount; ++i)
            threads_.at(i)->go();
    }
}

#include "threadnewmanager.moc"
