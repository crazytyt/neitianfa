#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>

#include "nei_common.h"

nei_bottom *mBottom;
nei_onepage *mOnepage;
nei_result *mRes;
nei_login *mLogin;
QStackedWidget *mStack;
QStackedWidget *mainStack;
int upscreenWidth;
int upscreenHeight;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();
    int screenWidth = screen.width();
    int screenHeight = screen.height();

    upscreenWidth = screenWidth * 0.9;
    upscreenHeight = screenHeight * 0.7; // table is 70% high of screen
    //setWindowFlags(this->windowFlags() |= Qt::FramelessWindowHint);

    setFixedSize(screenWidth * 0.9,screenHeight * 0.9); // 禁止改变窗口大小。

    QPixmap pixmap = QPixmap(":/background.jpg").scaled(this->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

   // this->move(QPoint(30,30));
    mStack = new QStackedWidget(this);

    mBottom = new nei_bottom;
    mOnepage = new nei_onepage;
    mRes = new nei_result;
    mLogin = new nei_login;


    mStack->addWidget(mLogin);
    mStack->addWidget(mOnepage);
mStack->addWidget(mRes); // ========= for test


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
//    mainLayout->setMargin(5);
//    mainLayout->setSpacing(5);

    mainLayout->addWidget(mStack);
    mainLayout->addWidget(mBottom);
    mainLayout->setStretchFactor(mStack, 8);
    mainLayout->setStretchFactor(mBottom, 2);


    qDebug() << upscreenWidth << upscreenHeight << screenWidth << screenHeight;

    twindow = new QWidget();
    twindow->setLayout(mainLayout);
    //twindow->setGeometry(QRect(0, 0, 2500, 2300));
    setCentralWidget(twindow);

    //qDebug() << mStack->width() << mStack->height();
    //this->resize(QSize(1180, 960));
    //window->resize(QSize(800,400));
    QObject::connect(mBottom, SIGNAL(sig_update_page()), mOnepage, SLOT(slot_update_page()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
