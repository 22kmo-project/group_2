#include "savings.h"
#include "ui_savings.h"
#include <QDebug>
#include <QByteArray>

savings::savings(QString givenToken, int idcard, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::savings)
{

    timer10sek->start(1000);
    ui->setupUi(this);
    token = givenToken;
    id_card = idcard;
    updateSavings();

    //hakee nykyisen savings moden
    QString site_url="http://localhost:3000/account/savingsmode/"+QString::number(id_card);
    QNetworkRequest request((site_url));
       //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
       //WEBTOKEN LOPPU
    getSavingsManager = new QNetworkAccessManager(this);

    connect(getSavingsManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getSavingsSlot(QNetworkReply*)));
    reply = getSavingsManager->get(request);
}

savings::~savings()
{
    delete ui;
}

void savings::getSavingsSlot(QNetworkReply *reply)
{
    savingsmode_data=reply->readAll();
    qDebug()<<"Data : "+savingsmode_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(savingsmode_data);
    QJsonObject json_obj = json_doc.object();
    QString savingsmode;
    saving =json_obj["savingsmode"].toInt();
    qDebug()<<"Current savings mode is:  " <<saving;
    ui->label_savingsmode_info->setText("Current savings mode is: "+QString::number(saving)+"%");
}


void savings::on_btn_save_savings_clicked()
{
    savingsUpdate = ui->lineEdit_savingsOn->text();

}



void savings::on_btn_savingsOff_clicked()
{


}


void savings::updateSavings()
{
    /*
     QString site_url = "http://localhost:3000/account/savingsmode" + QString::number(id_card);  //!!!
     QNetworkRequest request((site_url));

     //webtoken alku
     QByteArray myToken = "Bearer "+token.toLocal8Bit();
     request.setRawHeader(QByteArray("Authorization"), (myToken));
     //webtoken loppu

     savingsManager = new QNetworkAccessManager(this);
     connect(savingsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(savingsSlot(QNetworkReply*)));
     //reply = savingsManager->post(request);

 */



}

void savings::updateSavingsSlot(QNetworkReply *reply)
{

}




void savings::on_btn_logout_clicked()
{
    qDebug()<<"logout";
}




void savings::on_btn_Back_clicked()
{
    //emit resettimer30();
    timer10sek->stop();
    emit backtomainmenu();
    this->close();
}

void savings::timer10Slot()
{
    time10++;
    if (time10>10){
        timer10sek->stop();
        emit backtomainmenu();
        this->close();
    }
}
