#include "session.h"
#include <QDebug>
#include <QObject>

session::session()    // KONSTRUKTORI
{
 loginwindow = new MainWindow; // Loginikkunan luonti ja esiintuonti
 loginwindow->show();
 connect(loginwindow,SIGNAL(login(QString,QString)),this,SLOT(loginsuccesfulSlot(QString,QString)));
 session30timer=new QTimer;  // luodaan 30sek Qtimer olio
 connect(session30timer,SIGNAL(timeout()), this, SLOT(timer30slot()));
}

session::~session()
{
}

void session::getidcard()                   // HAKEE ID_CARDIN CARDNUMBERIN PERUSTEELLA,
{                                         // VASTAUS TULEE SLOTTIIN getCardIDSlot()
   session30timer->start(1000); // login on tehty, laitetaan idletimer käyntiin
    QString site_url="http://localhost:3000/card/cid";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+sessiontoken.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getsessioncardmanager = new QNetworkAccessManager(this);

    QJsonObject jsonObj;  // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("cardnumber",sessioncardnumber);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");  // requestin headeri, tarvitsee jotta url encoded muoto kuten loginissa
                                                                                // tarvitseeko olla juuri application/json, miksi ?
    connect(getsessioncardmanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getCardIDSlot(QNetworkReply*)));

    reply = getsessioncardmanager->post(request, QJsonDocument(jsonObj).toJson());
}

void session::getandcheckcredit()                   // HAKEE KORTIN CREDITIN ID_CARD PERUSTEELLA
{                                                       // VASTAUS TULEE SLOTTIIN getCreditSlot(); jonka jälkeen ikkunaoliot luodaan
    QString site_url="http://localhost:3000/card/cred";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+sessiontoken.toLocal8Bit();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    getcreditmanager = new QNetworkAccessManager(this);  // Olion luonti, muista poistaa
    QJsonObject jsonObj;                                // objekti jonka sisälle dbrequestiin lähtevä data
    jsonObj.insert("id_card",id_card);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");  // requestin headeri, tarvitsee jotta url encoded muoto kuten loginissa

    connect(getcreditmanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getCreditSlot(QNetworkReply*)));    // KYTKEE VASTAUSSIGNAALIN VASTAUSSLOTTIIN
                                                                                                          // VASTAUSSIGNAALI SISÄLTÄÄ DATAN (*REPLY)
    reply = getcreditmanager->post(request, QJsonDocument(jsonObj).toJson());
}

void session::createWindows()    // KAIKKIEN IKKUNAOLIOIDEN KONSTRUKTORIN KUTSU
{                                // LUO JA TUO ESILLE OIKEAN MAINMENUN KORTIN CRED PERUSTEELLA
    transactions = new Transactions(sessiontoken,id_card);
    saving = new savings(sessiontoken,id_card);
    debitwindow = new DebitWindow(sessiontoken,id_card);
    debitbalance = new Debitbalance(sessiontoken,id_card,credit);
    receiptwindow = new ReceiptWindow(sessiontoken,id_card);
    // ----------------TARKISTETAAN SAADUN CREDIT ARVON PERUSTEELLA KUMPI MAINMENU AVATAAN------------------------------------
    if(credit == 0){
        mainmenu = new MainMenu(sessiontoken, id_card);  // DEBIT MAIN MENU
        mainmenu->show();
        connect(mainmenu,SIGNAL(logout()),this,SLOT(logoutslot()));
        connect(mainmenu,SIGNAL(nextwindow(int)),this,SLOT(nextWindowSlot(int)));
        connect(mainmenu,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
    }
    if(credit > 0) {
        creditmenu = new MainMenuCredit(sessiontoken, id_card);  // DEBIT CREDIT MAIN MENU
        creditmenu->show();
        connect(creditmenu,SIGNAL(logout()),this,SLOT(logoutslot()));
        connect(creditmenu,SIGNAL(nextwindow(int)),this,SLOT(nextWindowSlot(int)));
        connect(creditmenu,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
    }
}

void session::deleteWindows()  // KAIKKIEN IKKUNAOLIOIDEN TUHOAMINEN
{
    delete transactions;           // LISÄÄ TÄNNE IKKUNASI DESTRUCTORIN KUTSU
    delete saving;
    delete debitwindow;
    delete debitbalance;
    if (credit==0){             // Tarkistaa ennen credit nollausta kumpi mainmenu on luotu sen perusteella
        mainmenu->close();        // ja kutsuu sen destruktorin. Sitten nollaa creditin.
        delete mainmenu;
    }
    if (credit > 0){
        creditmenu->close();
        delete creditmenu;
    }

    credit=0;
}

void session::logout()  // Ylikirjoittaa ja kutsuu kaikki tietojen ylikirjoitus ja olioiden tuhoamistoiminnot.
{
    session30timer->stop();
    timer30=0;
    sessiontoken="";
    loginwindow->cleartextsanddata();
    loginwindow->show();
    id_card=0;
    deleteWindows(); // POISTAA KAIKKI OLIOT
}




void session::getCardIDSlot(QNetworkReply *reply)   // ID CARDIN SAANTI SESSIONILLE
{                                                   // KUTSUU CREDIT TIEDONHAKUFUNKTION JOKA JATKAA IKKUNOIDEN LUOMISEEN
     cardresponse_data=reply->readAll();
     qDebug()<<"DATA : "+cardresponse_data;
     QJsonDocument json_doc = QJsonDocument::fromJson(cardresponse_data);
         QJsonObject json_obj = json_doc.object();    // Tätä menetelmää voi käyttää kun vastauksena on 1 objekti
         QString id_carddata;                           // Jos vastaus on array (esim logs), käytä QBYTEARRAY
         id_carddata=QString::number(json_obj["id_card"].toInt());
         id_card=id_carddata.toInt();  // Muoto jolla saa vastausdatasta tallennettua tämän olion int muuttujaan arvon
         qDebug()<<"Id card intti on = " <<id_card;
         getsessioncardmanager->deleteLater();   // POISTA KERTAKÄYTTÖ NETWORK OLIO
         getandcheckcredit();   // KUTSU HETI UUTTA FUNKTIOTA CREDITIN SAAMISEKSI
}

void session::getCreditSlot(QNetworkReply *reply)   // VASTAANOTTAA CREDITIN, KUTSUU IKKUNOIDENAVAUSFUNKTION
{
    creditresponse_data=reply->readAll();
    qDebug()<<"DATA : "+creditresponse_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(creditresponse_data);
        QJsonObject json_obj = json_doc.object();
        QString creditdata;
        creditdata=QString::number(json_obj["credit"].toInt());
        credit=creditdata.toInt();
        qDebug()<<"Creditti inttinä on = " <<credit;
        reply->deleteLater();
        getcreditmanager->deleteLater();
        createWindows();// LUO OIKEAN MAINMENUN JA KAIKKI IKKUNAOLIOT, OTETAAN TARPEEN MUKAAN ESILLE
}

void session::loginsuccesfulSlot(QString cn, QString t) // saadaan loginikkunalta cardnunber ja token, käynnistetään id_cardin haku
{                                                       // id_card hakufunktio käynnistää creditinhaun, joka kutsuu ikkunoidenluontifunktion
    sessioncardnumber=cn;
    sessiontoken=t;
    getidcard();
}

void session::logoutslot()  // logout signaali saatua kutsutaan logout funktio, jota myös ikkunan oma logout nappi käyttää.
{
    logout();
}



void session::nextWindowSlot(int i) // IKKUNOIDEN AVAAMISLOGIIKKA JA SIGNAALIEN KYTKENTÄ, TARPEELLISTEN CHILD FUNKTIOIDEN KUTSU
                                    // MUISTA KYTKEÄ SIGNAALIT BACKTOMAINMENU, RESETTIMER30 JA NEXTWINDOW
{
 switch(i){
 case 1:
     connect(debitwindow,SIGNAL(backtomainmenu()),this,SLOT(backtomainmenu()));
     connect(debitwindow,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
     connect(debitwindow,SIGNAL(nextwindow(int)),this,SLOT(nextWindowSlot(int)));
     debitwindow->startwindowtimer();
     debitwindow->getbalance();
     debitwindow->show();
     break;
 case 2:
     connect(transactions,SIGNAL(backtomainmenu()),this,SLOT(backtomainmenu()));
     connect(transactions,SIGNAL(resetTimer30()),this,SLOT(resettimerslot()));
     transactions->startwindowtimer();
     transactions->show();
     break;
 case 3:
     connect(saving,SIGNAL(backtomainmenu()),this,SLOT(backtomainmenu()));
     connect(saving,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
     saving->startwindowtimer();
     saving->show();
     break;
 case 4:
     connect(debitbalance,SIGNAL(backtomainmenu()),this,SLOT(backtomainmenu()));
     connect(debitbalance,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
     debitbalance->startwindowtimer();
     debitbalance->show();
     break;
 case 5:
     connect(receiptwindow,SIGNAL(backtomainmenu()),this,SLOT(backtomainmenu()));
     connect(receiptwindow,SIGNAL(logoutsignal()),this,SLOT(logoutslot()));
     connect(receiptwindow,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
     receiptwindow->getsavingsmode();
     receiptwindow->getLatestLog();
     receiptwindow->startwindowtimer();
     receiptwindow->show();
     break;
}
}



void session::resettimerslot()    // Signaalislot johon ikkunaolioiden resetsignaali kytketään, nappeja painaessa ajannollaus
{
 timer30=0;
}

void session::timer30slot()     // perus QTimerin signaalislotti istunnon 30sek idleajastimelle
{
    timer30++;
    qDebug()<<"Session time is " << timer30;
    if(credit==0){
        mainmenu->updateTimeUi(timer30);
    }
    if(credit>0){
        creditmenu->updateTimeUi(timer30);
    }

    if(timer30>29){
            logout();
            qDebug()<< "sessiontoken on nyt " + sessiontoken;
    }

}

void session::backtomainmenu()   // 10 sek päättymisen signaalislotti, palauttaa cred perusteella oikean mainmenun esiin
{
    if(credit==0){
        mainmenu->show();
    }
    if(credit>0){
        creditmenu->show();
    }
}




