#include "transactions.h"
#include "ui_transactions.h"
#include <QDebug>

Transactions::Transactions(QString givenToken, int idcard, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transactions)
{
    connect(timer10sek,SIGNAL(timeout()),this,SLOT(timer10Slot()));
    timer10sek->start(1000);
    ui->setupUi(this);
    token = givenToken;
    id_card = idcard;
    getTransactions();
}

Transactions::~Transactions()
{
    delete ui;
}

void Transactions::on_btn_Back_clicked()
{
    timer10sek->stop();
    emit backtomainmenu();
    this->close();
}


void Transactions::on_btn_LogOut_clicked()
{
    qDebug()<<"logout";
}

void Transactions::getTransactions()
{
    QString wb = token;  //Haetaan saatu webToken
    QByteArray bearerToken = "Bearer "+wb.toUtf8();  //Tungetaan token qbytearrayhin
    QString site_url = "http://localhost:3000/logs/" + QString::number(id_card);  //määritetään oikea id
    QNetworkRequest request((site_url)); //määritetään requestiin urli
    request.setRawHeader(QByteArray("Authorization"), (bearerToken)); //asetetaan requestin Authorization headeri tokeniksi

    logsManager = new QNetworkAccessManager(this);

    connect(logsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(logsSlots(QNetworkReply*)));//connectilla signaalin ja slotin yhdistys

    reply = logsManager->get(request);  //lähetetään GET-request*/
}

void Transactions::logsSlots(QNetworkReply *reply)
{
    response_data = reply->readAll();  //luetaan reply
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data); //luodaan replystä json-data järkevään muotoon
    QJsonArray json_array = json_doc.array(); //määritetään siitä array
    QString logs;

    foreach(const QJsonValue &value, json_array){  //syötetään joka json-array:n valuesta jotain ruudulle
        QJsonObject json_obj = value.toObject();
        //logs+=QString::number(json_obj["id_logs"].toInt()) + ", ";
        //logs+=QString::number(json_obj["id_account"].toInt()) + ", ";
        logs+=json_obj["log_time"].toString()+ ", ";  //Etsi kenttä "log_time" ja hae sen tieto stringginä ja lisää logs tekstikenttään.
        logs+=json_obj["log"].toString() + ", ";
        //logs+=json_obj["log_time"].toString()+ ", ";
        logs+=QString::number(json_obj["amount"].toInt()) + "€\n";  //huomaa lopussa rivinvaihto
    }

    qDebug()<<response_data;
    qDebug()<<logs;
    reply->deleteLater();
}

void Transactions::timer10Slot()
{
    time10++;
    if (time10>10){
        timer10sek->stop();
        emit backtomainmenu();
        this->close();
    }
}

void Transactions::setTransactionsView()
{

}

