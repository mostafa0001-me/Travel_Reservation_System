#ifndef PAYMENT_H
#define PAYMENT_H
#include <QMainWindow>


class Payment
{
private:
   int amounttopay;
public:
    Payment();
    virtual QString info(QString c) = 0;
};

#endif // PAYMENT_H

