#include "visa_payment.h"
#include "paymentui.h"
#include "ui_paymentui.h"


Visa_Payment::Visa_Payment()
{
    cardnum = "";
}

QString Visa_Payment::info(QString c){
    cardnum = c;
    message =  message = "Transaction made by card: " + c + " is successfull. \n" + "Your reservation is confirmed";
    return message;
}
