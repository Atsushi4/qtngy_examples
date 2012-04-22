#ifndef THREADNEWMANAGER_H
#define THREADNEWMANAGER_H

#include "manager.h"

class ThreadNewManager : public Manager
{
    Q_OBJECT
public:
    explicit ThreadNewManager(QObject *parent = 0);
    ~ThreadNewManager();

private:
    void run(RunMode mode);
    class CustomThread;
    QList<CustomThread*> threads_;
};

#endif // THREADNEWMANAGER_H
