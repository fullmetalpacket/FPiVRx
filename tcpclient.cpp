#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{

}

void TcpClient::doConnect(QString host, quint16 port)
{

    //MainWindow *ui = new MainWindow;
    //MainWindow *ui = new MainWindow();

    socket = new QTcpSocket(this);

    //connect(socket, SIGNAL(connected()), ui, SLOT(connectedToServer()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "Connecting to " + host + ":" + QString::number(port);

    // this is not blocking call
    socket->connectToHost(host, port);

    // we need to wait...
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
}

//void TcpClient::connected()
//{
//    qDebug() << "Connected...";

//    // Hey server, tell me about you.
//    //socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");

//    //ui->pushButton_Disconnect->setEnabled(true);
//    //ui->pushButton_Connect->setEnabled(false);


//    //ui.findChild<QPushButton*>("pushButton_Connect")->setEnabled(false);

//}

bool TcpClient::writeData(QByteArray data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        qDebug() << "sending data: " + QString::fromUtf8(data);
        socket->write(IntToArray(data.size())); //write size of data
        socket->write(data); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
        return false;
}

void TcpClient::disconnected()
{
    qDebug() << "disconnected...";






}

void TcpClient::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void TcpClient::readyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << socket->readAll();
}

QByteArray TcpClient::IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
