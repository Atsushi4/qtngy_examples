#ifndef RUNMANAGER_H
#define RUNMANAGER_H

#include "manager.h"
#include <QFuture>

class RunManager : public Manager
{
    Q_OBJECT
public:
    explicit RunManager(QObject *parent = 0);
    ~RunManager();
    
private:
    void run(RunMode mode);
    void doWork(int begin, int end);

    QFuture<void> future;
};

#endif // RUNMANAGER_H
