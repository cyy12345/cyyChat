#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    serverAddr.sin_family = AF_INET;
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this, SLOT(connectTo()));
}

login::~login()
{
    delete ui;
}

void login::connectTo()
{
    std::string server_ip = ui->server_ip->text().toStdString();
    std::string port = ui->server_port->text().toStdString();
    std::string username = ui->username->text().toStdString();

    if(server_ip =="" || port == "" || username == "")
    {
        qDebug() << "DON'T LEAVE THINGS BLANK" << endl;
        return;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_port = htons(stoi(port));
    serverAddr.sin_addr.s_addr = inet_addr(server_ip.c_str());
    clientInfo ci;
    strcpy(ci.username,username.c_str());
    if(sockfd < 0){
        perror("sock error");
        exit(-1);
    }
    std::cout << server_ip << std::endl;
    std::cout << port << std::endl;
    if(::connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0){
        perror("connect error");
        exit(-1);
    }
    int len = send(sockfd, (void*)&ci,sizeof(clientInfo),0);

    if(len < 0){
        perror("login error");
        exit(-1);
    }

//    char msg[BUF_SIZE]={0};

//    len = recv(sockfd,msg,BUF_SIZE,0);
//    std::cout << msg << std::endl;
//    if(len < 0){
//        perror("login error");
//        exit(-1);
//    }

//    if(!strcmp(msg,"Welcome to join the chat room!"))
//    {
        qDebug() << "login successful" << endl;
        mainwindow = new MainWindow(sockfd);
        mainwindow->show();
        this->close();
        //delete this;
//    }else
//    {
  //      return;
  //  }

}
