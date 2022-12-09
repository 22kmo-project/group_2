#ifndef DEBITAMOUNTWINDOW_H
#define DEBITAMOUNTWINDOW_H

#include <QDialog>

namespace Ui {
class DebitAmountWindow;
}

class DebitAmountWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DebitAmountWindow(QWidget *parent = nullptr);
    ~DebitAmountWindow();

signals:
    void customAmount(int);
    void back();

private slots:
    void on_withdraw_btn_clicked();

    void on_back_btn_clicked();

private:
    Ui::DebitAmountWindow *ui;
};

#endif // DEBITAMOUNTWINDOW_H
