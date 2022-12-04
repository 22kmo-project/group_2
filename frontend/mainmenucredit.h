#ifndef MAINMENUCREDIT_H
#define MAINMENUCREDIT_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class MainMenuCredit;
}

class MainMenuCredit : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenuCredit(QString,int,QWidget *parent = nullptr);
    ~MainMenuCredit();
    void resetAllTimers();
    void cleardata();
    void updateTimeUi(int);

signals:
    void resettimer30();
    void nextwindow(int);
    void logout();

private:
    Ui::MainMenuCredit *ui;
    int id_card;
    QString token;

    QNetworkAccessManager * getfnamemanager;
    QByteArray fname_data;
    QNetworkReply * reply;

private slots:
    void on_btn_debit_withdraw_clicked();


    void on_btn_logs_clicked();
    void on_btn_logout_clicked();
    void getfnameSlot(QNetworkReply *reply);
    void on_btn_debit_settings_clicked();
    void on_btn_debit_balance_clicked();
};

#endif // MAINMENUCREDIT_H
