#ifndef TCPSERVER
#define TCPSERVER


#include <QtNetwork>
#include <QtWidgets>

class MyTCPServer:public QTcpServer
{

  Q_OBJECT

public:
  MyTCPServer()
  {
    connect(this, SIGNAL(newConnection()), SLOT(slotNewConnection()));
  }

public slots:
  void slotNewConnection()
  {
    connection = nextPendingConnection();
    connect(connection, SIGNAL(readyRead()), SLOT(readData()));
    QMessageBox::information(NULL, "New Connection!", QString::number(connection->peerPort()));
  }

  void readData()
  {
    QMessageBox::information(NULL, "Received Data!", "Client Says: " + QString(connection->readAll()));
  }

private:
  QTcpSocket* connection;

};


















#endif // TCPSERVER

