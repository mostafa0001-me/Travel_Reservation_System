#ifndef WALLETFILLER_H
#define WALLETFILLER_H

#include <QMainWindow>
#include "invoicewallet.h"

namespace Ui {
class WalletFiller;
}

class WalletFiller : public QMainWindow
{
    Q_OBJECT

public:
    explicit WalletFiller(QWidget *parent = nullptr);
    ~WalletFiller();
    int getAmount();
    void showinvoice();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WalletFiller *ui;
    QString card;
    QString amount;
    InvoiceWallet* inv;
};

#endif // WALLETFILLER_H
