#ifndef PAYMENTINVOICE_H
#define PAYMENTINVOICE_H

#include <QMainWindow>

namespace Ui {
class PaymentInvoice;
}

class PaymentInvoice : public QMainWindow
{
    Q_OBJECT

public:
    explicit PaymentInvoice(QWidget *parent = nullptr);
    ~PaymentInvoice();
    void setmessage(QString m, QString em);

private:
    Ui::PaymentInvoice *ui;
};

#endif // PAYMENTINVOICE_H
