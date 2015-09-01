#ifndef TCPCLIENT
#define TCPCLIENT

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class TcpClient : public QObject
{

    Q_OBJECT

    public:
        explicit TcpClient(QObject *parent = 0);
        void doConnect(QString host, quint16 port);
        bool writeData(QByteArray data);
        bool validateIpAddress(QString ipAddress);
        QString stateToString(QAbstractSocket::SocketState socketState);
        QString errorToString(QAbstractSocket::SocketError socketError);
        QByteArray IntToArray(qint32 source);

    signals:


    public slots:
//        void connected();
        void disconnected();
        void bytesWritten(qint64 bytes);
        void readyRead();
        void displayError(QAbstractSocket::SocketError socketError);
        void displayState(QAbstractSocket::SocketState socketState);

    private:
        QTcpSocket *socket;

};

#endif // TCPCLIENT
