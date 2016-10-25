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
    ui->mSex->setMaxLength(10);
    ui->mName->setFocus();

}

nei_login::~nei_login()
{
    delete ui;
}

void nei_login::getInfo()
{
    mAge = ui->mAge->text();
    mJob = ui->mJob->text();
    mName = ui->mName->text();
    mSex = ui->mSex->text();
}
