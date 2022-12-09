#include "transactions.h"
#include "ui_transactions.h"
#include <QDebug>
#include <QAbstractScrollArea>
#include <QScrollBar>

Transactions::Transactions(QString givenToken, int idcard, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transactions)
{
    connect(timer10sek,SIGNAL(timeout()),this,SLOT(timer10Slot()));
    ui->setupUi(this);
    token = givenToken;
    id_card = idcard;
    connect(ui->transactions_Table->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(timerReset()));
}

Transactions::~Transactions()
{
    delete ui;
}

void Transactions::startwindowtimer()
{
    timer10sek->start(1000);
}

void Transactions::on_btn_Back_clicked()
{
    timer10sek->stop();
    emit backtomainmenu();
    this->close();
}


void Transactions::on_btn_LogOut_clicked()
{
    timer10sek->stop();
    emit logoutsignal();
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

    TokenEditor(json_doc);
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

void Transactions::timerReset()
{
    time10 = 0;
    emit resetTimer30();
}

QString Transactions::parseDate(QString dateQString) //ottaa vastaan QStringin päivämäärästä ja palauttaa QStringin päivämäärästä eurooppalaisessa muodossa "2022-11-30" --> "30.11.2022"
{
    QString rearrangedDate = "";
    QStringList splittedYearMonthDay = dateQString.split("-");  //["2022","11","30"]
    for(int i=splittedYearMonthDay.length()-1; i>=0;i--){ //pyöräyttää ympäri
        rearrangedDate.append(splittedYearMonthDay[i]);
        if(i!=0){
            rearrangedDate.append("."); //"30.11.2022"
        }
    }
    return rearrangedDate;
}

void Transactions::TokenEditor(QJsonDocument doc) //Ottaa vastaan QJsonDocumentin, pilkkoo sen neljään columniin ja luo rivin jokaisesta transactionista.
{
    ui->transactions_Table->setColumnCount(4);  //Asetetaan columnien määrä ja otsikot, kaikkia columneja joita sql:stä saadaan ei käytetä
    ui->transactions_Table->setHorizontalHeaderLabels({" Date ", " Time ", " Type ", " Amount "});

    QString dateHolder;
    QStringList splittedDateTime;
    QTableWidgetItem *date;

    QString timeHolder;
    QTableWidgetItem *time;

    QTableWidgetItem *type;

    QTableWidgetItem *amount;
    QString logString;

    int row=0;
    foreach(const QJsonValue &value, doc.array()){  //Käy json documentin läpi rivi riviltä
        ui->transactions_Table->insertRow(ui->transactions_Table->rowCount()); //Lisää rivi tableen per transaction
        QJsonObject json_obj = value.toObject();  //objecti rivistä
        qDebug()<<json_obj;

        dateHolder = json_obj["log_time"].toString();  //Pilkotaan log_time päivämäärään ja aikaan koska muoto on 2022-11-30T19:34:43.000Z
        splittedDateTime = dateHolder.split("T");  //["2022-11-30","19:34:43.000Z"]
        date = new QTableWidgetItem(parseDate(splittedDateTime[0])); //["2022-11-30"] --> "30.11.2022"

        timeHolder = splittedDateTime[1].split(".")[0];  //["19:34:43", "000Z"]Otetaan ajasta pelkät tunnit/minuutit/sekunnit pilkkomalla pisteen kohdalta ja ottamalla sen uuden arrayn ensimmäinen osa
        time = new QTableWidgetItem(timeHolder); //["19:34:43"]

        logString = json_obj["log"].toString();
        type = new QTableWidgetItem(logString);

        if(logString=="Debit withdraw" || logString=="Credit withdraw" || logString=="Savingmode on, sent to designated savings acc"){  //Tarkistetaan oliko transactionin tyyppi Debit/credit withdraw ja muutetaan määrä negatiiviseksi jos oli
            amount = new QTableWidgetItem("-" + QString::number(json_obj["amount"].toInt()) + "€" );
        }else{
            amount = new QTableWidgetItem(QString::number(json_obj["amount"].toInt()) + "€");
        }
        ui->transactions_Table->setItem(row, 0, date);  //asetetaan tauluun columnien arvot riville
        ui->transactions_Table->setItem(row, 1, time);
        ui->transactions_Table->setItem(row, 2, type);
        ui->transactions_Table->setItem(row, 3, amount);
        row++;
    }
    ui->transactions_Table->resizeColumnsToContents();
    ui->transactions_Table->resizeRowsToContents();
    ui->transactions_Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->transactions_Table->setCornerWidget(new QWidget());
    ui->transactions_Table->scrollToBottom();
}
