#include "receiptwindow.h"
#include "ui_receiptwindow.h"

ReceiptWindow::ReceiptWindow(QString tok, QString cn, int cid,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReceiptWindow)
{
    timer10sek=new QTimer;
    ui->setupUi(this);
    token = tok;
    id_card = cid;
    ui->label_savelogs->clear();
    ui->label_amount_save->clear();
    cardnumber = cn;
}

ReceiptWindow::~ReceiptWindow()
{
    delete ui;
}

void ReceiptWindow::getLatestLog()
{
    QString site_url="http://localhost:3000/logs/latest/"+QString::number(id_card);
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getlatestlogmanager = new QNetworkAccessManager(this);

    connect(getlatestlogmanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getlatestlogSlot(QNetworkReply*)));
    reply = getlatestlogmanager->get(request);
}

void ReceiptWindow::getsavingsmode()
{
    QString site_url="http://localhost:3000/account/savingsmode/"+QString::number(id_card);
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getsavingsmanager = new QNetworkAccessManager(this);

    connect(getsavingsmanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getsavingsSlot(QNetworkReply*)));
    reply = getsavingsmanager->get(request);
}

void ReceiptWindow::getsavelog()
{
    QString site_url="http://localhost:3000/logs/latestsave/"+QString::number(id_card);
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getsavelogmanager = new QNetworkAccessManager(this);
    connect(getsavelogmanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getsavelogSlot(QNetworkReply*)));
    reply = getsavelogmanager->get(request);
}

void ReceiptWindow::startwindowtimer()
{
    timer10sek->start(1000);
}

void ReceiptWindow::getlatestlogSlot(QNetworkReply * reply)
{
    latest_data=reply->readAll();
    qDebug()<<"Viimesin loki : "+latest_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(latest_data);
        QJsonObject json_obj = json_doc.object();
        QString latestlogdata;
        QString test="Debit withdraw";
        QString amount;
        QString timeholder, date, time;  // Jussi Mäen transactions ikkunasta opeteltu/lainattu metodi erotella aika
        QStringList splittedDateTime;
        latestlogdata=json_obj["log"].toString();
        amount = QString::number(json_obj["amount"].toInt());
        timeholder = json_obj["log_time"].toString();
        splittedDateTime = timeholder.split("T");
        date = splittedDateTime[0];
        timeholder = splittedDateTime[1].split(".")[0];
        time = timeholder;
        ui->label_logs->setText(latestlogdata);
        ui->label_amount1->setText("-"+amount+"€");
        ui->label_date->setText(date);
        ui->label_timestamp_2->setText(time);
        ui->label_cardnum->setText(cardnumber);
        if(savings>0 && latestlogdata==test){  // Aiemmin haettu savingsmoden arvon tarkistus, jos edellinen tapahtuma ollut "debit withdraw", täytyy hakea savelogi
            getsavelog();
        }
}

void ReceiptWindow::getsavingsSlot(QNetworkReply *reply)  // TALLENTAA SAADUN SAVINGS ARVON INT ARVOON
{
    savings_data=reply->readAll();
    qDebug()<<"Savings data : "+savings_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(savings_data);
        QJsonObject json_obj = json_doc.object();
        savings=json_obj["savingsmode"].toInt();
        qDebug()<<"Savingsmode arvo tilillä on  " <<savings;
}

void ReceiptWindow::getsavelogSlot(QNetworkReply *reply)
{
    savelog_data=reply->readAll();
    qDebug()<<"Viimesin loki : "+savelog_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(savelog_data);
        QJsonObject json_obj = json_doc.object();
        QString amount;
        amount = QString::number(json_obj["amount"].toInt());
        qDebug()<<"Viimeisin savelog summa on  " <<amount;
        ui->label_savelogs->setText("Sent to savings");
        ui->label_amount_save->setText("-"+amount+"€");
}

void ReceiptWindow::timer10sekslot()
{
time10++;
if(time10>10){
    timer10sek->stop();
    emit backtomainmenu();
    this->close();
}
}

void ReceiptWindow::on_btn_logout_clicked()
{
    timer10sek->stop();
    emit logoutsignal();
    // ei tarvi this->close kun tuhoutuu enivei, aiheuttaa kaatumisen
}


void ReceiptWindow::on_btn_back_clicked()
{
    emit resettimer30();
    timer10sek->stop();
    emit backtomainmenu();
    this->close();
}
