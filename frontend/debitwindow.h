#ifndef DEBITWINDOW_H
#define DEBITWINDOW_H

#include <QMainWindow>

namespace Ui {
class DebitWindow;
}

class DebitWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebitWindow(QString, int,QWidget *parent = nullptr);
    ~DebitWindow();

private:
    Ui::DebitWindow *ui;
};

#endif // DEBITWINDOW_H
