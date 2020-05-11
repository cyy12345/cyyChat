/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *server_ip;
    QLineEdit *server_port;
    QLineEdit *username;
    QPushButton *pushButton;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(727, 604);
        label = new QLabel(login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 160, 129, 34));
        label_2 = new QLabel(login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(110, 240, 171, 34));
        label_3 = new QLabel(login);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 310, 171, 34));
        server_ip = new QLineEdit(login);
        server_ip->setObjectName(QString::fromUtf8("server_ip"));
        server_ip->setGeometry(QRect(330, 150, 261, 42));
        server_port = new QLineEdit(login);
        server_port->setObjectName(QString::fromUtf8("server_port"));
        server_port->setGeometry(QRect(330, 230, 261, 42));
        username = new QLineEdit(login);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(330, 310, 261, 42));
        pushButton = new QPushButton(login);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(280, 410, 170, 48));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Dialog", nullptr));
        label->setText(QApplication::translate("login", "Server IP", nullptr));
        label_2->setText(QApplication::translate("login", "Server Port", nullptr));
        label_3->setText(QApplication::translate("login", "Username", nullptr));
        pushButton->setText(QApplication::translate("login", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
