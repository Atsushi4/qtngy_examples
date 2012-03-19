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
    // �i����M
    void progressChanged(int process, int done, int total);


    // �V���O���X���b�h
    void on_button1_clicked();
    // 3.1.�_���Ȏg�����|QThread��run��new
    void on_button2_clicked();
    // 3.2.�_���Ȏg�����|QThread��run�ɏ���������(exec���Ȃ�)
    void on_button3_clicked();


    // ������
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
