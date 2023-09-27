#include "walletfiller.h"
#include "ui_walletfiller.h"
#include <QEventLoop>
#include <QApplication>
QEventLoop loop;
WalletFiller::WalletFiller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WalletFiller)
{
    ui->setupUi(this);
}

WalletFiller::~WalletFiller()
{
    delete ui;
}

int WalletFiller::getAmount(){
    loop.exec();
    amount = ui->textEdit->toPlainText();
    return amount.toInt();
}

void WalletFiller::showinvoice(){
    card = ui->textEdit_2->toPlainText();
    amount = ui->textEdit->toPlainText();
    inv = new InvoiceWallet(this);
    inv->setmessage(card, amount);
    inv->show();
    loop.quit();
}

void WalletFiller::on_pushButton_clicked()
{
    showinvoice();

}
