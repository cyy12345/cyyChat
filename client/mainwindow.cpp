#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int sockfd, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget_userlist->setColumnCount(2);
    this->sockfd = sockfd;
    QStringList list;
    list << "userID" << "name";
    ui->tableWidget_userlist->setHorizontalHeaderLabels(list);
    ui->tableWidget_userlist->verticalHeader()->setVisible(false); //隐藏行表头
    ui->tableWidget_userlist->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget_userlist->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_userlist->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改


    ui->tableWidget_message->setColumnCount(1);
    ui->tableWidget_message->setShowGrid(false);
    ui->tableWidget_message->setColumnWidth(0,800);
    ui->tableWidget_message->setRowHeight(0,500);
    ui->tableWidget_message->verticalHeader()->setVisible(false);
    ui->tableWidget_message->horizontalHeader()->setVisible(false);
    ui->tableWidget_message->setEditTriggers(QAbstractItemView::NoEditTriggers);

    thread = new recvMsgThread(sockfd);
    thread->start();

    //recv_userinfo();
    //connect(ui->tableWidget_userlist,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(getItem(QTableWidgetItem*)));
    connect(ui->btn_send,SIGNAL(clicked()),this,SLOT(btn_send_slot()));
    connect(thread,SIGNAL(sendMsg_signal(char*)),this,SLOT(recv_msg(char*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    ::close(sockfd);
}

void MainWindow::btn_send_slot()
{
    QString msg_str = ui->plainTextEdit->toPlainText();
    if(msg_str == ""){
        return;
    }
    char msg[BUF_SIZE];

    strcpy(msg,msg_str.toStdString().c_str());
    send(sockfd,msg,strlen(msg),0);
    int row_count = ui->tableWidget_message->rowCount();
    ui->tableWidget_message->insertRow(row_count);
    ui->tableWidget_message->setItem(row_count,0,new QTableWidgetItem(QString(msg)+ ": Me"));
    QTableWidgetItem* item = ui->tableWidget_message->item(row_count,0);
    item->setTextAlignment(Qt::AlignRight);
    ui->plainTextEdit->clear();

}

void MainWindow::recv_msg(char* msg)
{
    int row_count = ui->tableWidget_message->rowCount();
    ui->tableWidget_message->insertRow(row_count);
    ui->tableWidget_message->setItem(row_count,0,new QTableWidgetItem(QString(msg)));
}
