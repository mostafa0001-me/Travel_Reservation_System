#include "signup.h"

#include "signin.h"

#include "ui_signup.h"

#include "interface.h"

#include <QMessageBox>

#include <QSqlDatabase>

#include <QSqlQuery>

#include <QSql>

signup::signup(QWidget * parent):
  QMainWindow(parent),
  ui(new Ui::signup) {
    ui -> setupUi(this);

  }

signup::~signup() {
  delete ui;
}

void signup::on_pushButton_clicked() {
  {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ="+QApplication::applicationDirPath()+"\\DB.accdb");
    db.open();
    QSqlQuery q = db.exec("SELECT ID, password FROM users WHERE email='" + ui -> textEdit -> toPlainText() + "'");

    // *******check if it already exists
    if (!q.first()) {

      if (ui -> textEdit_3 -> toPlainText() == ui -> textEdit_4 -> toPlainText()) {
        //*****add acount to database
          q = db.exec("INSERT INTO users (name, email, password, Wallet, Points, reservations) VALUES('"+ui->textEdit_2->toPlainText() +"', '"+ui->textEdit->toPlainText()+"', '"+ui->textEdit_3->toPlainText()+"', '0', '0', '')");
          q = db.exec("SELECT ID FROM users WHERE email='" + ui -> textEdit -> toPlainText() + "'");
          q.first();
        interface * inter = new interface(this,q.value(0).toInt());
        inter -> show();
        this -> hide();
      } else {
        QMessageBox msgBox2;
        msgBox2.setText("Error");
        msgBox2.setInformativeText("Passwords do not match! Please try again.");
        msgBox2.setStandardButtons(QMessageBox::Ok);
        int ret2 = msgBox2.exec();
        switch (ret2) {
        case QMessageBox::Ok:
          ui -> textEdit_4 -> setText("");
          break;
        default:
          break;
        }
      }

    } else {
      QMessageBox msgBox2;
      msgBox2.setText("Error");
      msgBox2.setInformativeText("This email already exists! Sign in instead?");
      msgBox2.setStandardButtons(QMessageBox::Ok);
      signin * s_in;
      int ret2 = msgBox2.exec();
      switch (ret2) {
      case QMessageBox::Ok:
        s_in = new signin;
        s_in -> show();
        this -> hide();
        break;
      default:
        break;
      }
    }
    db.close();
  }
  QSqlDatabase::removeDatabase("dbcon");
}
