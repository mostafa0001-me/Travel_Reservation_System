#include "flights.h"
#include "ui_flights.h"
#include <QMessageBox>
#include "paymentui.h"
int usERID;
QString flightpath;
Flights::Flights(QWidget *parent, int userid) :
    QMainWindow(parent),
    ui(new Ui::Flights)
{
    ui->setupUi(this);
usERID=userid;
    g1.addEdge(0, 1, 3); g1.addEdge(1, 0, 3); g1.addEdge(0, 4, 5); g1.addEdge(4, 0, 5); g1.addEdge(0, 2, 6); g1.addEdge(2, 0, 6);
    g1.addEdge(4, 2, 10); g1.addEdge(2, 4, 10); g1.addEdge(4, 3, 8); g1.addEdge(3, 4, 8);
    g1.addEdge(3, 1, 2); g1.addEdge(1, 3, 2); g1.addEdge(3, 2, 7); g1.addEdge(2, 3, 7);
    g1.addEdge(1, 2, 12); g1.addEdge(2, 1, 12);

    g2.addEdge(0, 1, 30); g2.addEdge(1, 0, 30); g2.addEdge(0, 4, 50); g2.addEdge(4, 0, 50); g2.addEdge(0, 2, 70); g2.addEdge(2, 0, 70);
    g2.addEdge(4, 2, 90); g2.addEdge(2, 4, 90); g2.addEdge(4, 3, 60); g2.addEdge(3, 4, 60);
    g2.addEdge(3, 1, 25); g2.addEdge(1, 3, 25); g2.addEdge(3, 2, 20); g2.addEdge(2, 3, 20);
    g2.addEdge(1, 2, 65); g2.addEdge(2, 1, 65);

    cost = 0;

}

Flights::~Flights()
{
    delete ui;
}

void Flights::showshort(QString sorc, QString desti, int x){
    for(int i = 0; i < 5; i++){
        if(cities[i] == sorc)
            src = i;
        else if(cities[i] == desti)
            dest = i;
    }
    int* arr = g1.findShortestPath(src, dest);
    message = "The trip with the least time is: " + cities[arr[0]];
    flightpath = cities[arr[0]];
    for(int i = 1; i < g1.index; i++){
        flightpath = flightpath + " -> " + cities[arr[i]];
        message = message + " -> " + cities[arr[i]];
        cost = cost + price[arr[i-1]][arr[i]];
    }
    message = message + "\n with price: " + QString::number(cost) + "$ \n N.B childeren older than 5 are considered a ticket";
    message = message + "\n you will pay extra 50$ for business or 100$ for first class.";
    ui->label->setText(message);
    num = x;
}

void Flights::showcheap(QString sorc, QString desti, int x){
    for(int i = 0; i < 5; i++){
        if(cities[i] == sorc)
            src = i;
        else if(cities[i] == desti)
            dest = i;
    }
    int* arr = g2.findShortestPath(src, dest);
    message = "The trip with the optimal price is: " + cities[arr[0]];
    flightpath = cities[arr[0]];
    int time1 = 0;
    for(int i = 1; i < g2.index; i++){
        message = message + " -> " + cities[arr[i]];
        flightpath = flightpath + " -> " + cities[arr[i]];
        time1 = time1 + time[arr[i-1]][arr[i]];
        cost = cost + price[arr[i-1]][arr[i]];
    }
    message = message + "\n with time: " + QString::number(time1) + " \n N.B childeren older than 5 are considered a ticket";
    message = message + "\n you will pay extra 50$ for business or 100$ for first class.";
    ui->label->setText(message);
    num = x;
}

void Flights::on_pushButton_clicked()
{
    QMessageBox msgBox1;
    msgBox1.setText("Book?");
    msgBox1.setInformativeText("The price of the trip is: " + QString::number(cost * num) + "$");
    msgBox1.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    int ret1 = msgBox1.exec();
    switch (ret1) {

    case QMessageBox::Yes:
      //add to reservations.
        PaymentUI* pay = new PaymentUI(this,usERID,(cost * num), flightpath,1);
        pay->show();
this->hide();
      // break;
    }
  }

void Flights::on_pushButton_2_clicked()
{
    QMessageBox msgBox1;
    msgBox1.setText("Book?");
    msgBox1.setInformativeText("The price of the trip is: " + QString::number((cost + 50) * num) + "$");
    msgBox1.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    int ret1 = msgBox1.exec();
    switch (ret1) {

    case QMessageBox::Yes:
      //add to reservations.
        PaymentUI* pay = new PaymentUI(this, usERID,((cost + 50) * num), flightpath,1);
        pay->show();
this->hide();
      // break;
    }
}

void Flights::on_pushButton_3_clicked()
{
    QMessageBox msgBox1;
    msgBox1.setText("Book?");
    msgBox1.setInformativeText("The price of the trip is: " + QString::number((cost + 100) * num) + "$");
    msgBox1.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    int ret1 = msgBox1.exec();
    switch (ret1) {

    case QMessageBox::Yes:
      //add to reservations.
        PaymentUI* pay = new PaymentUI(this, usERID,((cost + 100) * num), flightpath,1);
        pay->show();
this->hide();
      // break;
    }
}
