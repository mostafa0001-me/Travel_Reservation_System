#include "paymentinvoice.h"
#include "ui_paymentinvoice.h"
#include "smtp.h"

PaymentInvoice::PaymentInvoice(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaymentInvoice)
{
    ui->setupUi(this);
}

PaymentInvoice::~PaymentInvoice()
{
    delete ui;
}

void PaymentInvoice::setmessage(QString m, QString em){
    ui->label->setText(m);
    Smtp* smtp = new Smtp("speedopointreservations@gmail.com", "Speed*123456789*", "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    smtp->sendMail("speedopointreservations@gmail.com", em , "Confirmation",m);
}
