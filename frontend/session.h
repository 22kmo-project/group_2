#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
// ---SESSION TÄYTYY INCLUDE JOKAINEN IKKUNA.H
#include "mainmenu.h"
#include "mainmenucredit.h"


class session : public QObject
{
    Q_OBJECT
public:
    session(QString, QString);   // TÄMÄ OLIO SAA LOGINWINDOWILTA (MAINWINDOW)
    void getidcard();               // QSTRING TOKENIN JA QSTRING CARDNUMBERIN
    void getandcheckcredit();       // HAKEE NIILLÄ VÄLITTÖMÄSTI ID_CARD JA CREDIT TIEDOT

private:
    QString sessiontoken;           // MÄÄRITÄ jokainen ikkuna olio ottamaan vastaan QString ja int
    QString sessioncardnumber;      // VÄLITÄ aina luodessa sessiontoken ja id_card
    int id_card;                    // TALLENNA olion omiin muuttujiin ja käytä CRUD toiminnoissa
    int credit;
    int timer30=0;
    int currentwindow=0;


    // -------NETWORK POINTTERIT JA MUUTTUJAT
    QNetworkAccessManager * getsessioncardmanager; // sessionin id card hakua varten
    QNetworkAccessManager * getcreditmanager;     // toiminnoilla EHKÄ kaikilla oltava oma accesmanager
    QByteArray creditresponse_data;        // en tiedä tarviiko response data aina oman Arrayn
    QByteArray cardresponse_data;           // en tiedä tarviiko response data aina oman Arrayn
    QNetworkReply *reply;                   // sama reply toiminut tähänmennessä eri toimintojen välillä
   // -------IKKUNOITTEN POINTTERIT-------------
    MainMenu * mainmenu;
    mainmenucredit * creditmenu;

    // -------AJASTIMET--------------
    QTimer * session30timer;
signals:
private slots:
   // ----SLOTIT JOIHIN TULEE SIGNAALI/VASTAUS QNETWORKACCESSMANAGEREILTA-----
    void getCardIDSlot (QNetworkReply *reply); // KUTSUU getandcheckcredit() saatuaan id_card
    void getCreditSlot (QNetworkReply *reply);  // SAA credit tiedon ja LUO OIKEAN MENU OLION (Debit tai Debit/credit)

  // TÄNNE SLOTTIFUNKTIO AINA JOKA IKKUNALLE, KUN MAINMENUSTA VALITAAN ESIM DEBIT NOSTO
    // TÄÄLLÄ ON "opendebitmenu()" TYYPPINEN SLOTTI JOHON MAINMENU VÄLITTÄÄ SEN SIGNAALIN
    // JA SLOTISSA ON FUNKTIO JOLLA KYSEISEN MENUN KONSTRUKTORI KUTSUTAAN

    // -----TIMER SLOTIT-----
    void resettimerslot();   // Tähän kytketään muilta ikkunoilta signaali jolla 30sek ajastin nollataan aina nappia painettaessa
    void timer30slot();       // Normaali QTimerin slotti 30sek timeria varten, tänne toiminto kun 30sek tulee täyteen
    void backtomainmenu();  // KUN IKKUNAN 10 SEK AJASTIN LOPPUU



};

#endif // SESSION_H
