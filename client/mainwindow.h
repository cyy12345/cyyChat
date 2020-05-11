#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "Common.h"
#include <QTableWidgetItem>
#include "recvmsgthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int sockfd, QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int sockfd;
    recvMsgThread* thread;

private slots:
    //void getItem(QTableWidgetItem* item);

    void btn_send_slot();
    void recv_msg(char* msg);

};

#endif // MAINWINDOW_H
