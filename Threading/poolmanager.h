#ifndef POOLMANAGER_H
#define POOLMANAGER_H

#include "manager.h"

class PoolManager : public Manager
{
    Q_OBJECT
public:
    explicit PoolManager(QObject *parent = 0);
    
private:
    void run(RunMode mode);

    class Runnable;
};

#endif // POOLMANAGER_H
