#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget_userlist->setColumnCount(2);
    QStringList list;
    list << "userID" << "name";
    ui->tableWidget_userlist->setHorizontalHeaderLabels(list);
    ui->tableWidget_userlist->verticalHeader()->setVisible(false); //隐藏行表头
    ui->tableWidget_userlist->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget_userlist->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_userlist->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改


    ui->tableWidget_message->setColumnCount(1);
    ui->tableWidget_message->setShowGrid(false);
    ui->tableWidget_message->setColumnWidth(10,790);
    ui->tableWidget_message->verticalHeader()->setVisible(false);
    ui->tableWidget_message->horizontalHeader()->setVisible(false);
    ui->tableWidget_message->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //recv_userinfo();
    connect(ui->tableWidget_userlist,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(getItem(QTableWidgetItem*)));
    connect(ui->btn_send,SIGNAL(clicked()),this,SLOT(btn_send_slot()));
    //connect(thread,SIGNAL(sendMsg_signal(Msg*)),this,SLOT(recv_msg(Msg*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Client::Close();
}
