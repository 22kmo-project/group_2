#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QDebug>

MainMenu::MainMenu(QString t,int idcard, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    token = t;
    ui->label_tokendemo->setText(token);  // POISTA MYÖHEMMIN TÄSSÄ NÄKYY TOKEN
    id_card = idcard;
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::getDataSlot(QNetworkReply *reply)
{

}

void MainMenu::on_btn_Cardidhaku_clicked()
{
    emit resettimer30();
}

void MainMenu::timer10slot()
{
    sessiontime10++;
    if (sessiontime10){
        //emit timer10isup();
    }
}

void MainMenu::on_transactions_Button_clicked() //Lisää Mainiin
{
    //connect(mainmenu,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
    //connect(mainmenu,SIGNAL(timer10isup()),this,SLOT(backtomainmenu()));// IKKUNA AVATESSA AINA SIGNAALI KYTKETTÄVÄ
    transactions = new Transactions(token, id_card);
    transactions->show();
}

