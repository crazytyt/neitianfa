#ifndef NEI_LOGIN_H
#define NEI_LOGIN_H

#include <QWidget>

namespace Ui {
class nei_login;
}

class nei_login : public QWidget
{
    Q_OBJECT

public:
    explicit nei_login(QWidget *parent = 0);
    ~nei_login();
    QString mSex, mName, mAge, mJob;
    void getInfo(void);

private:
    Ui::nei_login *ui;
};

#endif // NEI_LOGIN_H
