#include "debitwindow.h"
#include "ui_debitwindow.h"
#include "session.h"
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

void DebitWindow::startwindowtimer()
{
    timer10sek->start(1000);
}

void DebitWindow::resets()
{
    time10=0;
    emit resettimer30();
}

void DebitWindow::getBalanceSlot(QNetworkReply *reply)
{
    account_balance_data=reply->readAll();
    qDebug()<<"DATA : "+account_balance_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(account_balance_data);
    QJsonObject json_obj = json_doc.object();
    QString balancedata;
    int balance;
    balancedata=QString::number(json_obj["account_balance"].toInt());
    balance=balancedata.toInt();
    qDebug()<<"Kortin saldo on  " <<balance;

    ui->label_balance->setText("Your account balance is: "+ QString::number(balance));
    getowner();DebitWindow
}

void DebitWindow::getowner()
{
    //HAKEE TILINOMISTAJAN TIEDOT
    QString site_url="http://localhost:3000/owner/alldata/" + QString::number(id_card); //mites sukunimi??
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getOwnerInfoManager = new QNetworkAccessManager(this);

    connect(getOwnerInfoManager, SIGNAL(finished (QNetworkReply)), this, SLOT(getOwnerInfoSlot(QNetworkReply)));
    reply = getOwnerInfoManager->get(request);
}

void DebitWindow::debitWithdrawSlot(QNetworkReply *reply)
{
    debit_withdraw_data=reply->readAll();
    qDebug()<<"DATA : "+debit_withdraw_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(debit_withdraw_data);
    QJsonObject json_obj = json_doc.object();
    int withdrawdata;
    withdrawdata=json_obj["affectedRows"].toInt();
    if(withdrawdata>0){
        timer10sek->stop();
        emit nextwindow(6);
        this->close();
    }
    if(withdrawdata==0){
        time10=0;
        emit resettimer30();
        ui->error_label->setText("Insufficient funds");

    }
}

void DebitWindow::customAmount(int amount)
{
    this->show();
    resets();
    withdraw(amount);
}

void DebitWindow::showUI()
{
    resets();
    this->show();
}

void DebitWindow::withdraw(int amount)
{
    //HAKEE DEBITBALANCEN
    QString site_url="http://localhost:3000/card/debitwithdraw";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    QJsonObject jsonObj;
    jsonObj.insert("id_card", id_card);
    jsonObj.insert("amount", amount);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    debitWithdrawManager = new QNetworkAccessManager(this);
    connect(debitWithdrawManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(debitWithdrawSlot(QNetworkReply*)));
    reply = debitWithdrawManager->get(request);
}

void DebitWindow::getOwnerInfoSlot(QNetworkReply *reply)
{
    owner_data=reply->readAll();
    qDebug()<<"DATA : "+owner_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(owner_data);
    QJsonObject json_obj = json_doc.object();
    QString ownerfname = json_obj["fname"].toString();
    QString ownerlname = json_obj["lname"].toString();
    QString address = json_obj["address"].toString();
    QString phonenumber = json_obj["phonenumber"].toString();
    QString email = json_obj["email"].toString();
    QString ownerInfo =
            "Account owner: " + ownerfname + " " + ownerlname + "\n" +
            "Address: " + address + "\n" +
            "Phonenumber: " + phonenumber + "\n"
            "Email: " + email + "\n";
    ui->label_info->setText(ownerInfo);
}

void DebitWindow::on_btn20_clicked()
{
    resets();
    withdraw(20);

}


void DebitWindow::on_btn40_clicked()
{
    resets();
    withdraw(40);
}


void DebitWindow::on_btn60_clicked()
{
    resets();
    withdraw(60);
}


void DebitWindow::on_btn100_clicked()
{
    resets();
    withdraw(100);
}


void DebitWindow::on_btn200_clicked()
{
    resets();
    withdraw(200);
}


void DebitWindow::on_btn500_clicked()
{
    resets();
    withdraw(500);
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

void DebitWindow::on_btnOther_clicked()
{
    amountWindow = new DebitAmountWindow(this);
    connect(amountWindow, SIGNAL(customAmount(int)), this, SLOT(customAmount(int)));
    connect(amountWindow, SIGNAL(back()), this, SLOT(showUI()));
    amountWindow->show();
    resets();
    this->hide();
}

