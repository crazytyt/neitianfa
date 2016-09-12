#ifndef NEI_BOTTOM_H
#define NEI_BOTTOM_H

#include <QWidget>
#include <QTextStream>
#include <QTime>
#include <QTimer>

#include <QDebug>

namespace Ui {
class nei_bottom;
}

class nei_bottom : public QWidget
{
    Q_OBJECT

signals:
    void sig_update_page(void);

    void sig_15min_handle(void);
    void sig_30min_handle(void);

public slots:
    void timeout_action(void);
    void slot_15min_handle(void);
    void slot_30min_handle(void);


public:
    explicit nei_bottom(QWidget *parent = 0);
    ~nei_bottom();
    QTimer  *timer;
    void display_time(int time);

    void init_timer(void);

private slots:
    void on_start_clicked();

    void on_reset_clicked();

private:
    Ui::nei_bottom *ui;

    int mCurTime;
};

#endif // NEI_BOTTOM_H
