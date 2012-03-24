#include "multithreadapp.h"
#include <iostream>
#include "worker.h"

static void addButton(QWidget *window, QLayout *layout, int index);

MultiThreadApp::MultiThreadApp(QWidget *parent)
    : QWidget(parent)
{
    bars << 0 << 0 << 0;
    QFormLayout *l;
    setLayout(l = new QFormLayout());
    l->addWidget(new QLabel("<font size=+2><i><b>Main</b></i><font>"));
    l->addRow(new QLabel("Process1"), bars[0] = new ProgressDisplay);
    l->addRow(new QLabel("Process2"), bars[1] = new ProgressDisplay);
    l->addRow(new QLabel("Process3"), bars[2] = new ProgressDisplay);
    l->addRow(new QLabel("<font color=red><b>Total</b></font>"), barTotal = new ProgressDisplay);
    barTotal->setMaximum(3);

    foreach (ProgressDisplay *bar, bars) {
        bar->setOrientation(Qt::Horizontal);
    }
    barTotal->setOrientation(Qt::Horizontal);

    for (int i = 1; i <= CaseCount; ++i) {
        addButton(this, l, i);
    }

    QMetaObject::connectSlotsByName(this);
}

MultiThreadApp::~MultiThreadApp()
{
    
}

void MultiThreadApp::progressChanged(int process, int done, int total)
{
    if (process < 1 || process > 3) exit(QMessageBox::critical(0, "error", "invalid arguments."));

    bars[process - 1]->setMaximum(total);
    bars[process - 1]->setValue(done);

    if (total == done) {
        barTotal->setValue(barTotal->value() + 1);
        if (barTotal->value() == barTotal->maximum()) {
            emit finished(true);
        }
    }
}

void MultiThreadApp::moveEvent(QMoveEvent *event)
{
    QPoint p = event->pos();
    p = window()->mapFrom(this, p);
    // win xpだと4だけど7だと7？ウィンドウのサイズはどうやって取るんだろう。。。
    p.rx() -= 7;
    p.ry() += window()->height() + 7;
    (std::cout << QString("pos:%1 %2\n").arg(p.x()).arg(p.y()).toStdString()).flush();
}

void MultiThreadApp::start()
{
    qobject_cast<QPushButton*>(sender())->setEnabled(false);
    (std::cout << "start:55\n").flush();
    foreach (ProgressDisplay *bar, bars) {
        bar->setValue(0);
    }
    barTotal->setValue(0);
    qApp->processEvents();
}

void addButton(QWidget *window, QLayout *layout, int index)
{
    QPushButton *button = new QPushButton(window->style()->standardIcon(QStyle::SP_MessageBoxCritical), QString("Case &%1").arg(index));
    button->setObjectName(QString("button%1").arg(index));
    window->connect(button, SIGNAL(clicked()), SLOT(start()));
    button->connect(window, SIGNAL(finished(bool)), SLOT(setEnabled(bool)));
    layout->addWidget(button);
}


