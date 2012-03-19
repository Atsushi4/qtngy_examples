/**
  3.2.�_���Ȏg�����|QThread��run�ɏ���������

  QThread���p�����Crun�֐����ɂ��̂܂܏����������B
  run�֐����͐V�����X���b�h�Ȃ̂ł��̂܂܏�����������B
  exec���Ă΂Ȃ��ƃC�x���g���[�v������Ȃ��̂ŏ����y�ʂ����H

  �ł�����ς芸����QThread���p�����闘�_�������Ǝv���B
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
    // run���I���Ə���Ɏ���ł����̂ł�����ƋC�y
    connect(manager, SIGNAL(finished()), manager, SLOT(deleteLater()));
    manager->start();
}

#include "moc_case3.cpp"
