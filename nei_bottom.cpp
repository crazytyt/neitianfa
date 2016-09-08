#include "nei_bottom.h"
#include "ui_nei_bottom.h"

#include "nei_common.h"

void nei_bottom::timeout_action()
{
    QString str;

    mCurTime--;

    if (mCurTime <= 0) {

    } else {
		if ((mCurTime % 60) == 0) {
				
		}
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
	timer->start(1000);
}

nei_bottom::~nei_bottom()
{
    delete ui;
}
