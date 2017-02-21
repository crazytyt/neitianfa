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
    //rect.moveTo(upscreenWidth/2 - rect.width()/2, rect.y());
    rect.moveTo(upscreenWidth/2 - rect.width()/2, 20);
    ui->title->setGeometry(rect);

    QPalette pal = ui->title->palette();
    pal.setColor(QPalette::WindowText, QColor(255, 255, 0));
    ui->title->setPalette(pal);

    // set frame's color and position
    QRect rect1 = ui->title->geometry();
    rect = ui->frame->geometry();
    rect.setWidth(upscreenWidth - 20);
    rect.setHeight(upscreenHeight * 0.5 - rect1.y() - rect1.height() - 4);
    rect.moveTo(5, rect1.y() + rect1.height() + 2);
    ui->frame->setGeometry(rect);

    // set result's color and position
    rect1 = ui->frame->geometry();
    rect = ui->result->geometry();
    rect.setWidth(rect1.width());
    rect.setHeight(rect1.height());
    rect.moveTo(5, 5);  //related to frame widget
    ui->result->setGeometry(rect);

    pal = ui->result->palette();
    pal.setColor(QPalette::WindowText, QColor(255, 255, 0));
    ui->result->setPalette(pal);

    // set plot's postion and size
    rect.setX(40); rect.setY(upscreenHeight/2);
    rect.setWidth(upscreenWidth-90);
    rect.setHeight(upscreenHeight * 0.4);
    ui->widget->setGeometry(rect);


}

nei_result::~nei_result()
{
    delete ui;
}

// four group data for stand calculation
const double PP[2][9] = {
    {0.84, 0.81, 0.83, 0.93, 0.92, 0.85, 1.00, 0.95, 0.98},
    {0.76, 0.73, 0.92, 0.94, 0.91, 0.84, 0.60, 0.94, 0.97}
};
const double SS[2][9] = {
    {0.84, 0.87, 0.97, 0.93, 0.98, 0.91, 0.75, 0.99, 0.92},
    {0.94, 0.91, 0.99, 0.99, 0.99, 0.95, 0.85, 0.99, 0.98}
};
const double CC[2][9] = {
    {0.78, 0.76, 0.90, 0.87, 0.86, 0.86, 1.00, 0.97, 0.94},
    {0.70, 0.70, 0.99, 0.90, 0.98, 0.87, 0.55, 0.98, 0.93}
};
const double SPSP[2][9] = {
    {0.87, 0.81, 0.90, 0.87, 0.89, 0.85, 0.85, 0.96, 0.94},
    {0.96, 0.99, 0.99, 0.96, 0.98, 0.86, 0.90, 0.95, 0.94}
};

void nei_result::cal_para()
{
    int i, j, p;
    double x1sum, x2sum;

    // calculate the first 15 minites result
    mErr = 0;
    for (i = 0; i < mOnepage->NUM_PAGE / 2; i++) {
        X1[i] = 0;
        for (j = 0; j < mOnepage->NUM_ROW; j++) {
            for (p = 0; p < mOnepage->NUM_COL - 1; p++) {
                if (mOnepage->mResult[i][j][p] == mOnepage->mCorrect[i][j][p]) {
					X1[i]++;
                } else if (mOnepage->mResult[i][j][p] != mOnepage->mPOISON) {
                    mErr++;
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
                } else if (mOnepage->mResult[i][j][p] != mOnepage->mPOISON) {
                    mErr++;
                }
				//qDebug() << "-- " << i << " " << j << " " << p << " " << mOnepage->mResult[i][j][p] << " " << mOnepage->mCorrect[i][j][p] << "\n";
			}
        }
		index++;

    }

//    // for test data1
//    X1[0]=63; X1[1]=56; X1[2]=57; X1[3]=58; X1[4]=50; X1[5]=48; X1[6]=49; X1[7]=55;
//    X1[8]=50; X1[9]=61; X1[10]=62; X1[11]=58; X1[12]=59; X1[13]=53; X1[14]=62;
//    X2[0]=79; X2[1]=73; X2[2]=80; X2[3]=65; X2[4]=71; X2[5]=77; X2[6]=76; X2[7]=84;
//    X2[8]=67; X2[9]=68; X2[10]=67; X2[11]=56; X2[12]=68; X2[13]=68; X2[14]=69;

//    // test data2
//    X1[0]=60; X1[1]=55; X1[2]=56; X1[3]=58; X1[4]=58; X1[5]=56; X1[6]=57; X1[7]=62;
//    X1[8]=61; X1[9]=58; X1[10]=66; X1[11]=61; X1[12]=61; X1[13]=62; X1[14]=63;
//    X2[0]=74; X2[1]=70; X2[2]=74; X2[3]=76; X2[4]=67; X2[5]=73; X2[6]=74; X2[7]=75;
//    X2[8]=72; X2[9]=72; X2[10]=68; X2[11]=74; X2[12]=66; X2[13]=67; X2[14]=66;

	x1sum = x2sum = 0;
	for (i = 0; i < 15; i++) {
        mCorr += X1[i] + X2[i];
        x1sum += X1[i] ;
        x2sum += X2[i] ;
	}
    mErrRate = (mErr * 1000 / (mCorr + mErr));
    mErrRate = static_cast<double>(static_cast<int>(mErrRate+5.0))/10.0;

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
        x1sum += qAbs(X1[i] - X1[1]);
        x2sum += qAbs(X2[i] - X2[1]);
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

    uM1 = 1-(qAbs(M1-41.63)/48.37);
    uM2 = 1-(qAbs(M2-50.73)/49.27);
    uR1 = 1-(qAbs(R1-12.73)/27.27);
    uR2 = 1-(qAbs(R2-13.18)/31.82);
    uS1 = 1-(qAbs(S1-3.82)/8.18);
    uS2 = 1-(qAbs(S2-4.08)/5.92);
    if (V < 0.0)
        uV = 1-(qAbs(V+8)/20);
    else
        uV = 1-(qAbs(V-8)/20);

    uN = 1-(qAbs(N-1.10)/0.4);
    uT = 1-(qAbs(T-1.23)/0.77);

    // round them to 3 places of decimal
    M1 = static_cast<double>(static_cast<int>(M1*1000+0.5))/1000.0;
    M2 = static_cast<double>(static_cast<int>(M2*1000+0.5))/1000.0;
    R1 = static_cast<double>(static_cast<int>(R1*1000+0.5))/1000.0;
    R2 = static_cast<double>(static_cast<int>(R2*1000+0.5))/1000.0;
    S1 = static_cast<double>(static_cast<int>(S1*1000+0.5))/1000.0;
    S2 = static_cast<double>(static_cast<int>(S2*1000+0.5))/1000.0;
    V = static_cast<double>(static_cast<int>(V*1000+0.5))/1000.0;
    N = static_cast<double>(static_cast<int>(N*1000+0.5))/1000.0;
    T = static_cast<double>(static_cast<int>(T*1000+0.5))/1000.0;

    uM1 = static_cast<double>(static_cast<int>(uM1*1000+0.5))/1000.0;
    uM2 = static_cast<double>(static_cast<int>(uM2*1000+0.5))/1000.0;
    uR1 = static_cast<double>(static_cast<int>(uR1*1000+0.5))/1000.0;
    uR2 = static_cast<double>(static_cast<int>(uR2*1000+0.5))/1000.0;
    uS1 = static_cast<double>(static_cast<int>(uS1*1000+0.5))/1000.0;
    uS2 = static_cast<double>(static_cast<int>(uS2*1000+0.5))/1000.0;
    uV = static_cast<double>(static_cast<int>(uV*1000+0.5))/1000.0;
    uN = static_cast<double>(static_cast<int>(uN*1000+0.5))/1000.0;
    uT = static_cast<double>(static_cast<int>(uT*1000+0.5))/1000.0;

    qDebug() << M1 << M2 << R1 << R2 << S1 << S2 << V << N << T;
    qDebug() << uM1 << uM2 << uR1 << uR2 << uS1 << uS2 << uV << uN << uT;
    if (V >= 0) {
		// calculate P
        calP[0][0] = qMax(uM1, PP[0][0]);
        calP[0][1] = qMax(uM2, PP[0][1]);
        calP[0][2] = qMax(uR1, PP[0][2]);
        calP[0][3] = qMax(uR2, PP[0][3]);
        calP[0][4] = qMax(uS1, PP[0][4]);
        calP[0][5] = qMax(uS2, PP[0][5]);
        calP[0][6] = qMax(uV, PP[0][6]);
        calP[0][7] = qMax(uN, PP[0][7]);
        calP[0][8] = qMax(uT, PP[0][8]);

        calP[1][0] = qMin(uM1, PP[0][0]);
        calP[1][1] = qMin(uM2, PP[0][1]);
        calP[1][2] = qMin(uR1, PP[0][2]);
        calP[1][3] = qMin(uR2, PP[0][3]);
        calP[1][4] = qMin(uS1, PP[0][4]);
        calP[1][5] = qMin(uS2, PP[0][5]);
        calP[1][6] = qMin(uV, PP[0][6]);
        calP[1][7] = qMin(uN, PP[0][7]);
        calP[1][8] = qMin(uT, PP[0][8]);

		// calculate S
        calS[0][0] = qMax(uM1, SS[0][0]);
        calS[0][1] = qMax(uM2, SS[0][1]);
        calS[0][2] = qMax(uR1, SS[0][2]);
        calS[0][3] = qMax(uR2, SS[0][3]);
        calS[0][4] = qMax(uS1, SS[0][4]);
        calS[0][5] = qMax(uS2, SS[0][5]);
        calS[0][6] = qMax(uV, SS[0][6]);
        calS[0][7] = qMax(uN, SS[0][7]);
        calS[0][8] = qMax(uT, SS[0][8]);

        calS[1][0] = qMin(uM1, SS[0][0]);
        calS[1][1] = qMin(uM2, SS[0][1]);
        calS[1][2] = qMin(uR1, SS[0][2]);
        calS[1][3] = qMin(uR2, SS[0][3]);
        calS[1][4] = qMin(uS1, SS[0][4]);
        calS[1][5] = qMin(uS2, SS[0][5]);
        calS[1][6] = qMin(uV, SS[0][6]);
        calS[1][7] = qMin(uN, SS[0][7]);
        calS[1][8] = qMin(uT, SS[0][8]);

		// calculate C
        calC[0][0] = qMax(uM1, CC[0][0]);
        calC[0][1] = qMax(uM2, CC[0][1]);
        calC[0][2] = qMax(uR1, CC[0][2]);
        calC[0][3] = qMax(uR2, CC[0][3]);
        calC[0][4] = qMax(uS1, CC[0][4]);
        calC[0][5] = qMax(uS2, CC[0][5]);
        calC[0][6] = qMax(uV, CC[0][6]);
        calC[0][7] = qMax(uN, CC[0][7]);
        calC[0][8] = qMax(uT, CC[0][8]);

        calC[1][0] = qMin(uM1, CC[0][0]);
        calC[1][1] = qMin(uM2, CC[0][1]);
        calC[1][2] = qMin(uR1, CC[0][2]);
        calC[1][3] = qMin(uR2, CC[0][3]);
        calC[1][4] = qMin(uS1, CC[0][4]);
        calC[1][5] = qMin(uS2, CC[0][5]);
        calC[1][6] = qMin(uV, CC[0][6]);
        calC[1][7] = qMin(uN, CC[0][7]);
        calC[1][8] = qMin(uT, CC[0][8]);

		// calculate S-P
        calSP[0][0] = qMax(uM1, SPSP[0][0]);
        calSP[0][1] = qMax(uM2, SPSP[0][1]);
        calSP[0][2] = qMax(uR1, SPSP[0][2]);
        calSP[0][3] = qMax(uR2, SPSP[0][3]);
        calSP[0][4] = qMax(uS1, SPSP[0][4]);
        calSP[0][5] = qMax(uS2, SPSP[0][5]);
        calSP[0][6] = qMax(uV, SPSP[0][6]);
        calSP[0][7] = qMax(uN, SPSP[0][7]);
        calSP[0][8] = qMax(uT, SPSP[0][8]);

        calSP[1][0] = qMin(uM1, SPSP[0][0]);
        calSP[1][1] = qMin(uM2, SPSP[0][1]);
        calSP[1][2] = qMin(uR1, SPSP[0][2]);
        calSP[1][3] = qMin(uR2, SPSP[0][3]);
        calSP[1][4] = qMin(uS1, SPSP[0][4]);
        calSP[1][5] = qMin(uS2, SPSP[0][5]);
        calSP[1][6] = qMin(uV, SPSP[0][6]);
        calSP[1][7] = qMin(uN, SPSP[0][7]);
        calSP[1][8] = qMin(uT, SPSP[0][8]);

    } else {
		// calculate P
        calP[0][0] = qMax(uM1, PP[1][0]);
        calP[0][1] = qMax(uM2, PP[1][1]);
        calP[0][2] = qMax(uR1, PP[1][2]);
        calP[0][3] = qMax(uR2, PP[1][3]);
        calP[0][4] = qMax(uS1, PP[1][4]);
        calP[0][5] = qMax(uS2, PP[1][5]);
        calP[0][6] = qMax(uV, PP[1][6]);
        calP[0][7] = qMax(uN, PP[1][7]);
        calP[0][8] = qMax(uT, PP[1][8]);

        calP[1][0] = qMin(uM1, PP[1][0]);
        calP[1][1] = qMin(uM2, PP[1][1]);
        calP[1][2] = qMin(uR1, PP[1][2]);
        calP[1][3] = qMin(uR2, PP[1][3]);
        calP[1][4] = qMin(uS1, PP[1][4]);
        calP[1][5] = qMin(uS2, PP[1][5]);
        calP[1][6] = qMin(uV, PP[1][6]);
        calP[1][7] = qMin(uN, PP[1][7]);
        calP[1][8] = qMin(uT, PP[1][8]);

		// calculate S
        calS[0][0] = qMax(uM1, SS[1][0]);
        calS[0][1] = qMax(uM2, SS[1][1]);
        calS[0][2] = qMax(uR1, SS[1][2]);
        calS[0][3] = qMax(uR2, SS[1][3]);
        calS[0][4] = qMax(uS1, SS[1][4]);
        calS[0][5] = qMax(uS2, SS[1][5]);
        calS[0][6] = qMax(uV, SS[1][6]);
        calS[0][7] = qMax(uN, SS[1][7]);
        calS[0][8] = qMax(uT, SS[1][8]);

        calS[1][0] = qMin(uM1, SS[1][0]);
        calS[1][1] = qMin(uM2, SS[1][1]);
        calS[1][2] = qMin(uR1, SS[1][2]);
        calS[1][3] = qMin(uR2, SS[1][3]);
        calS[1][4] = qMin(uS1, SS[1][4]);
        calS[1][5] = qMin(uS2, SS[1][5]);
        calS[1][6] = qMin(uV, SS[1][6]);
        calS[1][7] = qMin(uN, SS[1][7]);
        calS[1][8] = qMin(uT, SS[1][8]);

		// calculate C
        calC[0][0] = qMax(uM1, CC[1][0]);
        calC[0][1] = qMax(uM2, CC[1][1]);
        calC[0][2] = qMax(uR1, CC[1][2]);
        calC[0][3] = qMax(uR2, CC[1][3]);
        calC[0][4] = qMax(uS1, CC[1][4]);
        calC[0][5] = qMax(uS2, CC[1][5]);
        calC[0][6] = qMax(uV, CC[1][6]);
        calC[0][7] = qMax(uN, CC[1][7]);
        calC[0][8] = qMax(uT, CC[1][8]);

        calC[1][0] = qMin(uM1, CC[1][0]);
        calC[1][1] = qMin(uM2, CC[1][1]);
        calC[1][2] = qMin(uR1, CC[1][2]);
        calC[1][3] = qMin(uR2, CC[1][3]);
        calC[1][4] = qMin(uS1, CC[1][4]);
        calC[1][5] = qMin(uS2, CC[1][5]);
        calC[1][6] = qMin(uV, CC[1][6]);
        calC[1][7] = qMin(uN, CC[1][7]);
        calC[1][8] = qMin(uT, CC[1][8]);

		// calculate S-P
        calSP[0][0] = qMax(uM1, SPSP[1][0]);
        calSP[0][1] = qMax(uM2, SPSP[1][1]);
        calSP[0][2] = qMax(uR1, SPSP[1][2]);
        calSP[0][3] = qMax(uR2, SPSP[1][3]);
        calSP[0][4] = qMax(uS1, SPSP[1][4]);
        calSP[0][5] = qMax(uS2, SPSP[1][5]);
        calSP[0][6] = qMax(uV, SPSP[1][6]);
        calSP[0][7] = qMax(uN, SPSP[1][7]);
        calSP[0][8] = qMax(uT, SPSP[1][8]);

        calSP[1][0] = qMin(uM1, SPSP[1][0]);
        calSP[1][1] = qMin(uM2, SPSP[1][1]);
        calSP[1][2] = qMin(uR1, SPSP[1][2]);
        calSP[1][3] = qMin(uR2, SPSP[1][3]);
        calSP[1][4] = qMin(uS1, SPSP[1][4]);
        calSP[1][5] = qMin(uS2, SPSP[1][5]);
        calSP[1][6] = qMin(uV, SPSP[1][6]);
        calSP[1][7] = qMin(uN, SPSP[1][7]);
        calSP[1][8] = qMin(uT, SPSP[1][8]);

    }

    // round them to 3 places of decimal
	for (i=0; i<2; i++) {
		for (j=0; j<9; j++) {
            calP[i][j] = static_cast<double>(static_cast<int>(calP[i][j]*1000+0.5))/1000.0;
            calS[i][j] = static_cast<double>(static_cast<int>(calS[i][j]*1000+0.5))/1000.0;
            calC[i][j] = static_cast<double>(static_cast<int>(calC[i][j]*1000+0.5))/1000.0;
            calSP[i][j] = static_cast<double>(static_cast<int>(calSP[i][j]*1000+0.5))/1000.0;
		}
	}
//    for (i=0; i<2; i++) {
//        for (j=0; j<9; j++) {
//            qDebug() << calP[i][j] << calS[i][j] <<calC[i][j] <<calSP[i][j] ;
//        }
//    }

    // calculate P, S, C, SP
    double pmax = calP[1][0], pmin = calP[0][0];
    double smax = calS[1][0], smin = calS[0][0];
    double cmax = calC[1][0], cmin = calC[0][0];
    double spmax = calSP[1][0], spmin = calSP[0][0];

    for (i=1; i<9; i++) {
        pmax = qMax(calP[1][i], pmax);
        smax = qMax(calS[1][i], smax);
        cmax = qMax(calC[1][i], cmax);
        spmax = qMax(calSP[1][i], spmax);
        pmin = qMin(calP[0][i], pmin);
        smin = qMin(calS[0][i], smin);
        cmin = qMin(calC[0][i], cmin);
        spmin = qMin(calSP[0][i], spmin);
    }

    P = 0.5*(pmax + (1 - pmin));
    S = 0.5*(smax + (1 - smin));
    C = 0.5*(cmax + (1 - cmin));
    SP = 0.5*(spmax + (1 - spmin));

    qDebug() << " --- " << P << S << C << SP;

    double ttype = P;
    j = 0;
    if (S > ttype) {
        j = 1;
        ttype = S;
    }
    if (C > ttype) {
        j = 2;
        ttype = C;
    }
    if (SP > ttype) {
        j = 3;
        ttype = SP;
    }
    QString type[] = {QStringLiteral("黏液质"), QStringLiteral("多血质"),
                      QStringLiteral("胆汁质"), QStringLiteral("多-黏质")};
    mType = type[j];

    mLogin->getInfo();

    QString str;
    //QTextStream(&str) << mType << " ";
    QTextStream(&str) << QStringLiteral("姓名: ") << mLogin->mName << "  ";
    QTextStream(&str )<< QStringLiteral("年龄: ") << mLogin->mAge << "  ";
    QTextStream(&str )<< QStringLiteral("性别: ") << mLogin->mSex << " ";
    QTextStream(&str )<< QStringLiteral("职业: ") << mLogin->mJob << "  ";
    QTextStream(&str )<< QStringLiteral("地域: ") << mLogin->mLoc << "  ";
    QTextStream(&str )<< QStringLiteral("学历: ") << mLogin->mDegree << "\n\n";

    QTextStream(&str) << "M1=" << QString::number(M1, 'g', 6) << "  ";
    QTextStream(&str) << "M2=" << QString::number(M2, 'g', 6) << "  ";
    QTextStream(&str) << "R1=" << QString::number(R1, 'g', 6) << "  ";
    QTextStream(&str) << "R2=" << QString::number(R2, 'g', 6) << "  ";
    QTextStream(&str) << "S1=" << QString::number(S1, 'g', 6) << "  ";
    QTextStream(&str) << "S2=" << QString::number(S2, 'g', 6) << "  ";
    QTextStream(&str) << "V=" << QString::number(V, 'g', 6) << "  ";
    QTextStream(&str) << "N=" << QString::number(N, 'g', 6) << "  ";
    QTextStream(&str) << "T=" << QString::number(T, 'g', 6) << "\n";

    QTextStream(&str) << "uM1=" << QString::number(uM1, 'g', 6) << "  ";
    QTextStream(&str) << "uM2=" << QString::number(uM2, 'g', 6) << "  ";
    QTextStream(&str) << "uR1=" << QString::number(uR1, 'g', 6) << "  ";
    QTextStream(&str) << "uR2=" << QString::number(uR2, 'g', 6) << "  ";
    QTextStream(&str) << "uS1=" << QString::number(uS1, 'g', 6) << "  ";
    QTextStream(&str) << "uS2=" << QString::number(uS2, 'g', 6) << "  ";
    QTextStream(&str) << "uV=" << QString::number(uV, 'g', 6) << "  ";
    QTextStream(&str) << "uN=" << QString::number(uN, 'g', 6) << "  ";
    QTextStream(&str) << "uT=" << QString::number(uT, 'g', 6) << "\n";

    QTextStream(&str) << "P=" << QString::number(P, 'g', 6) << "  ";
    QTextStream(&str) << "S=" << QString::number(S, 'g', 6) << "  ";
    QTextStream(&str) << "C=" << QString::number(C, 'g', 6) << "  ";
    QTextStream(&str) << "SP=" << QString::number(SP, 'g', 6) << "\n\n";
    QTextStream(&str) << QStringLiteral("性格类型: ") << mType << "  ";
    QTextStream(&str) << QStringLiteral("答题合计: ") << mErr + mCorr << "  ";
    QTextStream(&str) << QStringLiteral("错误合计: ") << mErr << "  ";
    QTextStream(&str) << QStringLiteral("错误率: ") << QString::number(mErrRate, 'g', 4);

    ui->result->setText(str);

    /* plot the result */
    QCustomPlot *mPlot = ui->widget;

    QVector<double> keyS15, valueS15;
    for(int i=1;i<16;i++)
    {
        keyS15 << i;
        valueS15 << X1[i-1];
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
        valueE15 << X2[i-1];
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

    mPlot->xAxis->setRange(0,16);
    mPlot->yAxis->setRange(0,100);
    mPlot->xAxis2->setVisible(false);
    mPlot->yAxis2->setVisible(false);

    mPlot->legend->setVisible(true);
    mPlot->graph(0)->setName(QStringLiteral("前十五分钟"));
    mPlot->graph(1)->setName(QStringLiteral("后十五分钟"));
    mPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
}
