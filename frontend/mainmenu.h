#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "transactions.h" //Lisää mainiin

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QString, int, QWidget *parent = nullptr);
    ~MainMenu();
    void getData();
    int id_card;

signals:
    void resettimer30();

private:
    int sessiontime10;

    Ui::MainMenu *ui;
    QString token;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
    Transactions *transactions;  //Lisää Mainiin

private slots:
    void getDataSlot (QNetworkReply *reply);
    void timer10slot();
    void on_btn_Cardidhaku_clicked();
    void on_transactions_Button_clicked(); //Lisää Mainiin
};

#endif // MAINMENU_H
