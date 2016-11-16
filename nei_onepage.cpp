#include "nei_onepage.h"
#include "ui_nei_onepage.h"

#include "nei_common.h"


void nei_onepage::slot_update_page()
{

    save_onepage();

    /* update the page, total 30, update first 15 */
    mCurrentPage++;
    mCurrentRow = 1;
    mCurrentCol = 1;
    clear_result();
    display_onepage(mCurrentPage);


    tSetPosition(1, 1);



}

void nei_onepage::slot_update_pos(QStandardItem* item)
{
    //static int j = 0;
    Q_UNUSED(item);

    mCurrentCol++;
    if (mCurrentCol == 16) {
        mCurrentRow += 2;
        if (mCurrentRow >= 30)
            mCurrentRow = 29;
        mCurrentCol = 1;
    }

    tSetPosition(mCurrentRow, mCurrentCol);
    //qDebug() << mCurrentRow << "  " << mCurrentCol;
    //qDebug() << j++ << " -----";
}

nei_onepage::nei_onepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nei_onepage)
{
    ui->setupUi(this);

    int i, j;

    generate_data();

    model = new QStandardItemModel(NUM_ROW * 2, NUM_COL, this);
    ui->tableView->setModel(model);
    ui->tableView->setGeometry(QRect(10, 10, upscreenWidth-50, upscreenHeight-40));
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
                QStandardItem *firstRow = new QStandardItem(QString(" "));
                firstRow->setBackground(QBrush(QColor(215, 208, 214)));
                firstRow->setEditable(false);
                firstRow->setTextAlignment(Qt::AlignCenter);
                model->setItem(i+1, 0, firstRow);
            } else {

                QStandardItem *firstRow = new QStandardItem(QString(" "));
                firstRow->setTextAlignment(Qt::AlignCenter);
                firstRow->setEditable(true);
                model->setItem(i+1, j, firstRow);
            }
        }

    }

    // auto fit the width and height
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c)
    {
        ui->tableView->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

    for (int c = 0; c < ui->tableView->verticalHeader()->count(); ++c)
    {

        ui->tableView->verticalHeader()->setSectionResizeMode(
                    c, QHeaderView::Stretch);
    }

    mCurrentPage = 0;
    mCurrentRow = 1;
    mCurrentCol = 1;

    //QModelIndex tRow = model->index(5, 2);
    //QTableView::selectionModel()->select(tRow, QItemSelectionModel::ClearAndSelect |
     //                                    QItemSelectionModel::Rows);
    //ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    //tSetPosition(1, 1);
    //ui->tableView->selectionModel()->select(tRow, QItemSelectionModel::Select);

    //ui->tableView->edit(tRow, QAbstractItemView::DoubleClicked);
    //ui->tableView->setCurrentIndex(tRow);
    //ui->tableView->setCursor(Qt::IBeamCursor);

    //display_onepage(0);

    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slot_update_pos(QStandardItem*)));
}

nei_onepage::~nei_onepage()
{
    delete ui;
}

void nei_onepage::tSetPosition(int a, int b)
{
    ui->tableView->setFocus();
    QModelIndex tRow = model->index(a, b);
    ui->tableView->setCurrentIndex(tRow);

}

void nei_onepage::display_onepage(int index)
{
    int i, j;

    disconnect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slot_update_pos(QStandardItem*)));
    for (i = 0; i < NUM_ROW; i++) {
        for (j = 0; j < NUM_COL; j++) {
            model->item(i * 2, j)->setText(QString::number(mRaw[index][i][j]));
        }
    }
    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slot_update_pos(QStandardItem*)));
}

void nei_onepage::clear_result()
{
    int i, j;
    QStandardItem *item;

    disconnect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slot_update_pos(QStandardItem*)));
    for (i = 1; i < NUM_ROW * 2; i += 2) {
        for (j = 1; j < NUM_COL; j++) {
                item = model->item(i, j);
                //qDebug() << i << " " << j;
                item->setText(QString(" "));
        }
    }
    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slot_update_pos(QStandardItem*)));
}

void nei_onepage::clear_all()
{
    int i, j;
    QStandardItem *item;

    disconnect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slot_update_pos(QStandardItem*)));
    for (i = 0; i < NUM_ROW * 2; i++) {
        for (j = 0; j < NUM_COL; j++) {
                item = model->item(i, j);
                item->setText(QString(" "));
        }
    }
    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slot_update_pos(QStandardItem*)));
}

void nei_onepage::save_onepage()
{
    int i, j, num;
    QStandardItem *item;
    QString str;
    bool ok;

    /* save the calculate result */
    for (i = 1; i < NUM_ROW * 2; i += 2) {
        for (j = 1; j < NUM_COL; j++) {
                item = model->item(i, j);
                str = item->text();
                num = str.toInt(&ok, 10);
                if (ok == true)
                    mResult[mCurrentPage][(i - 1) / 2][j - 1] = num;
                else
                    mResult[mCurrentPage][(i - 1) / 2][j - 1] = mPOISON;
                //qDebug() << i << " " << j << " " << num;
        }

    }
}

void nei_onepage::generate_data()
{
    int i, j, p;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int high = 9, low = 1;

    for (i=0; i<NUM_PAGE; i++) {
        for (j = 0; j < NUM_ROW; j++) {
            for (p = 0; p < NUM_COL; p++) {
                mRaw[i][j][p] = qrand() % ((high + 1) - low) + low;
                mResult[i][j][p] = 200;
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
