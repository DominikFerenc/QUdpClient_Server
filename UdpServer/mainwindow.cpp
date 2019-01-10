#include "mainwindow.h"
#include "ui_mainwindow.h"

#define ODD "Odebrane"
#define SERVER_STATUS "Serwer ok!"
#define SERVER_BAD_STATUS "Serwer nie ok!"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

ServerUdp::ServerUdp()
{
    udpSocketServer = new QUdpSocket(this);


    if (udpSocketServer->bind(QHostAddress::LocalHost, 1200, QUdpSocket::ShareAddress))
    {
        result_ready(SERVER_STATUS);
        connect(udpSocketServer, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

    }
    else
        result_ready(SERVER_BAD_STATUS);
}

ServerUdp::~ServerUdp()
{
    udpSocketServer->close();
}



void ServerUdp::processPendingDatagrams()
{

    QByteArray datagram;
    QString datagramString;
    datagram.resize(udpSocketServer->pendingDatagramSize());
    udpSocketServer->readDatagram(datagram.data(), datagram.size());
    datagramString.append(datagram);
    resultReady(datagramString);
    result_ready(ODD);
    

}

void ServerUdp::readPendingDatagrams()
{
    while (udpSocketServer->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = udpSocketServer->receiveDatagram();
        processPendingDatagrams();
        QByteArray bytesDatagrams;
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
    qDebug("Program ServerUDP został zamkniety poprawnie");
}

void MainWindow::on_pushButton_2_clicked()
{
    on_textBrowser_2_windowIconTextChanged("Serwer nasłuchuje");
    udpServer = new ServerUdp();
    connect(udpServer, &ServerUdp::resultReady, this, &MainWindow::on_textBrowser_windowIconTextChanged);
    connect(udpServer, &ServerUdp::result_ready, this, &MainWindow::on_textBrowser_2_windowIconTextChanged);

}

void MainWindow::on_textBrowser_windowIconTextChanged(const QString &iconText)
{
    ui->textBrowser->append(iconText);
}

void MainWindow::on_textBrowser_2_windowIconTextChanged(const QString &text)
{
    ui->textBrowser_2->append(text);
}




