#ifndef SIGNIN_H
#define SIGNIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class signin; }
QT_END_NAMESPACE

class signin : public QMainWindow
{
    Q_OBJECT

public:
    signin(QWidget *parent = nullptr);
    ~signin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::signin *ui;
};
#endif // SIGNIN_H
