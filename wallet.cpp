#include "wallet.h"
#include "ui_wallet.h"
#include "walletfiller.h"
#include <QSqlDatabase>

#include <QSqlQuery>
#include <QMessageBox>
#include <QSql>
int USERID, amount;
Wallet::Wallet(QWidget *parent, int userid)
    : QMainWindow(parent)
    , ui(new Ui::Wallet)
{
    ui->setupUi(this);
    USERID= userid;

    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("SELECT Wallet, Points FROM users WHERE id=" + QString::number(USERID));
    if(q.first()){
        amount = q.value(0).toInt();
        points = q.value(1).toInt();
        ui->label->setText(QString::number(amount));
        ui->label_2->setText(QString::number(points));
    }
    db.close();
    }
    QSqlDatabase::removeDatabase("dbcon");
}

Wallet::~Wallet()
{
    delete ui;
}

void Wallet::addmoney(int add){
    amount = amount + add;
    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("UPDATE users SET Wallet = '" + QString::number(amount) + "' WHERE ID=" +QString::number(USERID));
    db.close();
    }
    QSqlDatabase::removeDatabase("dbcon");
    //view on screen
    ui->label->setText(QString::number(amount));
}

void Wallet::convpoint(int point){
    if(point != 0){
        points-=point;
        amount = amount + (point / 20);
        {
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
        db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
        db.open();
        QSqlQuery q = db.exec("UPDATE users SET Wallet = '" + QString::number(amount) + "' , Points='"+ QString::number(points) +"' WHERE id=" +QString::number(USERID));
        db.close();
        }
        QSqlDatabase::removeDatabase("dbcon");
    }
    //view on screen
    ui->label->setText(QString::number(amount));
    ui->label_2->setText(QString::number(points));
}

void Wallet::pay(int amo, QString m){
    if(amount > amo){
    amount = amount - amo;

    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("UPDATE users SET Wallet = '" + QString::number(amount) + "' WHERE ID=" +QString::number(USERID));
    db.close();
    }
    QSqlDatabase::removeDatabase("dbcon");
    //view on screen
    ui->label->setText(QString::number(amount));
    Smtp* smtp = new Smtp("speedopointreservations@gmail.com", "Speed*123456789*", "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    smtp->sendMail("speedopointreservations@gmail.com", "mostafamahmoud2086@gmail.com" , "Confirmation","Your payment with wallet is accepted and your reservation is confirmed");
    }
    else{
        QMessageBox msgBox1;
        msgBox1.setText("Transaction Denied");
        msgBox1.setInformativeText("You do not have sufficient amount of money in the wallet to pay.");
        msgBox1.setStandardButtons(QMessageBox::Ok);
        msgBox1.exec();
    }
}

void Wallet::on_pushButton_clicked()
{
    WalletFiller* w1 = new WalletFiller(this);
    w1->show();
    addmoney(w1->getAmount());
destroy(w1);
}

void Wallet::on_pushButton_2_clicked()
{
    convpoint(points);
}
