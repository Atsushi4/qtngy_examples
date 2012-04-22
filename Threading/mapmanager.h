#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "manager.h"

class MapManager : public Manager
{
    Q_OBJECT
public:
    explicit MapManager(QObject *parent = 0);

private:
    void run(RunMode mode);
};

#endif // MAPMANAGER_H
