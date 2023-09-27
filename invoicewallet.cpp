#include "invoicewallet.h"
#include "ui_invoicewallet.h"

InvoiceWallet::InvoiceWallet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InvoiceWallet)
{
    ui->setupUi(this);
}

InvoiceWallet::~InvoiceWallet()
{
    delete ui;
}

void InvoiceWallet::setmessage(QString card, QString am){
    message = "Transaction made by card: " + card + " is successfull. \n" + "You successfuly added: " + am + " to your Wallet.";
    ui->label->setText(message);
}
