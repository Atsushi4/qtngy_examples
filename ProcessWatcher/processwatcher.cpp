#include "processwatcher.h"

ProcessWatcher::ProcessWatcher(QWidget *parent)
    : QWidget(parent)
{
    bars << 0 << 0 << 0;
    QFormLayout *l;
    setLayout(l = new QFormLayout());
    l->addWidget(new QLabel("<font size=+2 color=gray><i><b>Sub</b></i><font>"));
    l->addRow(new QLabel("Process1"), bars[0] = new QProgressBar);
    l->addRow(new QLabel("Process2"), bars[1] = new QProgressBar);
    l->addRow(new QLabel("Process3"), bars[2] = new QProgressBar);
    l->addRow(new QLabel("<font color=red><b>Total</b></font>"), barTotal = new QProgressBar);
    barTotal->setMaximum(3);

    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), SLOT(readStandardOutput()));
    connect(process, SIGNAL(finished(int)), qApp, SLOT(quit()));
    process->start("MultiThreadApp");
}

ProcessWatcher::~ProcessWatcher()
{
    process->kill();
    process->waitForFinished();
}

void ProcessWatcher::readStandardOutput()
{
    QString str = process->readAll();
    qDebug() << str;

    QStringList lines = str.split("\n", QString::SkipEmptyParts);
    foreach (QString line, lines) {
        if (line.startsWith("pos:")) {
            line.remove("pos:");
            move(line.split(" ").at(0).toInt(), line.split(" ").at(1).toInt());
        } else if (line.startsWith("done:")) {
            line.remove("done:");
            QStringList values = line.split(" ");
            QProgressBar *bar = bars[values.at(0).toInt() - 1];
            bar->setMaximum(values.at(2).toInt());
            bar->setValue(values.at(1).toInt());
            barTotal->setValue(barTotal->value() + 1);
        } else if (line.startsWith("start:")) {
            line.remove("start:");
            barTotal->setMaximum(line.toInt());
            foreach (QProgressBar *bar, bars) {
                bar->setValue(0);
            }
            barTotal->setValue(0);
        }
    }
}
