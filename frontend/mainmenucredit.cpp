#include "mainmenucredit.h"
#include "ui_mainmenucredit.h"

mainmenucredit::mainmenucredit(QString t, int cid,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainmenucredit)
{
    ui->setupUi(this);
   token = t;
   id_card = cid;
}

mainmenucredit::~mainmenucredit()
{
    delete ui;
}

void mainmenucredit::on_transactions_Button_clicked()
{
    //connect(mainmenu,SIGNAL(resettimer30()),this,SLOT(resettimerslot()));
    //connect(mainmenu,SIGNAL(timer10isup()),this,SLOT(backtomainmenu()));// IKKUNA AVATESSA AINA SIGNAALI KYTKETTÄVÄ
    transactions = new Transactions(token, id_card);
    transactions->show();
}

