#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>

// ���[�J�[
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);

signals:
    void progressChanged(int process, int done, int total);
    
public slots:
    void doWork1(); // ���[�J�[�֐����̂P
    void doWork2(); // ���[�J�[�֐����̂Q
    void doWork3(); // ���[�J�[�֐����̂R

private:
    void work(int process, int msecs, int count);

private:
    static QMutex mutex;
};

#endif // WORKER_H
