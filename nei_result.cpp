#include "nei_result.h"
#include "ui_nei_result.h"

#include "nei_common.h"

#include <QVector>
#include <QPalette>

nei_result::nei_result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nei_result)
{
    ui->setupUi(this);

    // set title's color and position
    QRect rect = ui->title->geometry();
    rect.moveTo(upscreenWidth/2 - rect.width()/2, rect.y());
    ui->title->setGeometry(rect);

    QPalette pal = ui->title->palette();
    pal.setColor(QPalette::WindowText, QColor(234, 72, 32));
    ui->title->setPalette(pal);

    // set frame's color and position
    rect = ui->frame->geometry();
    rect.setWidth(upscreenWidth/3 * 2);
    rect.setHeight(upscreenHeight/3);
    rect.moveTo(upscreenWidth/2-rect.width()/2, rect.y());
    ui->frame->setGeometry(rect);

    // set result's color and position
    rect = ui->result->geometry();
    rect.setWidth(upscreenWidth/3 * 2);
    rect.setHeight(upscreenHeight/3);
    rect.moveTo(upscreenWidth/2-rect.width()/2, rect.y());
    ui->result->setGeometry(rect);

    pal = ui->result->palette();
    pal.setColor(QPalette::WindowText, QColor(234, 72, 32));
    ui->result->setPalette(pal);

    // set plot's postion and size
    rect.setX(40); rect.setY(upscreenHeight/2);
    rect.setWidth(upscreenWidth-90);
    rect.setHeight(upscreenHeight/2);
    ui->widget->setGeometry(rect);


}

nei_result::~nei_result()
{
    delete ui;
}

void nei_result::cal_para()
{
    int i, j, p;
	int x1sum, x2sum;

    for (i = 0; i < mOnepage->NUM_PAGE / 2; i++) {
        X1[i] = 0;
        for (j = 0; j < mOnepage->NUM_ROW; j++) {
            for (p = 0; p < mOnepage->NUM_COL - 1; p++) {
                if (mOnepage->mResult[i][j][p] == mOnepage->mCorrect[i][j][p]) {
					X1[i]++;
				}
			}
        }
    }

    int index = 0;
    for (i = mOnepage->NUM_PAGE / 2; i < mOnepage->NUM_PAGE; i++) {
        X2[index] = 0;
        for (j = 0; j < mOnepage->NUM_ROW; j++) {
            for (p = 0; p < mOnepage->NUM_COL - 1; p++) {
                if (mOnepage->mResult[i][j][p] == mOnepage->mCorrect[i][j][p]) {
                    X2[index]++;
				}
				//qDebug() << "-- " << i << " " << j << " " << p << " " << mOnepage->mResult[i][j][p] << " " << mOnepage->mCorrect[i][j][p] << "\n";
			}
        }
		index++;

    }

	x1sum = x2sum = 0;
	for (i = 0; i < 15; i++) {
		 x1sum += X1[i] ;
		 x2sum += X2[i] ;
	}

	M1 = x1sum / 15;
	M2 = x2sum / 15;

	X1min = X1[0];
	X1max = X1[0];
	for (i = 1; i < 15; i++) {
		if (X1[i] < X1min)
			X1min = X1[i];
		if (X1[i] > X1max)
			X1max = X1[i];
	}

	X2min = X2[0];
	X2max = X2[0];
	for (i = 1; i < 15; i++) {
		if (X2[i] < X2min)
			X2min = X2[i];
		if (X2[i] > X2max)
			X2max = X2[i];
	}

	R1 = X1max - X1min;
    R2 = X2max - X2min;

	x1sum = x2sum = 0;
	for (i = 0; i < 15; i++) {
        x1sum += abs(X1[i] - X1[1]);
        x2sum += abs(X2[i] - X2[1]);
	}
	S1 = x1sum / 15;
	S2 = x2sum / 15;

	x1sum = x2sum = 0;
	for (i = 0; i < 15; i++) {
		if (X1[i] > X1[1])
			x1sum++;
		if (X1[i] < X1[1])
			x2sum++;
	}
	V1 = x1sum - x2sum;

	x1sum = x2sum = 0;
	for (i = 0; i < 15; i++) {
		if (X2[i] > X2[1])
			x1sum++;
		if (X2[i] < X2[1])
			x2sum++;
	}
	V2 = x1sum - x2sum;
    V = V1 + V2;

	N = X1[0] / M1;
	T = M2 / M1;

	uM1 = 1-(M1-41.63/48.37);
	uM2 = 1-(M2-50.73/49.27);
	uR1 = 1-(R1-12.73/27.27);
	uR2 = 1-(R2-13.18/31.82);
	uS1 = 1-(S1-3.82/8.18);
	uS2 = 1-(S2-4.08/5.92);
	uV = 1-(V-8/20);
	uN = 1-(N-1.10/0.4);
    uT = 1-(T-1.23/0.77);

    mLogin->getInfo();
    QString str;
    QTextStream(&str) << mLogin->mName << "  " << mLogin->mSex << "  " << mLogin->mJob;
    QTextStream(&str) << "  " << mLogin->mAge << "\n";

    QTextStream(&str) << "m1 = " << QString::number(M1, 'g', 2) << ", " << "m2 = " << QString::number(M2, 'g', 2) << "\n";
    QTextStream(&str) << "r1 = " << R1 << ", " << "r2 = " << R2 << "\n";
    QTextStream(&str) << "s1 = " << QString::number(S1, 'g', 2) << ", " << "s2 = " << QString::number(S2, 'g', 2) << "\n";
    QTextStream(&str) << "n = " << QString::number(N, 'g', 2) << ", " << "t = " << QString::number(N, 'g', 2) << ", " << " v = " << V;
    ui->result->setText(str);

//    QString str1 = "str1 = ", str2 = "str2 = ";
//    for (i = 0; i < 15; i++) {
//        QTextStream(&str1) << X1[i] << " ";

//    }
//    for (i = 0; i < 15; i++) {

//        QTextStream(&str2) << X2[i] << " ";
//    }
//    qDebug() << str1 << " - " << str2;

    M1 = 45.07, M2=54.00, R1=11, R2=10,S1=3.93,S2=2.26,N=0.93,T=1.19,V=-4;
    for(int i = 1; i < 16; i++) {
        if (i % 2) {
            X1[i] = 50 + 3;
            X2[i] = 50 - 3;
        } else {
            X1[i] = 50 - 4;
            X2[i] = 50 + 4;
        }
    }

    QCustomPlot *mPlot = ui->widget;

    qDebug() << mPlot->geometry().width() << mPlot->geometry().height() \
             << mPlot->geometry().x() << mPlot->geometry().y();

    QVector<double> keyS15, valueS15;
    for(int i=1;i<16;i++)
    {
        keyS15 << i;
        valueS15 << X1[i];
    }
    mPlot->addGraph();
    mPlot->graph(0)->setPen(QPen(Qt::red));
    mPlot->graph(0)->setData(keyS15,valueS15);
    mPlot->graph(0)->setPen(QPen(QColor(255, 100, 0)));
    //mPlot->graph(0)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // fill with texture of specified image
    mPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    mPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));

    QVector<double> keyE15, valueE15;
    for(int i=1;i<16;i++)
    {
        keyE15 << i;
        valueE15 << X2[i];
    }
    mPlot->addGraph();
    mPlot->graph(1)->setPen(QPen(Qt::blue));
    mPlot->graph(1)->setData(keyE15,valueE15);
    //mPlot->graph(1)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // fill with texture of specified image
    mPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    mPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    //mPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDiamond, Qt::red, Qt::white, 7));

    mPlot->xAxis->setLabel(QStringLiteral("测试时间"));
    mPlot->yAxis->setLabel(QStringLiteral("工作量"));

    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    mPlot->xAxis->setTicker(fixedTicker);
    fixedTicker->setTickStep(1.0);
    fixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);

    mPlot->xAxis->setRange(0,15);
    mPlot->yAxis->setRange(0,100);
    mPlot->xAxis2->setVisible(false);
    mPlot->yAxis2->setVisible(false);

    mPlot->legend->setVisible(true);
    mPlot->graph(0)->setName(QStringLiteral("前十五分钟"));
    mPlot->graph(1)->setName(QStringLiteral("后十五分钟"));


//    QTextStream(&str) << mLogin->mName << "  " << mLogin->mSex << "  " << mLogin->mJob;
//    QTextStream(&str) << "  " << mLogin->mAge << "\n";
//    QTextStream(&str) << "m1 = " << QString::number(M1, 'g', 2) << ", " << "m2 = " << QString::number(M2, 'g', 2) << "\n";
//    QTextStream(&str) << "r1 = " << R1 << ", " << "r2 = " << R2 << "\n";
//    QTextStream(&str) << "s1 = " << QString::number(S1, 'g', 2) << ", " << "s2 = " << QString::number(S2, 'g', 2) << "\n";
//    QTextStream(&str) << "n = " << QString::number(N, 'g', 2) << ", " << "t = " << QString::number(N, 'g', 2) << ", " << " v = " << V;
//    ui->label->setText(str);

//    QString str1 = "str1 = ", str2 = "str2 = ";
//    for (int i = 0; i < 15; i++) {
//        QTextStream(&str1) << X1[i] << " ";

//    }
//    for (int i = 0; i < 15; i++) {

//        QTextStream(&str2) << X2[i] << " ";
//    }
}
