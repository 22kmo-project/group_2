#include "session.h"
#include <QDebug>
#include <QObject>

session::session()    // KONSTRUKTORI
{
 loginwindow = new MainWindow;
 loginwindow->show();
 connect(loginwindow,SIGNAL(login(QString,QString)),this,SLOT(loginsuccesfulSlot(QString,QString)));
 session30timer=new QTimer;
 connect(session30timer,SIGNAL(timeout()), this, SLOT(timer30slot()));
}

void session::getidcard()                   // HAKEE ID_CARDIN CARDNUMBERIN PERUSTEELLA,
{                                         // VASTAUS TULEE SLOTTIIN getCardIDSlot()
   session30timer->start(1000);
    QString site_url="http://localhost:3000/card/cid";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+sessiontoken.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getsessioncardmanager = new QNetworkAccessManager(this);  // toiminnoille jokaiselle oma manageri (?)

    QJsonObject jsonObj;  // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("cardnumber",sessioncardnumber);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");  // requestin headeri, tarvitsee jotta url encoded muoto kuten loginissa
                                                                                // tarvitseeko olla juuri application/json, miksi ?
    connect(getsessioncardmanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getCardIDSlot(QNetworkReply*)));

    reply = getsessioncardmanager->post(request, QJsonDocument(jsonObj).toJson());
}

void session::getandcheckcredit()                   // HAKEE KORTIN CREDITIN ID_CARD PERUSTEELLA
{                                                       // VASTAUS TULEE SLOTTIIN getCreditSlot();
    QString site_url="http://localhost:3000/card/cred";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+sessiontoken.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    getcreditmanager = new QNetworkAccessManager(this);  // Olion luonti, muista poistaa (?)
    QJsonObject jsonObj;                                // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("id_card",id_card);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");  // requestin headeri, tarvitsee jotta url encoded muoto kuten loginissa

    connect(getcreditmanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getCreditSlot(QNetworkReply*)));    // KYTKEE VASTAUSSIGNAALIN VASTAUSSLOTTIIN
                                                                                                          // VASTAUSSIGNAALI SISÄLTÄÄ DATAN (*REPLY)
    reply = getcreditmanager->post(request, QJsonDocument(jsonObj).toJson());
}

void session::logout()
{
    loginwindow->cleartextsanddata();
    loginwindow->show();
    id_card=0;
    if (credit==0){
        mainmenu->cleardata();
        mainmenu->close();
    }
    if (credit > 0){
        creditmenu->cleardata();
        creditmenu->close();
    }
    credit=0;
}


void session::getCardIDSlot(QNetworkReply *reply)   // ID CARDIN SAANTI SESSIONILLE
{                                                   // KUTSUU CREDIT TIEDONHAKUFUNKTION
     cardresponse_data=reply->readAll();
     qDebug()<<"DATA : "+cardresponse_data;

     QJsonDocument json_doc = QJsonDocument::fromJson(cardresponse_data);
         QJsonObject json_obj = json_doc.object();    // Tätä menetelmää voi käyttää kun vastauksena on 1 objekti
         QString id_carddata;                           // Jos vastaus on array (esim logs), käytä QBYTEARRAY
         id_carddata=QString::number(json_obj["id_card"].toInt());
         id_card=id_carddata.toInt();  // Muoto jolla saa vastausdatasta tallennettua tämän olion int muuttujaan arvon
         qDebug()<<"Id card intti on = " <<id_card;


         getsessioncardmanager->deleteLater();   // POISTA KERTAKÄYTTÖ ACCESS OLIO (?)

         getandcheckcredit();   // KUTSU HETI UUTTA POST FUNKTIOTA CREDITIN SAAMISEKSI
}

void session::getCreditSlot(QNetworkReply *reply)   // VASTAANOTTAA CREDITIN, PÄÄTTÄÄ KUMPI
                                                    // MAINMENU AUKEAA JA AVAA
{
    creditresponse_data=reply->readAll();
    qDebug()<<"DATA : "+creditresponse_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(creditresponse_data);
        QJsonObject json_obj = json_doc.object();
        QString creditdata;
        creditdata=QString::number(json_obj["credit"].toInt());
        credit=creditdata.toInt();  /// !!!!!!!!!!!!!!!!!!!!
        qDebug()<<"Creditti inttinä on = " <<credit;
        reply->deleteLater();
        getcreditmanager->deleteLater();

        if(credit == 0){
            mainmenu = new MainMenu(sessiontoken, id_card);  // DEBIT MAIN MENU, VÄLITÄ NÄMÄ SAMAT TIEDOT AINA KUN AVAAT IKKUNAOLION
            mainmenu->show();
            connect(mainmenu,SIGNAL(nextwindow(int)),this,SLOT(nextWindowSlot(int)));
            connect(mainmenu,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
            connect(mainmenu,SIGNAL(timer10isup()),this,SLOT(backtomainmenu()));// IKKUNA AVATESSA AINA SIGNAALI KYTKETTÄVÄ
        }                                                                          // MUUTA VAIN "mainmenu" OMAN IKKUNAN NIMEKSI ja nimeä signaalisi "resettimer30()"
        if(credit > 0) {
            creditmenu = new MainMenuCredit(sessiontoken, id_card);  // DEBIT CREDIT MAIN MENU, VÄLITÄ NÄMÄ SAMAT TIEDOT AINA KUN AVAAT IKKUNAOLION
            creditmenu->show();

            // TÄNNE TULEE SAMAT IKKUNANAVAUS KYTKENN*T JA VÄLITYKSET
        }

}

void session::loginsuccesfulSlot(QString cn, QString t)
{
    sessioncardnumber=cn;
    sessiontoken=t;
    getidcard();
}

void session::nextWindowSlot(int i)
{
 switch(i){
 case 1:
    // debitikkunaauki
     break;
 case 2:
     transactions=new Transactions(sessiontoken,id_card);
     connect(transactions,SIGNAL(backtomainmenu()),this,SLOT(backtomainmenu()));
     transactions->show();
     break;
case 3:
     saving=new savings(sessiontoken,id_card);
     connect(saving,SIGNAL(backtomainmenu()),this,SLOT(backtomainmenu()));
     connect(saving,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
     saving->show();


}
}



void session::resettimerslot()    // Signaalislot johon valikko-olioiden resetsignaali kytketään
{
 timer30=0;
}

void session::timer30slot()     // perus QTimerin signaalislotti
{
    timer30++;
    qDebug()<<"Session time is " << timer30;

    if(timer30>15){
            logout();
            session30timer->stop();
            timer30=0;
            sessiontoken="";
            qDebug()<< "sessiontoken on nyt " + sessiontoken;
    }

    // TEE ERILLINEN FUNKTIO JOLLA 30SEK TÄYTTYESSÄ/LOGOUT PAINAESSA ISTUNTO TIETOINEEN NOLLATAAN
    // KUTSU TÄSSÄ 30SEK TÄYTYTTYÄ KYSEISTÄ FUNKTIOTA
}

void session::backtomainmenu()   // 10 sek päättymisen signaalislotti, avaa cred perusteella oikean mainmenun
{
    if(credit==0){
        mainmenu->show();
    }
    if(credit>0){
        creditmenu->show();
    }
}
