#include "mapmanager.h"

#include <QtConcurrentMap>

MapManager::MapManager(QObject *parent) :
    Manager(parent)
{
}

static void doWork(Worker *worker) {
    worker->doWork();
}

void MapManager::run(Manager::RunMode mode)
{
    QtConcurrent::map(workers(), ::doWork);
}
