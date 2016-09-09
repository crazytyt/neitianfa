#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "nei_common.h"


nei_bottom *mBottom;
nei_onepage *mOnepage;
nei_result *mRes;
QStackedWidget *mStack;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mStack = new QStackedWidget(this);

    mBottom = new nei_bottom;
    mOnepage = new nei_onepage;
    mRes = new nei_result;

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

    QObject::connect(mBottom, SIGNAL(sig_update_page()), mOnepage, SLOT(slot_update_page()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
