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
    ui->label_savingsmode_info->setText("Your current savings mode is: "+QString::number(saving)+"%");
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


void savings::on_btn_save_savings_clicked()
{
    //luetaan annettu nro, ja viedään tietokantaan ehtorakenteen kautta

    savingsUpdate = ui->lineEdit_savingsOn->text();
    if  (savingsUpdate <1 && savingsUpdate >10){

        ui->label_savingsresponse->setText("Give number between 1-10");
    }

    else {

        QJsonObject jsonObj;
        jsonObj.insert("savingsmode",savingsmode);

        QString site_url = "http://localhost:3000/account/savingsmode/" + QString::number(id_card);  //!!!
        QNetworkRequest request((site_url));

                //webtoken alku
        QByteArray myToken = "Bearer "+token.toLocal8Bit();
        request.setRawHeader(QByteArray("Authorization"), (myToken));
                //webtoken loppu


        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        updateSavingsManager = new QNetworkAccessManager(this);

        connect(updateSavingsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(updateSavingsSlot(QNetworkReply*)));
        reply = updateSavingsManager->post(request, QJsonDocument(jsonObj).toJson());
    }
}

void savings::updateSavingsSlot(QNetworkReply *reply)
{
    savingsUpdate_data=reply->readAll();

    QJsonDocument json_doc = QJsonDocument::fromJson(savingsUpdate_data);
    QJsonObject json_obj = json_doc.object();
    int updateSavings;

    updateSavings =json_obj["updateSavings"].toInt();
    //updateSavings =savingsUpdate_data.toInt();
    qDebug()<<"Updated savings mode is: " <<updateSavings;
    ui->label_savingsresponse->setText("Savings mode is updated succesfully! "); //+QString::number(updateSavings));

}

void savings::on_btn_savingsOff_clicked()
{/*

   //manageri?
    QJsonObject jsonObj;
    jsonObj.insert("savingsmode",savingsmode);

    QString site_url = "http://localhost:3000/account/savingsmode" + QString::number(id_card);  //!!!
    QNetworkRequest request((site_url));

            //webtoken alku
    QByteArray myToken = "Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"), (myToken));
            //webtoken loppu


    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    updateSavingsManager = new QNetworkAccessManager(this);

    connect(updateSavingsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(updateSavingsSlot(QNetworkReply*)));
    reply = updateSavingsManager->post(request, QJsonDocument(jsonObj).toJson());
*/
}



void savings::savingsOffSlot(QNetworkReply *reply)
{
   /* savingsUpdate_data=reply->readAll();

    QJsonDocument json_doc = QJsonDocument::fromJson(savingsUpdate_data);
    QJsonObject json_obj = json_doc.object();

    int savingsOff;
    savingsOff =json_obj["affectedRows"].toInt();
    qDebug()<<"Updated savings mode is: " <<savingsOff;*/
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


