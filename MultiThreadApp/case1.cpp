/**
  �ׂ����肻�̂܂܁B
  ���̊֐��𔲂���܂�
  ���C���X���b�h�̃C�x���g���[�v�ɖ߂�Ȃ��̂�
  �X���C�_�͑S�������Ȃ��B
  ��ʂ��������Ȃ��B
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
