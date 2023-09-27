#ifndef INVOICEWALLET_H
#define INVOICEWALLET_H

#include <QMainWindow>

namespace Ui {
class InvoiceWallet;
}

class InvoiceWallet : public QMainWindow
{
    Q_OBJECT

public:
    explicit InvoiceWallet(QWidget *parent = nullptr);
    ~InvoiceWallet();
    void setmessage(QString card, QString am);

private:
    Ui::InvoiceWallet *ui;
    QString message;
};

#endif // INVOICEWALLET_H
