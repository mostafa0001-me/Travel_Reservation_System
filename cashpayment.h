#ifndef CASHPAYMENT_H
#define CASHPAYMENT_H
#include "payment.h"


class CashPayment : Payment
{
private:
    QString address;
    QString message;
public:
    CashPayment();
    QString info(QString c);
};

#endif // CASHPAYMENT_H
