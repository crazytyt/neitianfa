#include "nei_bottom.h"
#include "ui_nei_bottom.h"

void nei_bottom::timeout_action()
{
    QString str;

    mCurTime--;

    if (mCurTime <= 0) {

    } else {

    }

    QTextStream(&str) << " " << mCurTime / 60 << " : " << mCurTime % 60;

    ui->time->setText(str);
}

nei_bottom::nei_bottom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nei_bottom)
{
    ui->setupUi(this);

    ui->time->setText(QString(" 15 : 00"));
    mCurTime = 15 * 60;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout_action()));
}

nei_bottom::~nei_bottom()
{
    delete ui;
}
