#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpclient.h"
#include <QtWidgets>
#include <QtNetwork>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QMessageBox>
#include <QDebug>

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{

}

void TcpClient::doConnect(QString host, quint16 port)
{

    //MainWindow *ui = new MainWindow;
    MainWindow *ui = new MainWindow();

    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), ui, SLOT(connectedToServer()));
    //connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(displayState(QAbstractSocket::SocketState)));


    if(validateIpAddress(host))
    {

        qDebug() << "Connecting to " + host + ":" + QString::number(port);

        // this is not blocking call
        socket->connectToHost(host, port);


        // we need to wait...
        if(!socket->waitForConnected(5000))
        {
            qDebug() << "Error: " << socket->errorString();
        }

    }
    else
    {

        QMessageBox::warning(NULL, "Error", "This IP address is invalid.");
        qDebug() << "Invalid ip address: " + host;

    }

}


bool TcpClient::validateIpAddress(QString ipAddress)
{

    QHostAddress myIP;

    if(myIP.setAddress(ipAddress))
    {
        qDebug() << "validateIpAddress(): valid IP";
        return true;
    }
    else
    {
        qDebug() << "validateIpAddress(): Invalid IP";
        return false;
    }
}

void TcpClient::connected()
{
    qDebug() << "Connected...";

    // Hey server, tell me about you.
    //socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");

    //ui->pushButton_Disconnect->setEnabled(true);
    //ui->pushButton_Connect->setEnabled(false);


    //ui.findChild<QPushButton*>("pushButton_Connect")->setEnabled(false);

}

void TcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    //qDebug() << "onConnectError() fired...";

    QString errorString = errorToString(socketError);

    if(!errorString.isEmpty())
    {
        QMessageBox::critical(NULL, "Socket Error", errorString);
    }

    // Hey server, tell me about you.
    //socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");

    //ui->pushButton_Disconnect->setEnabled(true);
    //ui->pushButton_Connect->setEnabled(false);


    //ui.findChild<QPushButton*>("pushButton_Connect")->setEnabled(false);

}

void TcpClient::displayState(QAbstractSocket::SocketState socketState)
{
    //qDebug() << "onConnectError() fired...";

    QString stateString = stateToString(socketState);

    if(!stateString.isEmpty())
    {
        //QMessageBox::critical(NULL, "Socket Error", errorString);
        qDebug() << "displayState() fired... " + stateString;
    }

    // Hey server, tell me about you.
    //socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");

    //ui->pushButton_Disconnect->setEnabled(true);
    //ui->pushButton_Connect->setEnabled(false);


    //ui.findChild<QPushButton*>("pushButton_Connect")->setEnabled(false);

}

QString TcpClient::stateToString(QAbstractSocket::SocketState socketState)
{

    QString stateString;

    switch(socketState)
    {
        case QAbstractSocket::UnconnectedState : stateString = "The socket is not connected.";
        break;
        case QAbstractSocket::HostLookupState : stateString = "The socket is performing a host name lookup.";
        break;
        case QAbstractSocket::ConnectingState : stateString = "The socket has started establishing a connection.";
        break;
        case QAbstractSocket::ConnectedState : stateString = "A connection is established.";
        break;
        case QAbstractSocket::BoundState : stateString = "The socket is bound to an address and port.";
        break;
        case QAbstractSocket::ClosingState : stateString = "The socket is about to close.";
        break;
        case QAbstractSocket::ListeningState : stateString = "Listening state.";
        break;
        default: stateString = "Unknown state.";
    }

    return stateString;
}

QString TcpClient::errorToString(QAbstractSocket::SocketError socketError)
{

    QString errorString;

    switch(socketError)
    {
        case QAbstractSocket::ConnectionRefusedError : errorString = "The connection was refused by the peer (or timed out).";
        break;
//        case QAbstractSocket::RemoteHostClosedError : errorString = "The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.";
//        break;
        case QAbstractSocket::HostNotFoundError : errorString = "The host address was not found.";
        break;
        case QAbstractSocket::SocketAccessError : errorString = "The socket operation failed because the application lacked the required privileges.";
        break;
        case QAbstractSocket::SocketResourceError : errorString = "The local system ran out of resources (e.g., too many sockets).";
        break;
        case QAbstractSocket::SocketTimeoutError : errorString = "The socket operation timed out.";
        break;
        case QAbstractSocket::DatagramTooLargeError : errorString = "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).";
        break;
        case QAbstractSocket::NetworkError : errorString = "An error occurred with the network (e.g., the network cable was accidentally plugged out).";
        break;
        case QAbstractSocket::AddressInUseError : errorString = "The address specified to QAbstractSocket::bind() is already in use and was set to be exclusive.";
        break;
        case QAbstractSocket::SocketAddressNotAvailableError : errorString = "The address specified to QAbstractSocket::bind() does not belong to the host.";
        break;
        case QAbstractSocket::UnsupportedSocketOperationError : errorString = "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support).";
        break;
        case QAbstractSocket::ProxyAuthenticationRequiredError : errorString = "The socket is using a proxy, and the proxy requires authentication.";
        break;
        case QAbstractSocket::SslHandshakeFailedError : errorString = "The SSL/TLS handshake failed, so the connection was closed (only used in QSslSocket)";
        break;
        case QAbstractSocket::UnfinishedSocketOperationError : errorString = "Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background).";
        break;
        case QAbstractSocket::ProxyConnectionRefusedError : errorString = "Could not contact the proxy server because the connection to that server was denied";
        break;
        case QAbstractSocket::ProxyConnectionClosedError : errorString = "The connection to the proxy server was closed unexpectedly (before the connection to the final peer was established)";
        break;
        case QAbstractSocket::ProxyConnectionTimeoutError : errorString = "The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase.";
        break;
        case QAbstractSocket::ProxyNotFoundError : errorString = "The proxy address set with setProxy() (or the application proxy) was not found.";
        break;
        case QAbstractSocket::ProxyProtocolError : errorString = "The connection negotiation with the proxy server failed, because the response from the proxy server could not be understood.";
        break;
        case QAbstractSocket::OperationError : errorString = "An operation was attempted while the socket was in a state that did not permit it.";
        break;
        case QAbstractSocket::SslInternalError : errorString = "The SSL library being used reported an internal error. This is probably the result of a bad installation or misconfiguration of the library.";
        break;
        case QAbstractSocket::SslInvalidUserDataError : errorString = "Invalid data (certificate, key, cypher, etc.) was provided and its use resulted in an error in the SSL library.";
        break;
        case QAbstractSocket::TemporaryError : errorString = "A temporary error occurred (e.g., operation would block and socket is non-blocking).";
        break;
        case QAbstractSocket::UnknownSocketError : errorString = "An unidentified error occurred.";
        break;
        //default: errorString = "Unknown error.";
    }

    return errorString;
}

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
