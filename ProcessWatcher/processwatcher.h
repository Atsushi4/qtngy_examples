#ifndef PROCESSWATCHER_H
#define PROCESSWATCHER_H

#include <QtGui>

class ProcessWatcher : public QWidget
{
    Q_OBJECT
    
public:
    ProcessWatcher(QWidget *parent = 0);
    ~ProcessWatcher();

private slots:
    void readStandardOutput();

private:
    QProcess *process;
    QList<QProgressBar*> bars;
    QProgressBar *barTotal;
};

#endif // PROCESSWATCHER_H
