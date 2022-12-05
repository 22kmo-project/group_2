#include "savings.h"
#include "ui_savings.h"
#include <QDebug>

savings::savings(QString givenToken, int idcard, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::savings)
{
    connect(timer10sek,SIGNAL(timeout()),this,SLOT(timer10Slot()));

    ui->setupUi(this);
    token = givenToken;
    id_card = idcard;

}

savings::~savings()
{
    delete ui;
}

void savings::startwindowtimer()
{
    timer10sek->start(1000);
}

void savings::on_btn_savingsOn_clicked()
{

}


void savings::on_btn_savingsOff_clicked()
{

}

void savings::logsSlots(QNetworkReply *reply)
{

}

void savings::timer10Slot()
{
    time10++;
    if (time10>10){
        timer10sek->stop();
        emit backtomainmenu();
        this->close();
    }
}
