/**
  3.2.ダメな使い方－QThreadのrunに処理を書く

  QThreadを継承し，run関数内にそのまま処理を書く。
  run関数内は新しいスレッドなのでそのまま処理がかける。
  execを呼ばないとイベントループが走らないので少し軽量かも？

  でもやっぱり敢えてQThreadを継承する利点が無いと思う。
**/

#include <QThread>
#include "multithreadapp.h"
#include "worker.h"

class Manager2 : public QThread
{
    Q_OBJECT
public:
    Manager2(QObject *parent = 0) : QThread(parent) {}

private:
    void run()
    {
        Worker w;
        connect(&w, SIGNAL(progressChanged(int,int,int)), parent(), SLOT(progressChanged(int,int,int)));
        w.doWork1();
        w.doWork2();
        w.doWork3();
    }
};

void MultiThreadApp::on_button3_clicked()
{
    Manager2 *manager = new Manager2(this);
    // runが終わると勝手に死んでくれるのでちょっと気楽
    connect(manager, SIGNAL(finished()), manager, SLOT(deleteLater()));
    manager->start();
}

#include "case3.moc"
