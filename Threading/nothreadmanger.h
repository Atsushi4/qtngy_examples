#ifndef NOTHREADMANGER_H
#define NOTHREADMANGER_H
#include "manager.h"

class NoThreadManger : public Manager
{
    Q_OBJECT
public:
    explicit NoThreadManger(QObject *parent = 0);

private:
    void run(RunMode mode);
};

#endif // NOTHREADMANGER_H
