#include "mainmenucredit.h"
#include "ui_mainmenucredit.h"

MainMenuCredit::MainMenuCredit(QString t, int idcard,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuCredit)
{
    token=t;
    id_card=idcard;
    ui->setupUi(this);
}

MainMenuCredit::~MainMenuCredit()
{
    delete ui;
}

void MainMenuCredit::resetAllTimers()
{
    emit resettimer30();
}

void MainMenuCredit::cleardata()
{
    id_card = 0;
    token = "";
}

void MainMenuCredit::on_btn_debit_withdraw_clicked()
{
    resetAllTimers();
    emit nextwindow(1);
    this->hide();
}

void MainMenuCredit::on_btn_logs_clicked()
{
    resetAllTimers();
    emit nextwindow(2);
    this->hide();
}
