#include "debitbalance.h"
#include "ui_debitbalance.h"
#include <QDebug>

Debitbalance::Debitbalance(QString givenToken, int idcard, int cred, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Debitbalance)

{
    connect(timer10sek,SIGNAL(timeout()),this,SLOT(timer10Slot()));
    ui->setupUi(this);
    token = givenToken;
    id_card = idcard;
    credit = cred;
//  account_balance = debitbalance;


}

Debitbalance::~Debitbalance()
{
    delete ui;
}

void Debitbalance::startwindowtimer()
{
    timer10sek->start(1000);
}

void Debitbalance::getBalances()
{
    // HAKEE DEBITBALANCEN TIETOKANNASTA
    QString site_url="http://localhost:3000/account/balance/"+QString::number(id_card);
    QNetworkRequest request((site_url));

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    getdebitbalancemanager = new QNetworkAccessManager(this);
    connect(getdebitbalancemanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getdebitbalanceSlot(QNetworkReply*)));
    reply = getdebitbalancemanager->get(request);

}

void Debitbalance::getdebitbalanceSlot(QNetworkReply *reply)
{
    debitbalance_data=reply->readAll();
    qDebug()<<"DATA : "+debitbalance_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(debitbalance_data);
    QJsonObject json_obj = json_doc.object();    // Tätä menetelmää voi käyttää kun vastauksena on 1 objekti
    int debitbalance;
    QString debitbalancedata;                           // Jos vastaus on array (esim logs), käytä QBYTEARRAY
    debitbalancedata=QString::number(json_obj["account_balance"].toInt());
    debitbalance = debitbalancedata.toInt();

    qDebug()<<"Debit saldo on  " <<debitbalance;
    ui->label_debitbalance->setText("Your debit balance is: " +debitbalancedata+ " €.");
//  reply->deleteLater();
    if(credit > 0){
            // HAKEE CREDITBALANCEN TIETOKANNASTA
            QString site_url="http://localhost:3000/account/credit/"+QString::number(id_card);
            QNetworkRequest request((site_url));

            //WEBTOKEN ALKU
            QByteArray myToken="Bearer "+token.toLocal8Bit();
            request.setRawHeader(QByteArray("Authorization"),(myToken));
            //WEBTOKEN LOPPU

            QNetworkAccessManager * getcreditbalancemanager = new QNetworkAccessManager(this);
            connect(getcreditbalancemanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getcreditbalanceSlot(QNetworkReply*)));
            reply = getcreditbalancemanager->get(request);
        }
}

void Debitbalance::getcreditbalanceSlot(QNetworkReply *reply)
{
    creditbalance_data=reply->readAll();
    qDebug()<<"DATA : "+creditbalance_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(creditbalance_data);
    QJsonObject json_obj = json_doc.object();    // Tätä menetelmää voi käyttää kun vastauksena on 1 objekti
    int creditbalance;
    QString creditbalancedata;                           // Jos vastaus on array (esim logs), käytä QBYTEARRAY
    creditbalancedata=QString::number(json_obj["credit_balance"].toInt());
    creditbalance = creditbalancedata.toInt();

    qDebug()<<"Debit saldo on  " <<creditbalance;
    ui->label_creditbalance->setText("Available credit: " +creditbalancedata+ " €.");

}


void Debitbalance::timer10Slot()
{
    time10++;
    if (time10>10){
        time10=0;
        timer10sek->stop();
        emit backtomainmenu();
        this->close();
    }
}

void Debitbalance::on_btn_Back_clicked()
{
    emit resettimer30();
    timer10sek->stop();
    time10=0;
    emit backtomainmenu();
    this->close();
}

