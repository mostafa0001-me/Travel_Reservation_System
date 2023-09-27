#ifndef WALLET_H
#define WALLET_H

#include <QMainWindow>
#include"smtp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Wallet; }
QT_END_NAMESPACE

class Wallet : public QMainWindow
{
    Q_OBJECT

public:
    Wallet(QWidget *parent = nullptr, int userid=0);
    ~Wallet();
    void addmoney(int add);
    void convpoint(int point);
    void pay(int amo, QString m);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Wallet *ui;
    int amount, points;
};
#endif // WALLET_H
