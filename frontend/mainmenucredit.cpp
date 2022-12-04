#include "mainmenucredit.h"
#include "ui_mainmenucredit.h"

MainMenuCredit::MainMenuCredit(QString t, int idcard,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuCredit)
{
    token=t;
    id_card=idcard;
    ui->setupUi(this);

    // HAE OWNERIN NIMI TERVEHDYKSEEN
    QString site_url="http://localhost:3000/owner/fname";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getfnamemanager = new QNetworkAccessManager(this);

    QJsonObject jsonObj;  // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("id_card",id_card);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(getfnamemanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getfnameSlot(QNetworkReply*)));
    reply = getfnamemanager->post(request, QJsonDocument(jsonObj).toJson());
}

MainMenuCredit::~MainMenuCredit()
{
    delete ui;
}

void MainMenuCredit::resetAllTimers()
{
    emit resettimer30();
}

void MainMenuCredit::cleardata()
{
    id_card = 0;
    token = "";
}

void MainMenuCredit::updateTimeUi(int time)
{
    ui->label_sessiontime->setText("Session will end in "+QString::number(30-time)+ " sec");
}

void MainMenuCredit::on_btn_debit_withdraw_clicked()
{
    resetAllTimers();
    emit nextwindow(1);
    this->hide();
}
void MainMenuCredit::on_btn_logs_clicked()
{
    resetAllTimers();
    emit nextwindow(2);
    this->hide();
}

void MainMenuCredit::on_btn_logout_clicked()
{
    emit logout();
}

void MainMenuCredit::getfnameSlot(QNetworkReply *reply)
{
    fname_data=reply->readAll();
    qDebug()<<"DATA : "+fname_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(fname_data);
        QJsonObject json_obj = json_doc.object();    // Tätä menetelmää voi käyttää kun vastauksena on 1 objekti
        QString fnamedata;                           // Jos vastaus on array (esim logs), käytä QBYTEARRAY
        fnamedata=json_obj["fname"].toString();
        qDebug()<<"Kortinomistajan etunimi on  " <<fnamedata;

       ui->label_greeting->setText("Welcome "+ fnamedata+ ", what do you want to do?");
}


void MainMenuCredit::on_btn_debit_settings_clicked()
{
    resetAllTimers();
    emit nextwindow(3);
    this->hide();
}

void MainMenuCredit::on_btn_debit_balance_clicked()
{
    resetAllTimers();
    emit nextwindow(4);
    this->hide();
}
