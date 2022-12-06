#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainmenu.h>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int id_card;
    QString cardnumber;
    QString password;
    QString token;
    void cleartextsanddata();
    void pingServer();
signals:
    void reset30timer();
    void login(QString,QString);

private slots:
    void on_btn_login_clicked();
    void loginSlot (QNetworkReply *reply);   // loginiin
    void pingSlot(QNetworkReply * reply);  // pingiin
private:
    Ui::MainWindow *ui;

    MainMenu * mainmenu;
    QNetworkAccessManager * loginManager;// loginia varten
    QNetworkAccessManager * pingmanager;
    QNetworkReply *reply;
    QByteArray response_data;

};
#endif // MAINWINDOW_H
