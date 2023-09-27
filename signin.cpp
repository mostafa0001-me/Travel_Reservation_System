#include "signin.h"

#include "ui_signin.h"

#include "signup.h"

#include "interface.h"

#include <QMessageBox>

#include <QSqlDatabase>

#include <QSqlQuery>

#include <QSql>

#include <QCoreApplication>

signin::signin(QWidget * parent): QMainWindow(parent), ui(new Ui::signin) {
  ui -> setupUi(this);
}

signin::~signin() {
  delete ui;
}

void signin::on_pushButton_clicked() {
  {

    /*
   bool test = QSqlDatabase::isDriverAvailable("QMYSQL");
   QMessageBox msgBox2121;
   msgBox2121.setText("no");
   if(test) msgBox2121.setText("yes");
   msgBox2121.exec();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("sys");
    db.setUserName("root");
    db.setPassword("mynewpass");
    bool ok = db.open();
    QMessageBox msgBox221;
    msgBox221.setText("no");
    if(ok) msgBox221.setText("yes");
    msgBox221.exec();
*/

    /*  qDebug()<<q.value(0);
      if (q.last()) {
          do {
              qDebug()<<q.value(1);
          } while (q.previous());
      }
  */
    /*
    QSqlQuery query;
        query.prepare("INSERT INTO userlogevents (firstName, lastName, userName, eventMessage, dateTime) VALUES('John', 'Doe', 'JohnnyD', '"+msg+"', datetime(current_timestamp))");
        //---Executes Query Statement---//
        query.exec();
        */

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC","dbcon");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ="+QApplication::applicationDirPath()+"\\DB.accdb");
    db.open();

    QSqlQuery q = db.exec("SELECT ID, password FROM users WHERE email='" + ui -> textEdit -> toPlainText() + "'");
    if (!q.first()) {

      //**************if didn't find a record for this email

      QMessageBox msgBox1;
      msgBox1.setText("Error");
      msgBox1.setInformativeText("Couln't find this email! Do you want to sign up?");
      msgBox1.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
      int ret1 = msgBox1.exec();
      signup * inter;
      switch (ret1) {
      case QMessageBox::Yes:
        db.close();
        inter = new signup;
        inter -> show();
        this -> hide();
        break;
      case QMessageBox::Cancel:
        // Cancel was clicked
        break;
      default:
        // should never be reached
        break;
      }
    } else {

      if (ui -> textEdit_2 -> toPlainText() != q.value(1).toString()) {

        //***********if password is wrong

        QMessageBox msgBox2;
        msgBox2.setText("Error");
        msgBox2.setInformativeText("Wrong Password! Forgot password? Click 'Yes' to reset password, 'No' to try again");
        msgBox2.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret2 = msgBox2.exec();
        switch (ret2) {
        case QMessageBox::Yes:
          // **********forgot password
          break;
        case QMessageBox::No:

          break;
        default:
          break;
        }
      }
      //*************if everything is validated
      else {
        db.close();
        interface * inter = new interface(this, q.value(0).toInt());
        inter -> show();
        this -> hide();
      }
    }
    db.close();
  }
  QSqlDatabase::removeDatabase("dbcon");
}
