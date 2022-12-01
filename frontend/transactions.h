#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
#include <QTableWidget>
#include <QVBoxLayout>

namespace Ui {
class Transactions;
}

class Transactions : public QDialog
{
    Q_OBJECT

public:
    explicit Transactions(QString, int, QWidget *parent = nullptr);
    ~Transactions();

private slots:
    void on_btn_Back_clicked();

    void on_btn_LogOut_clicked();

    void logsSlots(QNetworkReply *reply);

    void timer10Slot();

signals:
    void backtomainmenu();

private:
    void getTransactions();
    void setTransactionsView();
    QTimer * timer10sek = new QTimer;

    void TokenEditor(QJsonDocument);
    QTableWidget *ui_userTokens;
    Ui::Transactions *ui;
    QString token;
    int id_card;
    int time10=0;

    QNetworkAccessManager *logsManager;
    QNetworkReply *reply;
    QByteArray response_data;

};

#endif // TRANSACTIONS_H
