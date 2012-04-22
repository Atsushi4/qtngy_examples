#include "threadrunmanager.h"

#include <QThread>
#include <QDebug>

class ThreadRunManager::CustomThread : public QThread
{
    Q_OBJECT
public:
    CustomThread(const QList<Worker*> &workers)
        : workers_(workers), stop_(false)
    {
    }

public slots:
    void workCancel() {stop_ = true;}

private:
    /**
     * QThreadを継承してrunに処理を書く。
     * execを呼ばないのでワーカスレッドではイベントループを回さない。
     */
    void run()
    {
        for (int i = 0; i < workers_.size(); ++i) {
            if (stop_) break;

            workers_.at(i)->doWork();
        }
    }
    QList<Worker*> workers_;
    bool stop_;
};

ThreadRunManager::ThreadRunManager(QObject *parent) :
    Manager(parent)
{
}

void ThreadRunManager::finished()
{
    threads_.removeAll(qobject_cast<CustomThread*>(sender()));
}

void ThreadRunManager::run(Manager::RunMode mode)
{
    threads_.clear();
    // lamda
    auto func = [&](const QList<Worker*> workers){
        auto thread = new CustomThread(workers);
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), SLOT(finished()));
        connect(this, SIGNAL(pauseWorker()), thread, SLOT(workCancel()), Qt::DirectConnection);
        thread->start();
        threads_ << thread;
    };

    if (mode == RunSeries) {
        func(workers());
    } else {
        QList<Worker*> workerLists[ThreadCount];
        for (int i = 0; i < workers().size(); ++i) {
            workerLists[i % ThreadCount] << workers().at(i);
        }

        for (int i = 0; i < ThreadCount; ++i) {
            func(workerLists[i]);
        }
    }
}

void ThreadRunManager::wait()
{
    for (auto t : threads_) {
        t->wait();
    }
}

#include "threadrunmanager.moc"
