#ifndef ASKFORRECEIPT_H
#define ASKFORRECEIPT_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class AskForReceipt;
}

class AskForReceipt : public QMainWindow
{
    Q_OBJECT

public:
    explicit AskForReceipt(QWidget *parent = nullptr);
    ~AskForReceipt();
    void starttimer();
signals:
    void nextwindow(int);
    void resettimer30();
    void logout();
    void backtomainmenu();
private slots:
    void on_btn_no_clicked();

    void on_btn_yes_clicked();

    void on_btn_logout_clicked();

    void receipttimerslot();

private:
    Ui::AskForReceipt *ui;
    QTimer * receipttimer;
    int time=0;
};

#endif // ASKFORRECEIPT_H
