#ifndef DEBITWINDOW_H
#define DEBITWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>

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

private slots:
    void on_btn20_clicked();
    void on_btn40_clicked();
    void on_btn60_clicked();
    void on_btn100_clicked();
    void on_btn200_clicked();
    void on_btn500_clicked();
    void on_btnBack_clicked();
    void timer10Slot();
    void getOwnerInfoSlot(QNetworkReply *reply);
    void getBalanceSlot(QNetworkReply *reply);



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

    QNetworkAccessManager *getOwnerInfoManager;
    QNetworkReply *reply;
    QByteArray owner_data;
    QNetworkAccessManager *getBalanceManager;
    QByteArray account_balance_data;
};

#endif // DEBITWINDOW_H
