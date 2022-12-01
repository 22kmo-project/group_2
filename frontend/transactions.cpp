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
        logs+=QString::number(json_obj["amount"].toInt()) + "€\n";  //huomaa lopussa rivinvaihto
    }
    //Date, Time, Type, Amount

    TokenEditor(json_doc);


    //qDebug()<<response_data;
    //qDebug()<<logs;
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

void Transactions::TokenEditor(QJsonDocument doc) //Ottaa vastaan QJsonDocumentin, pilkkoo sen kolmeen columniin ja luo rivin jokaisesta transactionista.
{
    qDebug()<<doc;
    //ui->ui_user->setRowCount(1);
    ui->ui_user->setColumnCount(3);
    ui->ui_user->setHorizontalHeaderLabels({"Date", "Type", "Amount"});

    QTableWidgetItem *date;
    QTableWidgetItem *type;
    QTableWidgetItem *amount;
    QString withdraw = "Debit withdraw";
    QString logString;
    //Rakenna seuraavaksi daten pilkkoja
    int row=0;
    foreach(const QJsonValue &value, doc.array()){
        ui->ui_user->insertRow ( ui->ui_user->rowCount() );
        QJsonObject json_obj = value.toObject();
        qDebug()<<json_obj;

        date = new QTableWidgetItem(json_obj["log_time"].toString());
        logString = json_obj["log"].toString();
        type = new QTableWidgetItem(logString);
        if(logString==withdraw){
            amount = new QTableWidgetItem("-" + QString::number(json_obj["amount"].toInt()) + "€" );
        }else{
            amount = new QTableWidgetItem(QString::number(json_obj["amount"].toInt()) + "€");
        }
        ui->ui_user->setItem(row, 0, date);
        ui->ui_user->setItem(row, 1, type);
        ui->ui_user->setItem(row, 2, amount);
        row++;
    }

    ui->ui_user->resizeColumnsToContents();
    ui->ui_user->resizeRowsToContents();
}
