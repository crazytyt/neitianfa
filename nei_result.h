#ifndef NEI_RESULT_H
#define NEI_RESULT_H

#include <QWidget>

namespace Ui {
class nei_result;
}

class nei_result : public QWidget
{
    Q_OBJECT

public:
    explicit nei_result(QWidget *parent = 0);
    ~nei_result();

	int X1[15], X2[15];
    int mErr, mCorr;
    double mErrRate;
    double X1max, X1min, X2max, X2min, R1, R2;
    double M1, M2, S1, S2, V, V1, V2, N, T;
	double uM1, uM2, uR1, uR2, uS1, uS2, uV, uN, uT;
    double calP[2][9], calS[2][9], calC[2][9], calSP[2][9];
    double P, S, C, SP;
    QString mType;
    void cal_para(void);
private:
    Ui::nei_result *ui;
};

#endif // NEI_RESULT_H
