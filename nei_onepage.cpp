#include "nei_onepage.h"
#include "ui_nei_onepage.h"


#include "nei_common.h"

nei_onepage::nei_onepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nei_onepage)
{
    ui->setupUi(this);

    int i, j, p;

    generate_data();

    model = new QStandardItemModel(16, 16, this);
    ui->tableView->setModel(model);
    ui->tableView->resize(QSize(824, 505));
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    for (i=0; i < NUM_ROW * 2; i += 2) {
        for (j=0; j < NUM_COL; j++) {
            QStandardItem *firstRow = new QStandardItem(QString(" "));
            firstRow->setBackground(QBrush(QColor(215, 208, 214)));
            firstRow->setEditable(false);
            firstRow->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, j, firstRow);

        }
        for (j = 0; j < NUM_COL; j++) {
            if (j == 0) {
                QStandardItem *firstRow = new QStandardItem(QString("NULL"));
                firstRow->setBackground(QBrush(QColor(215, 208, 214)));
                firstRow->setEditable(false);
                firstRow->setTextAlignment(Qt::AlignCenter);
                model->setItem(i+1, 0, firstRow);
            } else {
                QStandardItem *firstRow = new QStandardItem(QString(""));
                firstRow->setTextAlignment(Qt::AlignCenter);
                firstRow->setEditable(true);

                model->setItem(i+1, j, firstRow);
            }
        }

    }

    mCurrentPage = 0;
    mCurrentRow = 1;
    mCurrentCol = 1;

    //QModelIndex tRow = model->index(5, 2);
    //QTableView::selectionModel()->select(tRow, QItemSelectionModel::ClearAndSelect |
     //                                    QItemSelectionModel::Rows);
    ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    tSetPosition(1, 1);
    //ui->tableView->selectionModel()->select(tRow, QItemSelectionModel::Select);

    //ui->tableView->edit(tRow, QAbstractItemView::DoubleClicked);
    //ui->tableView->setCurrentIndex(tRow);
    //ui->tableView->setCursor(Qt::IBeamCursor);

    display_onepage(0);
}

nei_onepage::~nei_onepage()
{
    delete ui;
}

void nei_onepage::tSetPosition(int a, int b)
{
    QModelIndex tRow = model->index(a, b);
    ui->tableView->setCurrentIndex(tRow);
}

void nei_onepage::display_onepage(int index)
{
    int i, j;

    for (int i = 0; i < NUM_COL; i++)
        ui->tableView->setColumnWidth(i, 50);

    for (i = 0; i < NUM_ROW * 2; i += 2) {
        for (j = 0; j < NUM_COL; j++) {
            model->item(i, j)->setText(QString::number(mRaw[index][i][j]));
        }
    }
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

    for (i = 0; i < NUM_PAGE; i++) {
        for (j = 0; j < NUM_ROW; j++) {
            for (p = 0; p < NUM_COL - 1; p++) {
                mCorrect[i][j][p] = (mRaw[i][j][p] + mRaw[i][j][p + 1]) % 10;
            }
        }
    }
}
