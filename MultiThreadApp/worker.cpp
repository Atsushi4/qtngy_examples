#include "worker.h"
#include <iostream>
#include <windows.h>

QMutex Worker::mutex;

Worker::Worker(QObject *parent) :
    QObject(parent)
{
}

// 0.1秒の仕事を30回する
void Worker::doWork1()
{
    work(1, 100, 30);
}

// 0.4秒の仕事を10回する
void Worker::doWork2()
{
    work(2, 400, 10);
}

// 0.2秒の仕事を15回する
void Worker::doWork3()
{
    work(3, 200, 15);
}

void Worker::work(int process, int msecs, int count)
{
    for (int i = 1; i <= count; ++i)
    {
        ::Sleep(msecs);
        QMutexLocker lock(&mutex);
        (std::cout << QString("done:%1 %2 %3\n").arg(process).arg(i).arg(count).toStdString()).flush();
        emit progressChanged(process, i, count);
    }
}

