#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include "Client.h"
#include "mainwindow.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT
public:
    login();
private:
    Ui::login *ui;
    std::shared_ptr<MainWindow> main_window;
    std::shared_ptr<Client> client;
};

#endif // LOGIN_H
