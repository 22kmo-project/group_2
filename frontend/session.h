#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
#include <QFont>
// ---SESSION TÄYTYY INCLUDE JOKAINEN IKKUNA.H
#include "mainmenu.h"
#include "mainmenucredit.h"
#include "mainwindow.h"
#include "transactions.h"
#include "savings.h"
#include "debitwindow.h"
#include "debitbalance.h"
#include "receiptwindow.h"
#include "askforreceipt.h"

/*  TÄMÄ OLIO TOIMII MOOTTORINA/LOGIIKKANA IKKUNAOLIOITTEN VÄLILLÄ
    TÄTÄ OLIOTA EI TUHOTA OHJELMAN AJON AIKANA,
    TÄMÄ OLIO LUO JA TUHOAA ISTUNTOJEN VÄLISSÄ IKKUNAOLIOITA
    TÄMÄ OLIO PITÄÄ TALLESSA TIEDOT JOITA TULEE VÄLITTÄÄ IKKUNOILLE
    JA YLIKIRJOITTAA TALLENNETUT TIEDOT ISTUNNON PÄÄTTYESSÄ
    OLION TOIMINTA VAIHEINA:
 1. Olion konstruktori luo ja avaa Loginwindow (mainwindow.h)
    -Loginwindow palauttaa loginin onnistuessa signaalilla QStringit
     cardnumber ja token, token tallennetaan muita ikkunoita varten,
     cardnumberilla haetaan id_card jota muut ikkunat käyttävät database
     kommunikointiin.
 2.  Id_cardin saatua haetaan myös heti kortinomistajan tiedot ja kortin credit arvo,
        jonka perusteella tiedetään onko kortti debit vai debit/credit
        ja avataan oikea mainmenu.
        Kaikki muutkin istunnon ikkunaoliot luodaan, muttei tuoda esiin.
        Avattavat mainmenun signaalit kytketään luonnin yhteydessä.
 3.   Mainmenuilta vastaanotetaan signaaleilla joko nextwindow tai logout
        toimintoon signaali. Nextwindowssa on switch case joka ennaltasovittujen
        int arvojen perusteella avaa seuraavan ikkunan ja kytkee
        tarpeelliset signaalit. Samalla kutsutaan kyseisen ikkunan 10sek timerin käynnistysfunktio.
        Logout toiminnon signaalin vastaanottaessa tuhotaan kaikki ikkunaoliot
        ja luotu mainmenu. Loginikkunan tiedot ylikirjoitetaan ja se kutsutaan esiin.
        Myös tämän olion tallennetut tiedot ylikirjoitetaan.
        Tekijä: Tero Rantanen
*/
class session : public QObject
{
    Q_OBJECT
public:
    session();
    ~session();                     // TÄMÄ OLIO SAA LOGINWINDOWILTA (MAINWINDOW)
    void getidcard();               // QSTRING TOKENIN JA QSTRING CARDNUMBERIN
    void getandcheckcredit();       // HAKEE NIILLÄ VÄLITTÖMÄSTI ID_CARD JA CREDIT TIEDOT
    void createWindows();           // Luo kaikki mainmenun jälkeiset ikkunat, laita tänne "ikkunannimi" = new "ikkunasi"
    void deleteWindows();           // Poistaa kaikki em. ikkunat, laita tänne delete "ikkunannimi"
private:
    QString sessiontoken;           // MÄÄRITÄ jokainen ikkuna olio ottamaan vastaan QString ja int
    QString sessioncardnumber;      // VÄLITÄ aina luodessa ainakin sessiontoken ja id_card
    int id_card;                    // TALLENNA olion omiin muuttujiin ja käytä CRUD toiminnoissa
    int credit;
    int timer30=0;
    void logout();                  // ISTUNNON WIPE
    QString fname, lname, address, email, phonenumber;  // omistajan datan tallennuslohkot
    void getOwnerData();

    // -------NETWORK POINTTERIT JA MUUTTUJAT
    QNetworkAccessManager * getsessioncardmanager; // sessionin id card hakua varten
    QNetworkAccessManager * getcreditmanager;  // creditin haulle manageri.
    QNetworkAccessManager * getownerdatamanager; // omistajan datan haun manageri
    QByteArray creditresponse_data;
    QByteArray cardresponse_data;
    QByteArray ownerresponse_data;
    QNetworkReply *reply;
   // -------IKKUNOITTEN POINTTERIT-------------
    MainMenu * mainmenu;
    MainMenuCredit * creditmenu;
    MainWindow * loginwindow;
    Transactions * transactions;
    savings * saving;
    DebitWindow * debitwindow;
    Debitbalance * debitbalance;
    ReceiptWindow * receiptwindow;
    AskForReceipt * askforreceipt;
    // -------AJASTIMET--------------
    QTimer * session30timer;
signals:

private slots:
   // ----SLOTIT JOIHIN TULEE SIGNAALI/VASTAUS QNETWORKACCESSMANAGEREILTA-----
    void getCardIDSlot (QNetworkReply *reply); // KUTSUU getandcheckcredit() saatuaan id_card
    void getCreditSlot (QNetworkReply *reply);  // SAA credit tiedon ja LUO OIKEAN MENU OLION (Debit tai Debit/credit)
    void getownerDataSlot(QNetworkReply * reply); // saa ownerin tiedot
    // ----SLOTIT JOIHIN TULEE SIGNAALIT IKKUNAOLIOILTA---------
    void loginsuccesfulSlot(QString,QString); // loginwindow lähettää signaalin joka käynnistää id_card ja credithakuketjun
    void logoutslot();                          // mainmenujen logoutsignaalille
    void nextWindowSlot(int);  // SISÄLTÄÄ SWITCH CASEN JOSTA MAINMENU AUKOO SEURAAVAA IKKUNAA, PÄÄTÄ IKKUNALLE UNIIKKI NRO JÄRJESTYKSESSÄ
                                // JA SLOTISSA ON FUNKTIO JOLLA KYSEISEN MENUN KONSTRUKTORI KUTSUTAAN JA CONNECTIT TEHDÄÄN
    // -----TIMER SLOTIT-----
    void resettimerslot();   // Tähän kytketään muilta ikkunoilta signaali jolla 30sek ajastin nollataan aina nappia painettaessa
    void timer30slot();       // Normaali QTimerin slotti 30sek timeria varten, tänne toiminto kun 30sek tulee täyteen
    void backtomainmenu();   // KUN IKKUNAN OMA 10 SEK AJASTIN LOPPUU



};

#endif // SESSION_H
