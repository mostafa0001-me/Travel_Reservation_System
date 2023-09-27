#include "paymentui.h"
#include "ui_paymentui.h"
#include "paymentinvoice.h"
#include "wallet.h"
#include <QSqlDatabase>

#include <QSqlQuery>

#include <QSql>
int useRID;
int Cost;
int amount1;
int points1 = 0;
QString Flight;
bool ISflight;
PaymentUI::PaymentUI(QWidget *parent, int userid, int cost, QString flight, bool isflight) :
    QMainWindow(parent),
    ui(new Ui::PaymentUI)
{
    ui->setupUi(this);
    useRID=userid;
    Cost=cost;
    Flight = flight;
    ISflight = isflight;
}

PaymentUI::~PaymentUI()
{
    delete ui;
}

void PaymentUI::on_pushButton_2_clicked()
{

  if(ISflight){  {QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
        db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
        db.open();
                QSqlQuery q = db.exec("SELECT reservations FROM users WHERE ID=" + QString::number(useRID));
                q.first();
                QString userreservation = q.value(0).toString();
                q = db.exec("UPDATE users SET reservations = '" + userreservation + ": The flight " + Flight + " was reserved for a price of " + QString::number(Cost) + "' WHERE id = " + QString::number(useRID));
             db.close(); }
     QSqlDatabase::removeDatabase("dbcon");}
    PaymentInvoice* p1;
    p1 = new PaymentInvoice(this);
    p1->setmessage(v1.info(ui->textEdit_2->toPlainText()), ui->textEdit_4->toPlainText());
    p1->show();
    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("SELECT Wallet, Points FROM users WHERE id=" + QString::number(useRID));
    if(q.first()){
        amount1 = q.value(0).toInt();
        points1 = q.value(1).toInt();
    }
    points1 = points1 + 20;
    db.close();
    }
    QSqlDatabase::removeDatabase("dbcon");
    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("UPDATE users SET Wallet = '" + QString::number(amount1) + "' , Points='"+ QString::number(points1) +"' WHERE id=" +QString::number(useRID));
    db.close();
    }
    QSqlDatabase::removeDatabase("dbcon");
}

void PaymentUI::on_pushButton_clicked()
{
   if(ISflight){   {QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
        db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
        db.open();
                QSqlQuery q = db.exec("SELECT reservations FROM users WHERE ID=" + QString::number(useRID));
                q.first();
                QString userreservation = q.value(0).toString();
                q = db.exec("UPDATE users SET reservations = '" + userreservation + ": The flight " + Flight + " was reserved for a price of " + QString::number(Cost) + "' WHERE id = " + QString::number(useRID));
             db.close(); }
     QSqlDatabase::removeDatabase("dbcon");}
    PaymentInvoice* p1;
    p1 = new PaymentInvoice(this);
    p1->setmessage(c1.info(ui->textEdit_6->toPlainText()), ui->textEdit_10->toPlainText());
    p1->show();
    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("SELECT Wallet, Points FROM users WHERE id=" + QString::number(useRID));
    if(q.first()){
        amount1 = q.value(0).toInt();
        points1 = q.value(1).toInt();
    }
    points1 = points1 + 20;
    db.close();
    }
    QSqlDatabase::removeDatabase("dbcon");
    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("UPDATE users SET Wallet = '" + QString::number(amount1) + "' , Points='"+ QString::number(points1) +"' WHERE id=" +QString::number(useRID));
    db.close();
    }
    QSqlDatabase::removeDatabase("dbcon");
}

void PaymentUI::on_pushButton_4_clicked()
{

    Wallet* w1;
    w1 = new Wallet(this, useRID);
    w1->pay(Cost, ui->textEdit_10->toPlainText());
  if(ISflight){    {QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
        db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
        db.open();
                QSqlQuery q = db.exec("SELECT reservations FROM users WHERE ID=" + QString::number(useRID));
                q.first();
                QString userreservation = q.value(0).toString();
                q = db.exec("UPDATE users SET reservations = '" + userreservation + ": The flight " + Flight + " was reserved for a price of " + QString::number(Cost) + "' WHERE id = " + QString::number(useRID));
             db.close(); }
     QSqlDatabase::removeDatabase("dbcon");}
    destroy(w1);
    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("SELECT Wallet, Points FROM users WHERE id=" + QString::number(useRID));
    if(q.first()){
        amount1 = q.value(0).toInt();
        points1 = q.value(1).toInt();
    }
    points1 = points1 + 20;
    db.close();
    }
    QSqlDatabase::removeDatabase("dbcon");
    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("UPDATE users SET Wallet = '" + QString::number(amount1) + "' , Points='"+ QString::number(points1) +"' WHERE id=" +QString::number(useRID));
    db.close();
    }
    QSqlDatabase::removeDatabase("dbcon");

}

void PaymentUI::on_pushButton_3_clicked()
{
    Wallet* w1;
    w1 = new Wallet(this, useRID);
    w1->pay(Cost, ui->textEdit_4->toPlainText());
    if(ISflight){  {QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
        db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
        db.open();
                QSqlQuery q = db.exec("SELECT reservations FROM users WHERE ID=" + QString::number(useRID));
                q.first();
                QString userreservation = q.value(0).toString();
                q = db.exec("UPDATE users SET reservations = '" + userreservation + ": The flight " + Flight + " was reserved for a price of " + QString::number(Cost) + "' WHERE id = " + QString::number(useRID));
             db.close(); }
     QSqlDatabase::removeDatabase("dbcon");}
    destroy(w1);
    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("SELECT Wallet, Points FROM users WHERE id=" + QString::number(useRID));
    if(q.first()){
        amount1 = q.value(0).toInt();
        points1 = q.value(1).toInt();
    }
    points1 = points1 + 20;
    db.close();
    }
    QSqlDatabase::removeDatabase("dbcon");
    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("UPDATE users SET Wallet = '" + QString::number(amount1) + "' , Points='"+ QString::number(points1) +"' WHERE id=" +QString::number(useRID));
    db.close();
    }
    QSqlDatabase::removeDatabase("dbcon");
}
