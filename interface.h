#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>

namespace Ui {
class interface;
}

class interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface(QWidget *parent = nullptr, int userid=0);
    ~interface();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_actionWrite_a_review_triggered();

    void on_pushButton_clicked();

    void on_actionView_My_Reservations_triggered();

    void on_actionView_My_Wallet_triggered();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::interface *ui;
};

#endif // INTERFACE_H
