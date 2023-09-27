#ifndef PAYMENTUI_H
#define PAYMENTUI_H

#include <QMainWindow>
#include "visa_payment.h"
#include "cashpayment.h"

namespace Ui {
class PaymentUI;
}

class PaymentUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit PaymentUI(QWidget *parent = nullptr, int userid=0, int cost=0, QString flight= "", bool isflight =0);
    ~PaymentUI();
    Visa_Payment v1;
    CashPayment c1;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::PaymentUI *ui;
};

#endif // PAYMENTUI_H
