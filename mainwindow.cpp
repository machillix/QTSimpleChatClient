#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int serverPort = 9999;
    socket = new QTcpSocket(parent);
    socket->connectToHost(QHostAddress("127.0.0.1"),serverPort);
    connect(socket, SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(ui->sendButton,SIGNAL(pressed()),this,SLOT(onSendButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete socket;
}

void MainWindow::onSendButtonPressed()
{
    socket->write(QByteArray::fromStdString(ui->message->text().toStdString()));
}
void MainWindow::onReadyRead(){

    ui->messageArea->append(QString(socket->readAll()));
}
