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
    postsavings();

}

savings::~savings()
{
    delete ui;
}

void savings::on_btn_save_savings_clicked()
{
    savingsOn = ui->lineEdit_savingsOn->text();

}



void savings::on_btn_savingsOff_clicked()
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



void savings::postsavings()
{
    QString wb = token;
    QByteArray bearerToken = "Bearer "+wb.toUtf8();
    QString site_url = "http://localhost:3000/account/savingsmode" + QString::number(id_card);  //!!!
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"), (bearerToken));
    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    savingsManager = new QNetworkAccessManager(this);

    connect(savingsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(logsSlots(QNetworkReply*)));
    reply = savingsManager->post(request); //post request?

}


void savings::savingsSlot(QNetworkReply *reply)
{
    {
        response_data=reply->readAll();
        qDebug()<<response_data;
        reply->deleteLater();
        savingsManager->deleteLater();
    }

}



