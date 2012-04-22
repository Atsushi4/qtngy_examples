#ifndef MOVEMANAGER_H
#define MOVEMANAGER_H

#include "manager.h"
#include <QThread>

class MoveManager : public Manager
{
    Q_OBJECT
public:
    explicit MoveManager(QObject *parent = 0);
    ~MoveManager();
    
signals:
    void go();

private:
    void run(RunMode mode);
    QThread threads_[ThreadCount];
};

#endif // MOVEMANAGER_H
