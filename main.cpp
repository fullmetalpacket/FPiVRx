#include "mainwindow.h"
#include "tcpclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    //MyTCPServer server;
    //MyTCPClient client;

    //Listen connection requests coming from any IP to port 5001
//    if(!server.listen(QHostAddress::Any,5001))
//    {
//        QMessageBox::warning(NULL,"Error","Error Listening Port 5001!");
//    }
//    QProcess process;
//    process.setWorkingDirectory("/Users/fredericlandry");
//    process.execute("touch test > testfred333331122.txt");


    // exit calling application on called application start
    //connect(process, SIGNAL(started()), this, SLOT(Exit()));
    // receive errors
    //connect(process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(error(QProcess::ProcessError)));

    //process->startDetached(command);


    //log("server", "Running local command first. (" + command + ")");
//    qDebug() << process.errorString();
//    qDebug() << process.error();
//    qDebug() << process.state();
//    qDebug() << process.exitCode();
//    qDebug() << process.exitStatus();
//    qDebug() << process.environment();

    return a.exec();
}
