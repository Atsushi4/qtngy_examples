#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "worker.h"

/**
 * @brief The Manager class
 */
class Manager : public QObject
{
    Q_OBJECT
public:
    enum RunMode {
        RunParallel,
        RunSeries
    };
    Q_ENUMS(RunMode)
    static constexpr int WorkerCount = 10;
    static constexpr int ThreadCount = 2;

    virtual ~Manager() {}

protected:
    explicit Manager(QObject *parent = 0);

signals:
    /**
     * @brief progressChanged
     * @param index The Worker's index (0 <= index < WorkerCount)
     * @param done Progress in percent (0 <= done <= 100)
     */
    void progressChanged(int index, int done);
    void workCanceled();
    void workPaused();
    void pauseWorker();

public slots:
    void start(RunMode mode = RunSeries);
    virtual void pause();
    virtual void resume(Manager::RunMode mode);
    virtual void cancel();

protected:
    bool stop() const {return stop_;}
    const QList<Worker*> &workers() const {return workers_;}
    virtual void wait() {}

private:
    virtual void run(RunMode mode) = 0;

private slots:
    void hearProgress(int done);

private:
    QList<Worker*> workers_;
    int finished_;
    bool stop_;
};

#endif // MANAGER_H
