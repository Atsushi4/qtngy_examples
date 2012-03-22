#include "worker.h"
#include <iostream>
#include <QElapsedTimer>

QMutex Worker::mutex;

Worker::Worker(QObject *parent) :
    QObject(parent)
{
}

// 0.1�b�̎d����30�񂷂�
void Worker::doWork1()
{
    work(1, 100, 30);
}

// 0.4�b�̎d����10�񂷂�
void Worker::doWork2()
{
    work(2, 400, 10);
}

// 0.2�b�̎d����15�񂷂�
void Worker::doWork3()
{
    work(3, 200, 15);
}

void Worker::work(int process, int msecs, int count)
{
    for (int i = 1; i <= count; ++i)
    {
        QElapsedTimer timer;
        timer.start();
        while (timer.elapsed() < msecs)
            ;

        QMutexLocker lock(&mutex);
        (std::cout << QString("done:%1 %2 %3\n").arg(process).arg(i).arg(count).toStdString()).flush();
        emit progressChanged(process, i, count);
    }
}

