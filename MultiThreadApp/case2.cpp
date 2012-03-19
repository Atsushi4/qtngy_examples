/**
  3.1.ダメな使い方－QThreadのrunでnew

  QThreadを継承し，run関数内でWorkerをnewする。
  run関数内でnewされたWorkerは新しいスレッドに属する。
  このWorkerのslotは新しいスレッドで実行される。
  ワーカスレッドは一つなのでWorkerを3つに分けても並列化しない。

  敢えてQThreadを継承する利点が無い。
**/

#include <QThread>
#include "multithreadapp.h"
#include "worker.h"

class Manager1 : public QThread
{
    Q_OBJECT
public:
    Manager1(QObject *parent = 0) : QThread(parent) {}

signals:
    void go();

private:
    void run()
    {
        Worker *worker1 = new Worker;
        Worker *worker2 = new Worker;
        Worker *worker3 = new Worker;

        connect(worker1, SIGNAL(progressChanged(int,int,int)), parent(), SLOT(progressChanged(int,int,int)));
        connect(worker2, SIGNAL(progressChanged(int,int,int)), parent(), SLOT(progressChanged(int,int,int)));
        connect(worker3, SIGNAL(progressChanged(int,int,int)), parent(), SLOT(progressChanged(int,int,int)));

        connect(this, SIGNAL(go()), worker1, SLOT(doWork1()));
        connect(this, SIGNAL(go()), worker2, SLOT(doWork2()));
        connect(this, SIGNAL(go()), worker3, SLOT(doWork3()));

        connect(this, SIGNAL(finished()), worker1, SLOT(deleteLater()));
        connect(this, SIGNAL(finished()), worker2, SLOT(deleteLater()));
        connect(this, SIGNAL(finished()), worker3, SLOT(deleteLater()));

        exec();
    }
};

void MultiThreadApp::on_button2_clicked()
{
    Manager1 *t = new Manager1(this);
    connect(this, SIGNAL(finished(bool)), t, SLOT(quit()));
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
    t->start();
    QTimer::singleShot(100, t, SIGNAL(go()));
}

#include "moc_case2.cpp"
