#include "worker.h"
#include <QElapsedTimer>
#include <QMutex>
#include <QMutexLocker>
#include <iostream>

static QMutex mutex;

Worker::Worker(QObject *parent) :
    QObject(parent)
{
}

void Worker::doWork()
{
    QElapsedTimer t;
    while (progress_ < 100) {
        if (stop_) break;

        t.start();
        while (t.elapsed() < 10)
            ;

        emit progressChanged(++progress_);
        QMutexLocker lock(&mutex);
        std::cout << progress_ << std::endl;
    }
}

