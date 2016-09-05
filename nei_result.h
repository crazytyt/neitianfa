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

private:
    Ui::nei_result *ui;
};

#endif // NEI_RESULT_H
