#include "dialoggoods.h"
#include "ui_dialoggoods.h"

DialogGoods::DialogGoods(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGoods)
{
    ui->setupUi(this);
}

DialogGoods::~DialogGoods()
{
    delete ui;
}

void DialogGoods::on_buttonBox_accepted()
{
    accept();
}

void DialogGoods::on_buttonBox_rejected()
{
    reject();
}

QString DialogGoods::name() const
{
    return ui->goodsNameContainer->text();
}
int DialogGoods::amount() const
{
    return ui->goodsAmount->value();
}
double DialogGoods::price() const
{
    return ui->goodsPrice->value();
}
