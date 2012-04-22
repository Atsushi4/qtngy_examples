#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "nothreadmanger.h"
#include "threadrunmanager.h"
#include "threadnewmanager.h"
#include "movemanager.h"
#include "poolmanager.h"
#include "runmanager.h"
#include "mapmanager.h"
#include "lamdamapmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow),
    manager_(0),
    total(0)
{
    ui->setupUi(this);
    ui->comboBox->addItem("スレッド無し");
    ui->comboBox->addItem("QThreadのrunに処理を書く");
    ui->comboBox->addItem("QThreadのrunでnewする");
    ui->comboBox->addItem("moveToThreadする！");
    ui->comboBox->addItem("QThreadPool使ってみる");
    ui->comboBox->addItem("QtConcurrentRunする");
    ui->comboBox->addItem("QtConcurrentMapする");
    ui->comboBox->addItem("Lamda使ってみる");

    on_comboBox_currentIndexChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::progressChanged(int index, int done)
{
    findChild<QSlider*>(QString("progressBar_%1").arg(index + 1))
            ->setValue(done);
    ui->progressBar_11->setValue(++total / Manager::WorkerCount);
    if (total == 100 * Manager::WorkerCount)
        finished();
}

Manager *MainWindow::currentManager() const
{
    return manager_;
}

Manager::RunMode MainWindow::mode() const
{
    return ui->parallel->isChecked() ? Manager::RunParallel : Manager::RunSeries;
}

void MainWindow::finished()
{
    ui->comboBox->setEnabled(true);
    ui->pauseButton->setEnabled(false);
    ui->resumeButton->setEnabled(false);
    ui->cancelButton->setEnabled(false);
    ui->startButton->setEnabled(true);
}

void MainWindow::setManager(Manager *manager)
{
    connect(manager, SIGNAL(progressChanged(int,int)), SLOT(progressChanged(int,int)));
    connect(manager, SIGNAL(workCanceled()), SLOT(finished()));
    delete manager_;
    manager_ = manager;
}

void MainWindow::on_startButton_clicked()
{
    if (!manager_) return;

    for (auto b : findChildren<QSlider*>())
        b->setValue(0);

    ui->comboBox->setEnabled(false);
    ui->pauseButton->setEnabled(true);
    ui->cancelButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    qApp->processEvents();

    total = 0;
    currentManager()->start(mode());
}

void MainWindow::on_resumeButton_clicked()
{
    ui->pauseButton->setEnabled(true);
    ui->resumeButton->setEnabled(false);
    currentManager()->resume(mode());
}

void MainWindow::on_pauseButton_clicked()
{
    currentManager()->pause();
    ui->pauseButton->setEnabled(false);
    ui->resumeButton->setEnabled(true);
}

void MainWindow::on_cancelButton_clicked()
{
    currentManager()->cancel();
    ui->pauseButton->setEnabled(false);
    ui->resumeButton->setEnabled(false);
    ui->cancelButton->setEnabled(false);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        setManager(new NoThreadManger(this));
        break;
    case 1:
        setManager(new ThreadRunManager(this));
        break;
    case 2:
        setManager(new ThreadNewManager(this));
        break;
    case 3:
        setManager(new MoveManager(this));
        break;
    case 4:
        setManager(new PoolManager(this));
        break;
    case 5:
        setManager(new RunManager(this));
        break;
    case 6:
        setManager(new MapManager(this));
        break;
    case 7:
        setManager(new LamdaMapManager(this));
        break;
    default:
        break;
    }
}
