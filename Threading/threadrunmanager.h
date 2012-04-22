#ifndef THREADRUNMANAGER_H
#define THREADRUNMANAGER_H

#include "manager.h"

class ThreadRunManager : public Manager
{
    Q_OBJECT
public:
    explicit ThreadRunManager(QObject *parent = 0);

private slots:
    void finished();

private:
    void run(RunMode mode);
    void wait();
    class CustomThread;
    QList<CustomThread*> threads_;
};

#endif // THREADRUNMANAGER_H
