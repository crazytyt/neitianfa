#include "nei_onepage.h"
#include "ui_nei_onepage.h"

nei_onepage::nei_onepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nei_onepage)
{
    ui->setupUi(this);

    int i, j, p;

//    generate_data();

    QStandardItemModel *model = new QStandardItemModel(16, 16, this);
    ui->tableView->setModel(model);
    ui->tableView->resize(QSize(824, 505));


    for (i=0; i < NUM_ROW * 2; i += 2) {
        for (j=0; j < NUM_COL; j++) {
            QStandardItem *firstRow = new QStandardItem(QString(""));
            firstRow->setBackground(QBrush(QColor(215, 208, 214)));
            firstRow->setEditable(false);
            model->setItem(i, j, firstRow);

        }
        QStandardItem *firstRow = new QStandardItem(QString(""));
        firstRow->setBackground(QBrush(QColor(215, 208, 214)));
        firstRow->setEditable(false);
        model->setItem(i+1, 0, firstRow);
    }

    for (int i = 0; i < NUM_COL; i++)
        ui->tableView->setColumnWidth(i, 50);


}

nei_onepage::~nei_onepage()
{
    delete ui;
}

void nei_onepage::generate_data()
{
    int i, j, p, q;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int high = 9, low = 1;

    for (i=0; i<NUM_PAGE; i++) {
        for (j = 0; j < NUM_ROW; j++) {
            for (p = 0; p < NUM_COL; p++) {
                mRaw[i][j][p] = qrand() % ((high + 1) - low) + low;

                mResult[i][j][p] = 0;
            }
        }
    }
}
