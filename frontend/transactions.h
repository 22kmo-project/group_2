#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QDialog>

namespace Ui {
class Transactions;
}

class Transactions : public QDialog
{
    Q_OBJECT

public:
    explicit Transactions(QWidget *parent = nullptr);
    ~Transactions();

private slots:
    void on_btn_Back_clicked();

    void on_btn_LogOut_clicked();


private:
    Ui::Transactions *ui;
};

#endif // TRANSACTIONS_H
