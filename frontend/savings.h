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

private slots:
    void on_btn_savingsOn_clicked();

    void on_btn_savingsOff_clicked();

    void logsSlots(QNetworkReply *reply);

    void timer10Slot();

signals:
    void backtomainmenu();
    void resettimer30();

private:
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
