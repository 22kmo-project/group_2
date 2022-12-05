#include "savings.h"
#include "ui_savings.h"
#include <QDebug>
#include <QByteArray>

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
    savingsUpdate = ui->lineEdit_savingsOn->text();

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
    {
        response_data=reply->readAll();
        qDebug()<<response_data;
        reply->deleteLater();
        savingsManager->deleteLater();
    }



}


void savings::savingsSlot(QNetworkReply *reply)
{
    //hakee savingsmoden?
    QString site_url = "http://localhost:3000/account/savingsmode" + QString::number(id_card);  //!!!
    QNetworkRequest request((site_url));
    //webtoken alku
    QByteArray myToken = "Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"), (myToken));
    //webtoken loppu

    savingsManager = new QNetworkAccessManager(this);
    connect(savingsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(savingsSlot(QNetworkReply*)));
    reply = savingsManager->post(request); //post request?


}



