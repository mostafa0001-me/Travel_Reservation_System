#include "interface.h"
#include "wallet.h"

#include "paymentui.h"
#include "ui_interface.h"

#include <QApplication>

#include <QInputDialog>

#include <QDate>

#include <QMessageBox>

#include <QSqlDatabase>

#include <QSqlQuery>

#include <QSql>

#include <QCoreApplication>

#include <QStringList>

#include <QStringListModel>

#include <QAbstractItemView>

#include "wallet.h"

#include "flights.h"


int userID;
interface::interface(QWidget * parent, int userid):
  QMainWindow(parent),
  ui(new Ui::interface) {
    ui -> setupUi(this);
    userID = userid;
  }

interface::~interface() {
  delete ui;
}

void interface::on_checkBox_stateChanged(int arg1) {
  if (ui -> checkBox -> isChecked()) {
    ui -> back_date -> setVisible(true);
    ui -> back_label -> setVisible(true);
  } else {
    ui -> back_date -> setVisible(false);
    ui -> back_label -> setVisible(false);
  }
}
QString review(QString title) {
  bool ok;
  // Ask for birth date as a string.
  QString text = QInputDialog::getMultiLineText(0, title,
    "Review:",
    "", & ok);
  if (ok && !text.isEmpty()) {
    return text;
  } else if (ok && text.isEmpty()) {
    return review("Please enter a valid review");
  } else {
    return "";
  }

}
void interface::on_actionWrite_a_review_triggered() {
  review("Enter your review");
}

void interface::on_pushButton_clicked() {
  {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
    db.open();
    QVector < QString > hotels;
    QSqlQuery q = db.exec("SELECT Hotel FROM rooms WHERE Location='" + ui -> lineEdit_3 -> text() + "' GROUP BY Hotel");
    if (q.first()) {
      do {
        hotels.append(q.value(0).toString());
      } while (q.next());
    }

    for (auto & hotel: hotels) {

      int r1 = 0, r2 = 0, r1p = 0, r2p = 0; // r1 is the number of single rooms available and r2 is the number of double rooms available.
      QVector < int > r1numbers, r2numbers;
      QSqlQuery q = db.exec("SELECT reservations, capacity, price, rating, ID FROM rooms WHERE Location='" + ui -> lineEdit_3 -> text() + "' AND Hotel='" + hotel + "'");
      if (q.first()) {
        do {
          bool t = true;
          QStringList list = q.value(0).toString().split(":", Qt::SkipEmptyParts);
          for (auto & ls: list) {
            QStringList dates = ls.split("-");
            if ((dates[0].toInt() <= ui -> dateEdit -> date().toJulianDay() && ui -> dateEdit -> date().toJulianDay() <= dates[1].toInt()) ||
              (dates[0].toInt() <= ui -> dateEdit_2 -> date().toJulianDay() && ui -> dateEdit_2 -> date().toJulianDay() <= dates[1].toInt())) {
              t = false;
            }
          }
          if (t) {
            if (q.value(1).toInt() == 1) {
              r1 += 1;
              r1p += q.value(2).toInt();
              r1numbers.append(q.value(4).toInt());
            }
            if (q.value(1).toInt() == 2) {
              r2 += 1;
              r2p += q.value(2).toInt();
              r2numbers.append(q.value(4).toInt());
            }
          }
        } while (q.next());
      }
      r1 != 0 ? r1p /= r1 : r1p = 0;
      r2 != 0 ? r2p /= r2 : r2p = 0;
      int doublerooms = ui -> spinBox -> text().toInt() / 2;
      int singlerooms = ui -> spinBox -> text().toInt() % 2;
      if (r2 < doublerooms) {
        singlerooms += (doublerooms - r2) * 2;
        doublerooms = r2;
      }
      if (r1 >= singlerooms) {
        int price = doublerooms * r2p + singlerooms * r1p + ui -> spinBox_2 -> text().toInt() / 2.0 * (doublerooms == 0 ? r1p : r2p);
        q.first();
        int stars = q.value(3).toInt();
        QMessageBox msgBox1;
        msgBox1.setText("Book?");
        msgBox1.setInformativeText(hotel + " (" + QString::number(stars) + " stars) is available with optimal price of " + QString::number(price) +
          (doublerooms != 0 ? (", " + QString::number(doublerooms) + " double room(s)(" + QString::number(r2p) + " per room)") : "") + (singlerooms != 0 ? (", " + QString::number(singlerooms) + " single room(s)(" + QString::number(r1p) + " per room)") : "") + (ui -> spinBox_2 -> text().toInt() != 0 ? (" and a half charge of " + QString((doublerooms == 0 ? "single room" : "double room")) + " for the kids") : ""));
        msgBox1.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        int ret1 = msgBox1.exec();
        switch (ret1) {

        case QMessageBox::Yes:
          for (int i = 0; i < singlerooms; i++) {
            QSqlQuery q = db.exec("SELECT reservations FROM rooms WHERE ID=" + QString::number(r1numbers[i]));
            q.first();
            QString reservation = q.value(0).toString();
            q = db.exec("UPDATE rooms SET reservations = '" + reservation + ":" + QString::number(ui -> dateEdit -> date().toJulianDay()) + "-" + QString::number(ui -> dateEdit_2 -> date().toJulianDay()) + "' WHERE id = " + QString::number(r1numbers[i]));
          }
          for (int i = 0; i < doublerooms; i++) {
            QSqlQuery q = db.exec("SELECT reservations FROM rooms WHERE ID=" + QString::number(r2numbers[i]));
            q.first();
            QString reservation = q.value(0).toString();
            q = db.exec("UPDATE rooms SET reservations = '" + reservation + ":" + QString::number(ui -> dateEdit -> date().toJulianDay()) + "-" + QString::number(ui -> dateEdit_2 -> date().toJulianDay()) + "' WHERE id = " + QString::number(r2numbers[i]));
          } {
            QSqlQuery q = db.exec("SELECT reservations FROM users WHERE ID=" + QString::number(userID));
            q.first();
            QString userreservation = q.value(0).toString();
            q = db.exec("UPDATE users SET reservations = '" + userreservation + ":" + hotel + " (" + QString::number(stars) + " stars) was reserved for a price of " + QString::number(price) + " from " + ui -> dateEdit -> date().toString() + " to " + ui -> dateEdit_2 -> date().toString() +
              (doublerooms != 0 ? (", " + QString::number(doublerooms) + " double room(s)(" + QString::number(r2p) + " per room)") : "") + (singlerooms != 0 ? (", " + QString::number(singlerooms) + " single room(s)(" + QString::number(r1p) + " per room)") : "") + (ui -> spinBox_2 -> text().toInt() != 0 ? (" and a half charge of " + QString((doublerooms == 0 ? "single room" : "double room")) + " for the kids") : "") + "' WHERE id = " + QString::number(userID));
          }

        {PaymentUI* pay = new PaymentUI(this, userID,price,"",1);
          pay->show();}
          // break;
          case QMessageBox::Cancel:
            // Cancel was clicked
            // break;
          default:
            // should never be reached
            break;
        }
      }
    }
    db.close();

  }
  QSqlDatabase::removeDatabase("dbcon");
}

void interface::on_actionView_My_Reservations_triggered() {
  QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
  db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=" + QApplication::applicationDirPath() + "\\DB.accdb");
  db.open();
  QVector < QString > hotels;
  QSqlQuery q = db.exec("SELECT reservations FROM users WHERE id=" + QString::number(userID));
  q.first();
  QString list = q.value(0).toString().replace(":", "\n");
  QMessageBox msgBox1;
  msgBox1.setText("Your Reservations");
  msgBox1.setInformativeText(list);
  msgBox1.setStandardButtons(QMessageBox::Ok);
  msgBox1.exec();

}

void interface::on_actionView_My_Wallet_triggered()
{
    Wallet* w1;
    w1 = new Wallet(this, userID);
    w1->show();
}

void interface::on_pushButton_3_clicked()
{
    Flights* f1 = new Flights(this, userID);
    f1->showshort(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->spinBox_4->text().toInt());
    f1->show();
}

void interface::on_pushButton_2_clicked()
{
    Flights* f1 = new Flights(this, userID);
    f1->showcheap(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->spinBox_4->text().toInt());
    f1->show();
}
