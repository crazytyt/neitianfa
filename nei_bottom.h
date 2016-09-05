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

public slots:
    void timeout_action(void);

public:
    explicit nei_bottom(QWidget *parent = 0);
    ~nei_bottom();
    QTimer  *timer;
private:
    Ui::nei_bottom *ui;

    int mCurTime;
};

#endif // NEI_BOTTOM_H
