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

    QString savingsUpdate;
    //QString savingsOff;
    QString savingsmode;


private slots:


    void on_btn_savingsOff_clicked();

    void savingsOffSlot (QNetworkReply *reply);

    void timer10Slot();

    void getSavingsSlot(QNetworkReply *reply);

    void updateSavingsSlot(QNetworkReply *reply);

    void on_btn_save_savings_clicked();

    void on_btn_Back_clicked();

    void on_btn_logout_clicked();

signals:
    void backtomainmenu();
    void logout();


private:

    Ui::savings *ui;
    QTimer * timer10sek = new QTimer;
    QString token;
    int saving;
    int id_card;
    int time10=0;


    QByteArray savingsmode_data;

    QByteArray savingsUpdate_data; //vai QString

    QNetworkAccessManager *getSavingsManager;

    QNetworkAccessManager *updateSavingsManager; //!!!

    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // SAVINGS_H
