#include "nei_bottom.h"
#include "ui_nei_bottom.h"

#include "nei_common.h"

void nei_bottom::timeout_action()
{
    QString str;

    mCurTime--;

    if (mCurTime <= 0) {

    } else {
        if ((mCurTime % 5) == 0) {
                emit sig_update_page();
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

    display_time(30 * 60);
    mCurTime = 30 * 60;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout_action()));

}

nei_bottom::~nei_bottom()
{
    delete ui;
}

void nei_bottom::display_time(int time)
{
	QString str;

	QTextStream(&str) << " " << time / 60 << " : " << time % 60;
    ui->time->setText(str);

    //ui->
}

void nei_bottom::init_timer()
{
    display_time(30 * 60);
    mCurTime = 30 * 60;
}

void nei_bottom::on_start_clicked()
{
    mOnepage->mCurrentPage = 0;
	mOnepage->mCurrentRow = 1;
	mOnepage->mCurrentCol = 1;
    init_timer();
			
    mOnepage->display_onepage(0);
    mStack->setCurrentIndex(0);
    ui->start->setEnabled(false);
    timer->start(1000);
    mOnepage->tSetPosition(1, 1);
}

void nei_bottom::on_reset_clicked()
{
    mOnepage->mCurrentPage = 0;
    mOnepage->mCurrentRow = 1;
    mOnepage->mCurrentCol = 1;

    mOnepage->clear_all();
    mStack->setCurrentIndex(0);
    init_timer();
    timer->stop();
    ui->start->setEnabled(true);

}
