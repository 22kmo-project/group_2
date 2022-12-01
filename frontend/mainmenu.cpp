#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QDebug>

MainMenu::MainMenu(QString t,int idcard, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    token = t;
    id_card = idcard;
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::resetAllTimers()
{
    emit resettimer30();
}

void MainMenu::cleardata()
{
    id_card = 0;
    token = "";
}

void MainMenu::on_btn_debit_withdraw_clicked()
{
    resetAllTimers();
    emit nextwindow(1);
    this->hide();
}


void MainMenu::on_btn_logs_clicked()
{
    resetAllTimers();
    emit nextwindow(2);
    this->hide();
}

void MainMenu::on_btn_logout_clicked()
{
   // emit logout();
}


void MainMenu::on_btn_debit_settings_clicked()
{
    resetAllTimers();
    emit nextwindow(3);
    this->hide();
}

