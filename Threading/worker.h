#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    
signals:
    void progressChanged(int done);
    
public slots:
    void doWork();
    void stop() {stop_ = true;}
    void reset() {progress_ = 0; stop_ = false;}
    void resume() {stop_ = false;}

private:
    int progress_;
    bool stop_;
};

#endif // WORKER_H
