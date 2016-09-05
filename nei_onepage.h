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

    enum {  NUM_PAGE = 30, NUM_ROW = 8, NUM_COL = 16 };



public:
    explicit nei_onepage(QWidget *parent = 0);
    ~nei_onepage();

    int mRaw[NUM_PAGE][NUM_ROW][NUM_COL];
    int mResult[NUM_PAGE][NUM_ROW][NUM_COL];

private:
    Ui::nei_onepage *ui;

    void generate_data(void);

};

#endif // NEI_ONEPAGE_H
