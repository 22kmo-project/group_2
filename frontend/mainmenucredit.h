#ifndef MAINMENUCREDIT_H
#define MAINMENUCREDIT_H

#include <QMainWindow>
#include "transactions.h" //Lisää mainiin

namespace Ui {
class mainmenucredit;
}

class mainmenucredit : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainmenucredit(QString, int, QWidget *parent = nullptr);
    ~mainmenucredit();

private slots:
    void on_transactions_Button_clicked(); //Lisää Mainiin

private:
    Ui::mainmenucredit *ui;
    Transactions *transactions;  //Lisää Mainiin

    QString token;
    int id_card;
};

#endif // MAINMENUCREDIT_H
