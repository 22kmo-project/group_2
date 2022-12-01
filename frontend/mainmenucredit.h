#ifndef MAINMENUCREDIT_H
#define MAINMENUCREDIT_H

#include <QMainWindow>

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

signals:
    void resettimer30();
    void timer10isup();
    void nextwindow(int);

private:
    Ui::MainMenuCredit *ui;
    int id_card;
    QString token;

private slots:
    void on_btn_debit_withdraw_clicked();
    void on_btn_logs_clicked();

};

#endif // MAINMENUCREDIT_H
