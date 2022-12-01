#include "savings.h"
#include "ui_savings.h"
#include <QDebug>

savings::savings(QString givenToken, int idcard, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::savings)
{
    connect(timer10sek,SIGNAL(timeout()),this,SLOT(timer10Slot()));
    timer10sek->start(1000);
    ui->setupUi(this);
    token = givenToken;
    id_card = idcard;

}

savings::~savings()
{
    delete ui;
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


void savings::on_btn_logout_clicked()
{
    qDebug()<<"logout";
}

void savings::getsavings()
{
    QString wb = token;
    QByteArray bearerToken = "Bearer "+wb.toUtf8();
    QString site_url = "http://localhost:3000/account/savingsmode" + QString::number(id_card);  //!!!
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"), (bearerToken));

    savingsManager = new QNetworkAccessManager(this);

    connect(savingsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(logsSlots(QNetworkReply*)));
    reply = savingsManager->get(request);

}

