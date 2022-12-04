#include "debitwindow.h"
#include "ui_debitwindow.h"

DebitWindow::DebitWindow(QString token, int idcard,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebitWindow)
{
    ui->setupUi(this);
}

DebitWindow::~DebitWindow()
{
    delete ui;
}
