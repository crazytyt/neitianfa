#ifndef NEI_ONEPAGE_H
#define NEI_ONEPAGE_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QStandardItemModel>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>

namespace Ui {
class nei_onepage;
}

class nei_onepage : public QWidget
{
    Q_OBJECT



signals:

public slots:
    void slot_update_page(void);
    void slot_update_pos(QStandardItem *);
public:
    explicit nei_onepage(QWidget *parent = 0);
    ~nei_onepage();
    enum {  NUM_PAGE = 30, NUM_ROW = 8, NUM_COL = 13 };

    int mRaw[NUM_PAGE][NUM_ROW][NUM_COL];
    int mResult[NUM_PAGE][NUM_ROW][NUM_COL];
    int mCorrect[NUM_PAGE][NUM_ROW][NUM_COL];
    void tSetPosition(int a, int b);
    int mCurrentPage;
    int mCurrentRow;
    int mCurrentCol;

    QStandardItemModel *model;
    void display_onepage(int index);
    void clear_result(void);
    void clear_all(void);

    void save_onepage(void);
    void generate_data(void);


private:
    Ui::nei_onepage *ui;
};

#endif // NEI_ONEPAGE_H
