#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

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

private:
    void getTransactions();
    void setTransactionsView();

    Ui::Transactions *ui;
    QString token;
    int id_card;

    QNetworkAccessManager *logsManager;
    QNetworkReply *reply;
    QByteArray response_data;

};

#endif // TRANSACTIONS_H
