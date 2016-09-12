#include "nei_result.h"
#include "ui_nei_result.h"

#include "nei_common.h"

nei_result::nei_result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nei_result)
{
    ui->setupUi(this);
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
	R2 - X2max - X2min;

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

    QString str;

    QTextStream(&str) << "m1 = " << QString::number(M1, 'g', 2) << ", " << "m2 = " << QString::number(M2, 'g', 2) << "\n";
    QTextStream(&str) << "r1 = " << R1 << ", " << "r2 = " << R2 << "\n";
    QTextStream(&str) << "s1 = " << QString::number(S1, 'g', 2) << ", " << "s2 = " << QString::number(S2, 'g', 2) << "\n";
    QTextStream(&str) << "n = " << QString::number(N, 'g', 2) << ", " << "t = " << QString::number(N, 'g', 2) << ", " << " v = " << V;
    ui->label->setText(str);

    QString str1 = "str1 = ", str2 = "str2 = ";
    for (i = 0; i < 15; i++) {
        QTextStream(&str1) << X1[i] << " ";

    }
    for (i = 0; i < 15; i++) {

        QTextStream(&str2) << X2[i] << " ";
    }
    qDebug() << str1 << " - " << str2;
}
