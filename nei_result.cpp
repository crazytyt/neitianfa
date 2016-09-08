#include "nei_result.h"
#include "ui_nei_result.h"

#include "nei_common.h"

nei_result::nei_result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nei_result)
{
    ui->setupUi(this);
}

nei_result::~nei_result()
{
    delete ui;
}
