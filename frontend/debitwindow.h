#ifndef DEBITWINDOW_H
#define DEBITWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
#include "debitamountwindow.h"

namespace Ui {
class DebitWindow;
}

class DebitWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebitWindow(QString, int,QWidget *parent = nullptr);
    ~DebitWindow();

    void resetAllTimers();
    void getbalance();
    void getowner();
    void withdraw(int amount);
    void startwindowtimer();
    void resets();

private slots:
    void on_btn20_clicked();
    void on_btn40_clicked();
    void on_btn60_clicked();
    void on_btn100_clicked();
    void on_btn200_clicked();
    void on_btn500_clicked();
    void on_btnBack_clicked();
    void on_pushButton_clicked();
    void on_btnOther_clicked();
    void timer10Slot();
    void getOwnerInfoSlot(QNetworkReply *reply);
    void getBalanceSlot(QNetworkReply *reply);
    void debitWithdrawSlot(QNetworkReply* reply);
    void customAmount(int);
    void showUI();


signals:
    void resettimer30();
    void backtomainmenu();
    void nextwindow(int);

private:
    Ui::DebitWindow *ui;
    QTimer * timer10sek = new QTimer;
    QString token;
    int account_balance;
    int id_card;
    int time10=0;
    void debitwithdraw(int);

    QNetworkAccessManager *getOwnerInfoManager;
    QByteArray owner_data;
    QNetworkAccessManager *getBalanceManager;
    QByteArray account_balance_data;
    QNetworkAccessManager *debitWithdrawManager;
    QByteArray debit_withdraw_data;
    QNetworkReply *reply;
    DebitAmountWindow *amountWindow;
};

#endif // DEBITWINDOW_H
