#ifndef LAMDAMAPMANAGER_H
#define LAMDAMAPMANAGER_H

#include "manager.h"

class LamdaMapManager : public Manager
{
    Q_OBJECT
public:
    explicit LamdaMapManager(QObject *parent = 0);

private:
    void run(RunMode mode);
};

#endif // LAMDAMAPMANAGER_H
