#ifndef MULTITHREADAPP_H
#define MULTITHREADAPP_H

#include <QtGui>

class MultiThreadApp : public QWidget
{
    Q_OBJECT
public:
    typedef QSlider ProgressDisplay;
//    typedef QProgressBar ProgressDisplay;

public:
    MultiThreadApp(QWidget *parent = 0);
    ~MultiThreadApp();

public slots:
    // 進捗受信
    void progressChanged(int process, int done, int total);


    // シングルスレッド
    void on_button1_clicked();
    // 3.1.ダメな使い方－QThreadのrunでnew
    void on_button2_clicked();
    // 3.2.ダメな使い方－QThreadのrunに処理を書く(execしない)
    void on_button3_clicked();


    // 初期化
    void start();


signals:
    void finished(bool result);

private:
    void moveEvent(QMoveEvent *event);

private:
    static const int CaseCount = 3;
    QList<ProgressDisplay*> bars;
    ProgressDisplay *barTotal;
};

#endif // MULTITHREADAPP_H
