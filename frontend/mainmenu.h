#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>


namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QString, int, QWidget *parent = nullptr);
    ~MainMenu();

    void resetAllTimers();
    void cleardata();
    void updateTimeUi(int);
    void setFonts();

signals:
    void resettimer30();
    void nextwindow(int);
    void logout();

private:
    Ui::MainMenu *ui;
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

#endif // MAINMENU_H
