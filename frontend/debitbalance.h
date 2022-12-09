#ifndef DEBITBALANCE_H
#define DEBITBALANCE_H

#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
#include <QTableWidget>

namespace Ui {
class Debitbalance;
}

class Debitbalance : public QWidget
{
    Q_OBJECT

public:
    explicit Debitbalance(QString, int, int, QWidget *parent = nullptr);
    ~Debitbalance();
    void startwindowtimer();

private slots:
    void getdebitbalanceSlot(QNetworkReply *reply);
    void getcreditbalanceSlot(QNetworkReply *reply);
    void timer10Slot();


    void on_btn_Back_clicked();

signals:
    void backtomainmenu();
    void resettimer30();

private:
    Ui::Debitbalance *ui;
    QTimer * timer10sek = new QTimer;
    QString token;
    int credit;
    int account_balance;
    int id_card;
    int time10=0;
    QNetworkAccessManager * getdebitbalancemanager;
    QByteArray debitbalance_data;
    QByteArray creditbalance_data;
    QNetworkReply * reply;


};

#endif // DEBITBALANCE_H
