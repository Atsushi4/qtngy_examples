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
    void doWork1(); // ワーカー関数その１
    void doWork2(); // ワーカー関数その２
    void doWork3(); // ワーカー関数その３

private:
    void work(int process, int msecs, int count);

private:
    static QMutex mutex;
};

#endif // WORKER_H
