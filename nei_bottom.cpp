#include "nei_bottom.h"
#include "ui_nei_bottom.h"

#include "nei_common.h"

void nei_bottom::timeout_action()
{
    QString str;

    mCurTime--;
    QTextStream(&str) << " " << mCurTime / 60 << " : " << mCurTime % 60;

    /*
     *     save_onepage();


    mCurrentPage++;

    display_onepage(mCurrentPage);

    clear_result();
    tSetPosition(1, 1);

    mCurrentRow = 1;
    mCurrentCol = 1;
    */
    ui->time->setText(str);
    if (mCurTime <= 0) {
        emit sig_30min_handle();
        //qDebug() << " --- over";
        /* done the first part */
    } else if (mCurTime == 15 * 60){

        emit sig_15min_handle();
        //qDebug() << " --- half";
    } else if (mCurTime % 60 == 0){

        emit sig_update_page();
         //qDebug() << " --- page: " << mOnepage->mCurrentPage;
    }


}

void nei_bottom::slot_15min_handle()
{
    ui->start->setText(QStringLiteral("继续"));  // continue
    ui->start->setEnabled(true);
    timer->stop();
    mOnepage->save_onepage();
    mOnepage->clear_all();
    mOnepage->mCurrentPage++;
}

void nei_bottom::slot_30min_handle()
{
    timer->stop();
    mOnepage->save_onepage();
    mOnepage->clear_all();

    ui->start->setText(QStringLiteral("开始"));   //start

    ui->start->setEnabled(true);

    mRes->cal_para();
    mStack->setCurrentIndex(2);
}

nei_bottom::nei_bottom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nei_bottom)
{
    ui->setupUi(this);

    QRect pos = ui->start->geometry();
    pos.moveTo(upscreenWidth/3, pos.y());
    ui->start->setGeometry(pos);

    pos = ui->reset->geometry();
    pos.moveTo(upscreenWidth/3*2, pos.y());
    ui->reset->setGeometry(pos);

    display_time(30 * 60);
    mCurTime = 30 * 60;
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(timeout_action()));
    QObject::connect(this, SIGNAL(sig_15min_handle()), this, SLOT(slot_15min_handle()));
    QObject::connect(this, SIGNAL(sig_30min_handle()), this, SLOT(slot_30min_handle()));
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

}

void nei_bottom::init_timer()
{
    display_time(30 * 60);
    mCurTime = 30 * 60;

}
// code for this file is gb2312.
const int time_int = 1000;
void nei_bottom::on_start_clicked()
{
    if (mOnepage->mCurrentPage != 15) {

        mOnepage->mCurrentPage = 0;
        mOnepage->mCurrentRow = 1;
        mOnepage->mCurrentCol = 1;
        init_timer();

        mOnepage->display_onepage(0);
        mStack->setCurrentIndex(1);
        ui->start->setEnabled(false);
        timer->start(time_int);
        mOnepage->tSetPosition(1, 1);
        //qDebug() << "first --";
        /* pause */
    } else {
        mOnepage->clear_all();

        mStack->setCurrentIndex(1);
        ui->start->setEnabled(false);
        timer->start(time_int);
        mOnepage->display_onepage(15);
        mOnepage->mCurrentRow = 1;
        mOnepage->mCurrentCol = 1;
        mOnepage->tSetPosition(1, 1);

    }
}

void nei_bottom::on_reset_clicked()
{

    mOnepage->mCurrentPage = 0;
    mOnepage->mCurrentRow = 1;
    mOnepage->mCurrentCol = 1;

    mOnepage->clear_all();
    mOnepage->generate_data();
    mStack->setCurrentIndex(1);
    init_timer();
    timer->stop();
    ui->start->setEnabled(true);
    ui->start->setText(QStringLiteral("开始")); //start
}
