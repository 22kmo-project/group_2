#ifndef RECEIPTWINDOW_H
#define RECEIPTWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
/* TÄMÄ IKKUNAOLIO TARKISTAA VIIMEISIMMÄN LOKITAPAHTUMAN JA KORTIN SAVINGSMODEN
 * Jos Savingsmode on aktiivinen, ja viimeisin tapahtuma on ollut debit withdraw
   Haetaan myös viimeisin logi joka kirjoitettu savingsmoden kanssa.
 * Hakee logeista viimeisimmän nostotyypin credit withdraw, debit withdraw tai debit deposit
   ja antaa siitä tapahtumatekstin ja summan.
   Tehnyt: Tero Rantanen
*/
namespace Ui {
class ReceiptWindow;
}

class ReceiptWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReceiptWindow(QString, QString, int,QWidget *parent = nullptr);
    ~ReceiptWindow();
    void getLatestLog();
    void getsavingsmode();
    void getsavelog();
    void startwindowtimer();

signals:
    void backtomainmenu();
    void logoutsignal();
    void resettimer30();
private:
    QTimer * timer10sek;
    Ui::ReceiptWindow *ui;
    QNetworkAccessManager * getlatestlogmanager;
    QNetworkAccessManager * getsavingsmanager;
    QNetworkAccessManager * getsavelogmanager;
    QByteArray latest_data;
    QByteArray savings_data;
    QByteArray savelog_data;
    QNetworkReply * reply;
    int id_card;
    int time10=0;
    QString token;
    int savings;
    QString cardnumber;

private slots:
    void getlatestlogSlot(QNetworkReply * reply);
    void getsavingsSlot(QNetworkReply * reply);
    void getsavelogSlot(QNetworkReply * reply);
    void timer10sekslot();

    void on_btn_logout_clicked();
    void on_btn_back_clicked();
};

#endif // RECEIPTWINDOW_H
