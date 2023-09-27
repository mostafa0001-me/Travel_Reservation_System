#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <QMainWindow>
#include "graph.h"
namespace Ui {
class Flights;
}

class Flights : public QMainWindow
{
    Q_OBJECT

public:
    explicit Flights(QWidget *parent = nullptr, int userid = 0);
    ~Flights();
    void showshort(QString sorc, QString desti, int x);
    void showcheap(QString sorc, QString desti, int x);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Flights *ui;
    QString message;
    Graph g1;
    Graph g2;
    int price[5][5] = {{0, 30, 70, 0, 50}, {30, 0, 60, 25, 0}, {70, 60, 0, 20, 90}, {0, 25, 20, 0, 65}, {50, 0, 90, 65, 0}};
    int time[5][5] = {{-1, 3, 6, -2, 5}, {3, -1, 12, 2, -2}, {6, 12, -1, 7, 10}, {-2, 2, 7, -1, 8}, {5, -2, 10, 8, -1}};
    QString cities[5] = {"Cairo", "London", "Newyork", "Estanbul", "Paris"};
    int src, dest, cost, num;
};

#endif // FLIGHTS_H
