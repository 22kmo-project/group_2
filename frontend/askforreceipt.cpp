#include "askforreceipt.h"
#include "ui_askforreceipt.h"

AskForReceipt::AskForReceipt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AskForReceipt)
{
    ui->setupUi(this);
    receipttimer = new QTimer;
}

AskForReceipt::~AskForReceipt()
{
    delete ui;
}

void AskForReceipt::starttimer()
{
    receipttimer->start(1000);
}

void AskForReceipt::on_btn_no_clicked()
{
    receipttimer->stop();
    emit resettimer30();
    emit backtomainmenu();
    this->close();
}


void AskForReceipt::on_btn_yes_clicked()
{
    receipttimer->stop();
    emit resettimer30();
    emit nextwindow(5);
    this->close();
}


void AskForReceipt::on_btn_logout_clicked()
{
    receipttimer->stop();
    emit logout();
}

void AskForReceipt::receipttimerslot()
{
    time++;
    if(time>5){
        receipttimer->stop();
        emit backtomainmenu();
    }
}

