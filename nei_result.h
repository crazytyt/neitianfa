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
	int X1max, X1min, X2max, X2min, R1, R2;
	double M1, M2, S1, S2;
    int V, V1, V2;
	double N, T;
	double uM1, uM2, uR1, uR2, uS1, uS2, uV, uN, uT;
    void cal_para(void);
private:
    Ui::nei_result *ui;
};

#endif // NEI_RESULT_H
