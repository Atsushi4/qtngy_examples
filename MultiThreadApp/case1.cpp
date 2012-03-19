/**
  べったりそのまま。
  この関数を抜けるまで
  メインスレッドのイベントループに戻らないので
  スライダは全く動かない。
  画面も反応しない。
**/
#include "multithreadapp.h"
#include "worker.h"

void MultiThreadApp::on_button1_clicked()
{
    Worker w;
    connect(&w, SIGNAL(progressChanged(int,int,int)), SLOT(progressChanged(int,int,int)));
    w.doWork1();
    w.doWork2();
    w.doWork3();
}
