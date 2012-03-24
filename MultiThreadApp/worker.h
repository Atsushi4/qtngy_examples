#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>

// ワーカー
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);

signals:
    void progressChanged(int process, int done, int total);
    
public slots:
    void doWork1(); // 100msecの仕事を30回します。
    void doWork2(); // 400msecの仕事を10回します。
    void doWork3(); // 200msecの仕事を15回します。

private:
    void work(int process, int msecs, int count);

private:
    static QMutex mutex;
};

#endif // WORKER_H
