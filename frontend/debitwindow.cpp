#include "debitwindow.h"
#include "ui_debitwindow.h"
#include <QDebug>
#include <QByteArray>

DebitWindow::DebitWindow(QString givenToken, int idcard,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebitWindow)
{
    //AJASTIN
    connect(timer10sek,SIGNAL(timeout()),this,SLOT(timer10Slot()));
    ui->setupUi(this);
    id_card = idcard;
    token = givenToken;

}

DebitWindow::~DebitWindow()
{
    delete ui;
}

void DebitWindow::getbalance()
{
    //HAKEE TILIN SALDON
    QString site_url="http://localhost:3000/account/"+QString::number(id_card);
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getBalanceManager = new QNetworkAccessManager(this);
    connect(getBalanceManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getBalanceSlot(QNetworkReply*)));
    reply = getBalanceManager->get(request);
}

void DebitWindow::getowner()
{
    //HAKEE TILINOMISTAJAN TIEDOT
    QString site_url="http://localhost:3000/owner/fname"; //mites sukunimi??
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getOwnerInfoManager = new QNetworkAccessManager(this);

    QJsonObject jsonObj;  // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("id_card",id_card);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(getOwnerInfoManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getOwnerInfoSlot(QNetworkReply*)));
    reply = getOwnerInfoManager->post(request, QJsonDocument(jsonObj).toJson());
}

void DebitWindow::startwindowtimer()
{
    timer10sek->start(1000);
}

void DebitWindow::getBalanceSlot(QNetworkReply *reply)
{
    account_balance_data=reply->readAll();
    qDebug()<<"TILITIEDOT : "+account_balance_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(account_balance_data);
    QJsonObject json_obj = json_doc.object();
    QString balancedata;
    int balance;
    balancedata=QString::number(json_obj["account_balance"].toInt());
    balance=balancedata.toInt();
    qDebug()<<"Kortin saldo on  " <<balance;

    ui->label_balance->setText("Your account balance is: "+ QString::number(balance));
    getowner();
}

void DebitWindow::getOwnerInfoSlot(QNetworkReply *reply)
{
    owner_data=reply->readAll();
    qDebug()<<"DATA : "+owner_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(owner_data);
    QJsonObject json_obj = json_doc.object();
    QString ownerdata;
    ownerdata=json_obj["fname"].toString();
    qDebug()<<"Tilinomistaja on  " <<ownerdata;

    ui->label_info->setText("Account owner is: "+ ownerdata+ "");


}

void DebitWindow::on_btn20_clicked()
{
    timer10sek->stop();
    emit nextwindow(6);
    this->close();
}


void DebitWindow::on_btn40_clicked()
{
    timer10sek->stop();
    emit nextwindow(6);
    this->close();
}


void DebitWindow::on_btn60_clicked()
{
    timer10sek->stop();
    emit nextwindow(6);
    this->close();
}


void DebitWindow::on_btn100_clicked()
{
    timer10sek->stop();
    emit nextwindow(6);
    this->close();
}


void DebitWindow::on_btn200_clicked()
{
    timer10sek->stop();
    emit nextwindow(6);
    this->close();
}


void DebitWindow::on_btn500_clicked()
{
    timer10sek->stop();
    emit nextwindow(6);
    this->close();
}


void DebitWindow::on_btnBack_clicked()
{
    timer10sek->stop();
    emit backtomainmenu();
    this->close();
}

void DebitWindow::timer10Slot()
{
    time10++;
    if (time10>10){
        timer10sek->stop();
        emit backtomainmenu();
        this->close();
    }
}
