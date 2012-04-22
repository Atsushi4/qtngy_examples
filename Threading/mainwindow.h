#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

#include "manager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void progressChanged(int index, int done);


private:
    Manager *currentManager() const;
    Manager::RunMode mode() const;

private slots:
    void finished();

private slots:
    void on_startButton_clicked();
    void on_resumeButton_clicked();
    void on_pauseButton_clicked();
    void on_cancelButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    void setManager(Manager *manager);

private:
    Ui::MainWindow *ui;
    Manager* manager_;
    int total;
};

#endif // MAINWINDOW_H
