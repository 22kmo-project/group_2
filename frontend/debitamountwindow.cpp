#include "debitamountwindow.h"
#include "ui_debitamountwindow.h"

DebitAmountWindow::DebitAmountWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebitAmountWindow)
{
    ui->setupUi(this);
}

DebitAmountWindow::~DebitAmountWindow()
{
    delete ui;
}

void DebitAmountWindow::on_withdraw_btn_clicked()
{
    emit customAmount(ui->withdraw_amount->text().toInt());
    this->close();
}


void DebitAmountWindow::on_back_btn_clicked()
{
    emit back();
    this->close();
}
