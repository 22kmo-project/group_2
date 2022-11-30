#include "transactions.h"
#include "ui_transactions.h"
#include <QDebug>


Transactions::Transactions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transactions)
{
    ui->setupUi(this);
}

Transactions::~Transactions()
{
    delete ui;
}

void Transactions::on_btn_Back_clicked()
{

}


void Transactions::on_btn_LogOut_clicked()
{
    qDebug()<<"logout";
}
