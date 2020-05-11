#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private:
    Ui::login *ui;
    MainWindow* mainwindow;
    int sockfd;
    struct sockaddr_in serverAddr;

private slots:
    void connectTo();

};

#endif // LOGIN_H
