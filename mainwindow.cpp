#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int high = 30, low = 10;
    for (int i=0; i<10; i++) {
        //qDebug() << qrand() % ((high + 1) - low) + low;

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
