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




class session : public QObject
{
    Q_OBJECT
public:
    session();
    ~session();// TÄMÄ OLIO SAA LOGINWINDOWILTA (MAINWINDOW)
    void getidcard();               // QSTRING TOKENIN JA QSTRING CARDNUMBERIN
    void getandcheckcredit();       // HAKEE NIILLÄ VÄLITTÖMÄSTI ID_CARD JA CREDIT TIEDOT
    void createWindows();  // Luo kaikki mainmenun jälkeiset ikkunat, laita tänne "ikkunannimi" = new "ikkunasi"
    void deleteWindows(); // Poistaa kaikki em. ikkunat, laita tänne delete "ikkunannimi"
private:
    QString sessiontoken;           // MÄÄRITÄ jokainen ikkuna olio ottamaan vastaan QString ja int
    QString sessioncardnumber;      // VÄLITÄ aina luodessa sessiontoken ja id_card
    int id_card;                    // TALLENNA olion omiin muuttujiin ja käytä CRUD toiminnoissa
    int credit;
    int timer30=0;
    void logout();   // ISTUNNON POISTO
    void setFontsToUI();


    // -------NETWORK POINTTERIT JA MUUTTUJAT
    QNetworkAccessManager * getsessioncardmanager; // sessionin id card hakua varten
    QNetworkAccessManager * getcreditmanager;     // toiminnoilla EHKÄ kaikilla oltava oma accesmanager
    QByteArray creditresponse_data;        // en tiedä tarviiko response data aina oman Arrayn
    QByteArray cardresponse_data;           // en tiedä tarviiko response data aina oman Arrayn
    QNetworkReply *reply;                   // sama reply toiminut tähänmennessä eri toimintojen välillä
   // -------IKKUNOITTEN POINTTERIT-------------
    MainMenu * mainmenu;
    MainMenuCredit * creditmenu;
    MainWindow * loginwindow;
    Transactions * transactions;
    savings * saving;
    DebitWindow * debitwindow;
    Debitbalance * debitbalance;
    // -------AJASTIMET--------------
    QTimer * session30timer;
signals:

private slots:
   // ----SLOTIT JOIHIN TULEE SIGNAALI/VASTAUS QNETWORKACCESSMANAGEREILTA-----
    void getCardIDSlot (QNetworkReply *reply); // KUTSUU getandcheckcredit() saatuaan id_card
    void getCreditSlot (QNetworkReply *reply);  // SAA credit tiedon ja LUO OIKEAN MENU OLION (Debit tai Debit/credit)

    void loginsuccesfulSlot(QString,QString);
    void logoutslot();  // mainmenujen logoutsignaalille



    void nextWindowSlot(int);  // SISÄLTÄÄ SWITCH CASEN JOSTA MAINMENU AUKOO SEURAAVAA IKKUNAA, PÄÄTÄ IKKUNALLE UNIIKKI NRO JÄRJESTYKSESSÄ
    // JA SLOTISSA ON FUNKTIO JOLLA KYSEISEN MENUN KONSTRUKTORI KUTSUTAAN JA CONNECTIT TEHDÄÄN

    // -----TIMER SLOTIT-----
    void resettimerslot();   // Tähän kytketään muilta ikkunoilta signaali jolla 30sek ajastin nollataan aina nappia painettaessa
    void timer30slot();       // Normaali QTimerin slotti 30sek timeria varten, tänne toiminto kun 30sek tulee täyteen
    void backtomainmenu();  // KUN IKKUNAN 10 SEK AJASTIN LOPPUU



};

#endif // SESSION_H
