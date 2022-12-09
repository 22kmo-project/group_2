#ifndef MAINMENUCREDIT_H
#define MAINMENUCREDIT_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

/*  TÄMÄ OLIO TOIMII DEBIT/CREDIT KORTIN MAINMENUNA
  TÄMÄN OLION LUONNISTA PÄÄTTÄÄ SESSION OLIO
  OLENNAISET TOIMINNOT
 -Sisältää signaalin jolla nollataan Session-olion 30sek timeri
 -Sisältää signaalin jolla aktivoidaan Session-olion logout() toiminto.
 -Hakee käynnistyessään kortinomistajan etunimen tervehdykseen
 -Sisältää julkisen funktion jota Session olio voi kutsua
  ruudulla näkyvän ajan päivitykseen.
 -Sisältää nextwindow signaalin jonka mukana menee int-luku Session-oliolle,
  jolla on toiminto seuraavan ikkunaolion avaamiseen.
  Tekijä: Tero Rantanen
*/
namespace Ui {
class MainMenuCredit;
}

class MainMenuCredit : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenuCredit(QString,QString,int,QWidget *parent = nullptr);
    ~MainMenuCredit();
    void resetAllTimers();

    void updateTimeUi(int);

signals:
    void resettimer30();
    void nextwindow(int);
    void logout();

private:
    Ui::MainMenuCredit *ui;
    int id_card;
    QString token;

    QNetworkAccessManager * getfnamemanager;
    QByteArray fname_data;
    QNetworkReply * reply;

private slots:
    void on_btn_debit_withdraw_clicked();


    void on_btn_logs_clicked();
    void on_btn_logout_clicked();
    void getfnameSlot(QNetworkReply *reply);
    void on_btn_debit_settings_clicked();
    void on_btn_debit_balance_clicked();
    void on_btn_credit_withdraw_clicked();
};

#endif // MAINMENUCREDIT_H
