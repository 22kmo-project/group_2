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

    savingsUpdate =ui->lineEdit_savingsOn->text();

    int savings=savingsUpdate.toInt();

    if  (savings <1 || savings >10){

        ui->label_savingsresponse->setText("Give number between 1-10");
    }

    else {

        QJsonObject jsonObj;
        jsonObj.insert("id_card",id_card);
        jsonObj.insert("savings",savings);


        QString site_url = "http://localhost:3000/account/savingsmode";
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

    updateSavings =json_obj["affectedRows"].toInt();

    if (updateSavings >0){
        qDebug()<<"Updated successfully: " <<updateSavings;
        ui->label_savingsresponse->setText("Savings mode is updated succesfully! You can now log out. ");
    }

    if(updateSavings==0){
        ui->label_savingsresponse->setText("Could not update savingsmode");
    }


}

void savings::on_btn_savingsOff_clicked()
{
    ui->lineEdit_savingsOn->clear();
    QJsonObject jsonObj;
    jsonObj.insert("id_card",id_card);
    jsonObj.insert("savings",0);


    QString site_url = "http://localhost:3000/account/savingsmode";
    QNetworkRequest request((site_url));

            //webtoken alku
    QByteArray myToken = "Bearer "+token.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"), (myToken));
            //webtoken loppu

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    updateSavingsManager = new QNetworkAccessManager(this);

    connect(updateSavingsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(savingsOffSlot(QNetworkReply*)));
    reply = updateSavingsManager->post(request, QJsonDocument(jsonObj).toJson());

   ui->label_savingsOff->setText("Saving mode is updated to be 0%, now you can log out.");

}

void savings::savingsOffSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"Updated: "<<response_data;
    reply->deleteLater();
    updateSavingsManager->deleteLater();


}


void savings::on_btn_logout_clicked()
{
    emit logout();
}




void savings::on_btn_Back_clicked()
{
    timer10sek->stop();
    emit backtomainmenu();
    this->close();
}


