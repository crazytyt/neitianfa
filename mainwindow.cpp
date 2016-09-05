#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "nei_onepage.h"
#include "nei_result.h"
#include "nei_bottom.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mStack = new QStackedWidget(this);

    nei_bottom *mBottom = new nei_bottom;
    nei_onepage *mOnepage = new nei_onepage;
    nei_result *mRes = new nei_result;

    mStack->addWidget(mOnepage);
    mStack->addWidget(mRes);


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
//    mainLayout->setMargin(5);
//    mainLayout->setSpacing(5);

    mainLayout->addWidget(mStack);
    mainLayout->addWidget(mBottom);
    mainLayout->setStretchFactor(mStack, 8);
    mainLayout->setStretchFactor(mBottom, 1);

    QWidget *window = new QWidget();
    window->setLayout(mainLayout);
    setCentralWidget(window);

}

MainWindow::~MainWindow()
{
    delete ui;
}
