#include "debitwindow.h"
#include "ui_debitwindow.h"
#include <QDebug>

DebitWindow::DebitWindow(QString token, int idcard,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebitWindow)
{
    connect(timer10sek,SIGNAL(timeout()),this,SLOT(timer10Slot()));
    timer10sek->start(1000);
    ui->setupUi(this);
    token = givenToken;
    id_card = idcard;

    QString site_url="http://localhost:3000/account/account_balance";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getBalanceManager = new QNetworkAccessManager(this);

    QJsonObject jsonObj;  // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("id_card",id_card);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(getBalanceManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getBalanceSlot(QNetworkReply*)));
    reply = getBalanceManager->post(request, QJsonDocument(jsonObj).toJson());
}

DebitWindow::~DebitWindow()
{
    delete ui;
}

void DebitWindow::getBalanceSlot(QNetworkReply *reply)
{
    account_balance_data=reply->readAll();
    qDebug()<<"DATA : "+account_balance_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(account_balance_data);
    QJsonObject json_obj = json_doc.object();
    QString balancedata;
    balancedata=json_obj["balance"].toString();
    qDebug()<<"Kortin saldo on  " <<balancedata;

    ui->label_balance->setText("Your account balance is: "+ balancedata+ "");
}

void DebitWindow::on_btn20_clicked()
{
    resetAllTimers();
    emit nextwindow(1);
    this->close();
}


void DebitWindow::on_btn40_clicked()
{
    resetAllTimers();
    emit nextwindow(1);
    this->close();
}


void DebitWindow::on_btn60_clicked()
{
    resetAllTimers();
    emit nextwindow(1);
    this->close();
}


void DebitWindow::on_btn100_clicked()
{
    resetAllTimers();
    emit nextwindow(1);
    this->close();
}


void DebitWindow::on_btn200_clicked()
{
    resetAllTimers();
    emit nextwindow(1);
    this->close();
}


void DebitWindow::on_btn500_clicked()
{
    resetAllTimers();
    emit nextwindow(1);
    this->close();
}


void DebitWindow::on_btnBack_clicked()
{
    resetAllTimers();
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

