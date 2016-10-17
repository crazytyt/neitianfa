#include "nei_login.h"
#include "ui_nei_login.h"

#include <QValidator>

nei_login::nei_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nei_login)
{
    ui->setupUi(this);

    QValidator *validator = new QIntValidator(5,100,this);
    ui->mAge->setValidator(validator);
    ui->mJob->setMaxLength(10);
    ui->mName->setMaxLength(10);
    ui->mPlace->setMaxLength(10);
}

nei_login::~nei_login()
{
    delete ui;
}
