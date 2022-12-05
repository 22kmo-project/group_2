#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainmenu.h>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

/* TÄMÄ OLIO TOIMII LOGINWINDOWINA, TÄMÄN OLION LUO SESSION OLIO
 OLENNAISIA TOIMINTOJA:
 Onnistunut login lähettää signaalin jonka mukana QStringit "cardnumber" ja "token"
 Session olio käsittelee nämä tiedot
 Tätä oliota EI TUHOTA, tämä piilotetaan this->hide() komennolla
 Uloskirjautuessa ajetaan funktio joka ylikirjoittaa kaiken tallennetun tiedon,
 ikkuna palautetaan näkyviin ja ollaan valmiita vastaanottamaan uusi login.
    Tekijä: Tero Rantanen */

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int id_card;
    QString cardnumber;
    QString password;
    QString token;
    void cleartextsanddata();  // resettaa tallennetun datan
signals:
    void reset30timer();
    void login(QString,QString);

private slots:
    void on_btn_login_clicked();
    void loginSlot (QNetworkReply *reply);   // loginiin

private:
    Ui::MainWindow *ui;

    MainMenu * mainmenu;
    QNetworkAccessManager * loginManager;// loginia varten
    QNetworkAccessManager * pingmanager;
    QNetworkReply *reply;
    QByteArray response_data;

};
#endif // MAINWINDOW_H
