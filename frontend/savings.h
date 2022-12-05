#ifndef SAVINGS_H
#define SAVINGS_H

#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>

namespace Ui {
class savings;
}

class savings : public QWidget
{
    Q_OBJECT

public:
    explicit savings(QString, int, QWidget *parent = nullptr);
    ~savings();
    //double amountPercage; //säästöön prosentteina
    QString savingsUpdate;
    QString savingsOff;

private slots:


    void on_btn_savingsOff_clicked();

    void logsSlots(QNetworkReply *reply);

    void timer10Slot();

    void on_btn_logout_clicked();

    void savingsSlot(QNetworkReply *reply);

    void on_btn_save_savings_clicked();

signals:
    void backtomainmenu();


private:
    void postsavings();
    Ui::savings *ui;
    QTimer * timer10sek = new QTimer;
    QString token;
    int id_card;
    int time10=0;

    QNetworkAccessManager *savingsManager; //!!!

    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // SAVINGS_H
