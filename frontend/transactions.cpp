#include "transactions.h"
#include "ui_transactions.h"
#include <QDebug>
#include "restapiurl.h"

Transactions::Transactions(QString givenToken, int idcard, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transactions)
{
    ui->setupUi(this);
    token = givenToken;
    id_card = idcard;
    qDebug()<<id_card;
    getTransactions();
}

Transactions::~Transactions()
{
    delete ui;
}

void Transactions::on_btn_Back_clicked()
{

}


void Transactions::on_btn_LogOut_clicked()
{
    qDebug()<<"logout";
}

void Transactions::getTransactions()
{
    QString wb = token;  //Haetaan saatu webToken
    QByteArray bearerToken = "Bearer "+wb.toUtf8();  //Tungetaan token qbytearrayhin
    QString site_url = restApiURL::getBaseUrl()+"/logs/" + QString::number(id_card);  //määritetään oikea id
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

void Transactions::setTransactionsView()
{

}
