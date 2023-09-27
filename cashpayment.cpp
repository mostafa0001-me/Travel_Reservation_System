#include "cashpayment.h"

CashPayment::CashPayment()
{
    address = "";
}

QString CashPayment::info(QString c){
    address = c;
    message =  message = "Your reservation is confirmed \n and one of our representatives will meet you at: \n" + address;
    return message;
}
