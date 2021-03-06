#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QStandardItemModel>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWidget *twindow;
private slots:

private:

    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H
