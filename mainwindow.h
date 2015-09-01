#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMediaPlayer>
#include <QSpinBox>
#include <QVideoWidget>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QProcess>
#include "ui_mainwindow.h"
#include "tcpclient.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        void defaultValues();
        void log(QString where, QString data);
        bool runLocalCommand(QString command);
        bool killLocalCommand();
        bool checkIfProcessIsRunning(QString process);
        QString generateRemoteGStreamerCommand();
        QString generateLocalGStreamerCommand();
        QLineEdit lineEdit_ServerIp;
        QSpinBox spinBox_ServerPort;
        TcpClient s;

    public slots:
        void connectedToServer();

    private slots:
        void on_pushButton_Mute_clicked();
        void on_pushButton_Connect_clicked();
        void on_pushButton_Disconnect_clicked();
        void on_pushButton_Shutdown_clicked();
        void on_pushButton_StartStreaming_clicked();
        void on_pushButton_StopStreaming_clicked();

    private:
        Ui::MainWindow *ui;
        QMediaPlayer livePlayer;
        QMediaPlayer recordingPlayer;

};

#endif // MAINWINDOW_H
