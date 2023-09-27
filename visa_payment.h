#ifndef VISA_PAYMENT_H
#define VISA_PAYMENT_H
#include <QMainWindow>
#include "payment.h"
#include <tchar.h>
#include <string>
#include <stdio.h>
#include <iomanip>
//#include <comdef.h>

namespace Ui {
class PaymentUI;
}

struct expdate{
    int mm;
    int yyyy;
};

class Visa_Payment : public Payment
{
private:
    QString cardnum;
    expdate exp;
    int cvv;
    QString Email;
    QString message;
public:
    Visa_Payment();
    QString info(QString c);
};

#endif // VISA_PAYMENT_H
