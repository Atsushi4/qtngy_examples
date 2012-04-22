#include "lamdamapmanager.h"

#include <QtConcurrentRun>
#include <QtConcurrentMap>

LamdaMapManager::LamdaMapManager(QObject *parent) :
    Manager(parent)
{
}

void LamdaMapManager::run(Manager::RunMode mode)
{
    if (mode == RunSeries) {
        QtConcurrent::run([](const QList<Worker*> workerlist){
            for (auto w : workerlist)
                w->doWork();
        }, workers());
    } else {
        QtConcurrent::map(workers(), [](Worker *w){w->doWork();});
    }
}
