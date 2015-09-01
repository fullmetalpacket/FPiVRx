#include <QMediaPlayer>
#include <QVideoWidget>
#include <QtWidgets>
#include <QtNetwork>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    defaultValues();

    QString videofile = "/Users/fredericlandry/Downloads/test2.mp4";

    QMediaPlayer *livePlayer = new QMediaPlayer;

    livePlayer->setMedia(QUrl::fromLocalFile(videofile));

    livePlayer->setVideoOutput(ui->liveVideoFrame);

    livePlayer->pause();



    QMediaPlayer *recordingPlayer = new QMediaPlayer;

    recordingPlayer->setMedia(QUrl::fromLocalFile(videofile));

    recordingPlayer->setVideoOutput(ui->recordingVideoFrame);

    recordingPlayer->pause();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connectedToServer()
{

    qDebug() << "Connected UI...";

    //ui->label_ServerStatus->setText("Connected!");

    // Hey server, tell me about you.
    //socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");

    //ui->pushButton_Disconnect->setEnabled(true);
    //ui->pushButton_Connect->setEnabled(false);


    //ui.findChild<QPushButton*>("pushButton_Connect")->setEnabled(false);

}

void MainWindow::defaultValues()
{

    // ComboBox AWB Mode
    ui->comboBox_AWBMode->addItem("Off");
    ui->comboBox_AWBMode->addItem("Auto");
    ui->comboBox_AWBMode->addItem("Sunlight");
    ui->comboBox_AWBMode->addItem("Cloudy");
    ui->comboBox_AWBMode->addItem("Shade");
    ui->comboBox_AWBMode->addItem("Tungsteen");
    ui->comboBox_AWBMode->addItem("Fluorescent");
    ui->comboBox_AWBMode->addItem("Incandescent");
    ui->comboBox_AWBMode->addItem("Flash");
    ui->comboBox_AWBMode->addItem("Horizon");

    // ComboBox Image Effect
    ui->comboBox_ImageEffect->addItem("None");
    ui->comboBox_ImageEffect->addItem("Negative");
    ui->comboBox_ImageEffect->addItem("Solarize");
    ui->comboBox_ImageEffect->addItem("Posterize");
    ui->comboBox_ImageEffect->addItem("Whiteboard");
    ui->comboBox_ImageEffect->addItem("Blackboard");
    ui->comboBox_ImageEffect->addItem("Sketch");
    ui->comboBox_ImageEffect->addItem("Denoise");
    ui->comboBox_ImageEffect->addItem("Emboss");
    ui->comboBox_ImageEffect->addItem("Oilpaint");
    ui->comboBox_ImageEffect->addItem("Hatch");
    ui->comboBox_ImageEffect->addItem("Gpen");
    ui->comboBox_ImageEffect->addItem("Pastel");
    ui->comboBox_ImageEffect->addItem("Watercolour");
    ui->comboBox_ImageEffect->addItem("Film");
    ui->comboBox_ImageEffect->addItem("Blur");
    ui->comboBox_ImageEffect->addItem("Saturation");
    ui->comboBox_ImageEffect->addItem("Colourswap");
    ui->comboBox_ImageEffect->addItem("Washedout");
    ui->comboBox_ImageEffect->addItem("Posterise");
    ui->comboBox_ImageEffect->addItem("Colourpoint");
    ui->comboBox_ImageEffect->addItem("Colourbalance");
    ui->comboBox_ImageEffect->addItem("Cartoon");

    // ComboBox Metering Mode
    ui->comboBox_MeteringMode->addItem("Average");
    ui->comboBox_MeteringMode->addItem("Spot");
    ui->comboBox_MeteringMode->addItem("Backlist");
    ui->comboBox_MeteringMode->addItem("Matrix");

    // ComboBox H264 Profile
    ui->comboBox_H264Profile->addItem("High");
    ui->comboBox_H264Profile->addItem("Main");
    ui->comboBox_H264Profile->addItem("Base");

    // ComboBox Exposure Mode
    ui->comboBox_ExposureMode->addItem("Off");
    ui->comboBox_ExposureMode->addItem("Auto");
    ui->comboBox_ExposureMode->addItem("Night");
    ui->comboBox_ExposureMode->addItem("Nightpreview");
    ui->comboBox_ExposureMode->addItem("Backlight");
    ui->comboBox_ExposureMode->addItem("Spotlight");
    ui->comboBox_ExposureMode->addItem("Sports");
    ui->comboBox_ExposureMode->addItem("Snow");
    ui->comboBox_ExposureMode->addItem("Beach");
    ui->comboBox_ExposureMode->addItem("Verylong");
    ui->comboBox_ExposureMode->addItem("Fixedfps");
    ui->comboBox_ExposureMode->addItem("Antishake");
    ui->comboBox_ExposureMode->addItem("Fireworks");

    // ComboBox Image Rotation
    ui->comboBox_ImageRotation->addItem("0");
    ui->comboBox_ImageRotation->addItem("90");
    ui->comboBox_ImageRotation->addItem("180");
    ui->comboBox_ImageRotation->addItem("270");

    log("client", "All default values have been applied.");

}

QString MainWindow::generateRemoteGStreamerCommand()
{
    // Server command
//    /usr/bin/gst-launch-1.0 rpicamsrc
//    do-timestamp=false
//            bitrate=5120000
//            preview=false
//            hflip=true
//            vflip=true
//            video-stabilisation=false
//            sharpness=0
//            contrast=0
//            brightness=50
//            saturation=0
//            iso=0
//            rotation=0 roi-x=0 roi-y=0 roi-w=1 roi-h=1
//            awb-mode=off metering-mode=average
//            image-effect=none ! "video/x-h264,profile=high,width=1920,height=1080,framerate=30/1" !
//            h264parse ! tee name=splitter splitter. !
//            queue max-size-bytes=10000000 ! rtph264pay pt=96 config-interval=1 !
//            udpsink port=5000 host=192.168.0.100 sync=false splitter. !
//            queue ! h264parse ! mpegtsmux ! filesink location=/home/pi/streamer/record_TX_1920x1080_30fps_5000kbps_20150819_145432.ts > /dev/null 2>/dev/null &


// Client command
//    -v udpsrc port=5000 caps="application/x-rtp,media=(string)video,clock-rate=(int)90000,encoding-name=(string)H264"
//    ! rtph264depay ! tee name=splitter splitter.
//    ! queue ! avdec_h264 ! videoconvert ! autovideosink sync=false async=false splitter.
//    ! queue ! mpegtsmux ! filesink location=d:/videos/record_RX_1920x1080_30fps_5000kbps_20150819_145433.ts

    //QString fileNameDate = QDate::toString("yyyyMMdd") + QTime::toString("HHmmss");

    QDateTime dateTime = dateTime.currentDateTime();
    QString RemoteRecordFilename = ui->lineEdit_RemoteRecordingPath->text()
            + "record_TX_" + ui->lineEdit_ResolutionWidth->text()
            + "x" + ui->lineEdit_ResolutionHeight->text()
            + "_" + ui->spinBox_FPS->text()
            + "fps_" + ui->spinBox_Bitrate->text()
            + "kbps_" + dateTime.toString("yyyyMMddHHmmss")
            + ".ts";


//                RemoteGStreamerCommand = "/usr/bin/gst-launch-1.0 rpicamsrc do-timestamp=" + doTimestamps
//                + " bitrate=" + Bitrate + " preview=false hflip=" + Hflip + " vflip=" + Vflip + " video-stabilisation=" + VideoStabilisation
//                + " sharpness=" + num_Sharpness.Value.ToString() + " contrast=" + num_Contrast.Value.ToString()
//                + " brightness=" + num_Brightness.Value.ToString() + " saturation=" + num_Saturation.Value.ToString()
//                + " iso=" + num_ISO.Value.ToString()
//                + " rotation=" + cmb_ImageRotation.SelectedItem.ToString() + " roi-x=" + txt_ROIx.Text
//                + " roi-y=" + txt_ROIy.Text + " roi-w=" + txt_ROIwidth.Text + " roi-h=" + txt_ROIheight.Text
//                + " awb-mode=" + cmb_AWBMode.SelectedItem.ToString().ToLower()
//                + " metering-mode=" + cmb_MeteringMode.SelectedItem.ToString().ToLower() + " image-effect=" + cmb_ImageEffect.SelectedItem.ToString().ToLower()
//                + " ! \"video/x-h264,profile=" + cmb_H264Profile.SelectedItem.ToString().ToLower() + ",width=" + txt_ResolutionWidth.Text
//                + ",height=" + txt_ResolutionHeight.Text + ",framerate=" + num_FPS.Value.ToString() + "/1\" ! h264parse "
//                + "! tee name=splitter splitter. ! queue max-size-bytes=10000000 ! rtph264pay pt=96 config-interval=1 "
//                + "! udpsink port=" + txt_StreamingPort.Text + " host=" + txt_StreamingDestination.Text
//                + " sync=" + RemoteSync + " splitter. ! queue ! h264parse ! mpegtsmux "
//                + "! filesink location=" + RemoteRecordFilename + " > /dev/null 2>/dev/null &"


    QString doTimestamps = "false";
    QString remoteRecording = "false";
    QString enableMulticast = "false";
    QString horizontalFlip = "false";
    QString verticalFlip = "false";
    QString videoFrameSync = "false";
    QString videoStabilisation = "false";
    QString localVideoFrameSync = "false";
    QString asynchronousFrameSync = "false";
    QString forceAspectRatio = "false";

    if(ui->checkBox_DoTimestamps->isChecked())
    {
        doTimestamps = "true";
    }

    if(ui->checkBox_RemoteRecording->isChecked())
    {
        remoteRecording = "true";
    }

    if(ui->checkBox_EnableMulticast->isChecked())
    {
        enableMulticast = "true";
    }

    if(ui->checkBox_HorizontalFlip->isChecked())
    {
        horizontalFlip = "true";
    }

    if(ui->checkBox_VerticalFlip->isChecked())
    {
        verticalFlip = "true";
    }

    if(ui->checkBox_VideoFrameSync->isChecked())
    {
        videoFrameSync = "true";
    }

    if(ui->checkBox_VideoStabilisation->isChecked())
    {
        videoStabilisation = "true";
    }

    if(ui->checkBox_LocalVideoFrameSync->isChecked())
    {
        localVideoFrameSync = "true";
    }

    if(ui->checkBox_AsynchronousFrameSync->isChecked())
    {
        asynchronousFrameSync = "true";
    }

    if(ui->checkBox_ForceAspectRatio->isChecked())
    {
        forceAspectRatio = "true";
    }

    uint bitRate = ui->spinBox_Bitrate->text().toUInt() * 1024;

    QString finalBitrate = QString::number(bitRate);


    QString RemoteGStreamerCommand = "/usr/bin/gst-launch-1.0 rpicamsrc do-timestamp=" + doTimestamps
            + " bitrate=" + finalBitrate
            + " preview=false"
            + " hflip=" + horizontalFlip
            + " vflip=" + verticalFlip
            + " video-stabilisation=" + videoStabilisation
            + " sharpness=" + ui->spinBox_Sharpness->text()
            + " contrast=" + ui->spinBox_Contrast->text()
            + " brightness=" + ui->spinBox_Brightness->text()
            + " saturation=" + ui->spinBox_Saturation->text()
            + " iso=" + ui->spinBox_ISO->text()
            + " rotation=" + ui->comboBox_ImageRotation->itemText(ui->comboBox_ImageRotation->currentIndex())
            + " roi-x=" + ui->lineEdit_RegionX->text()
            + " roi-y=" + ui->lineEdit_RegionY->text()
            + " roi-w=" + ui->lineEdit_RegionWidth->text()
            + " roi-h=" + ui->lineEdit_RegionHeight->text()
            + " awb-mode=" + ui->comboBox_AWBMode->itemText(ui->comboBox_AWBMode->currentIndex()).toLower()
            + " metering-mode=" + ui->comboBox_MeteringMode->itemText(ui->comboBox_MeteringMode->currentIndex()).toLower()
            + " image-effect=" + ui->comboBox_ImageEffect->itemText(ui->comboBox_ImageEffect->currentIndex()).toLower()
            + " ! \"video/x-h264,profile=" + ui->comboBox_H264Profile->itemText(ui->comboBox_H264Profile->currentIndex()).toLower()
            + ",width=" + ui->lineEdit_ResolutionWidth->text()
            + ",height=" + ui->lineEdit_ResolutionHeight->text()
            + ",framerate=" + ui->spinBox_FPS->text() + "/1\" ! h264parse "
            + "! tee name=splitter splitter. ! queue max-size-bytes=10000000 ! rtph264pay pt=96 config-interval=1 "
            + "! udpsink port=" + ui->spinBox_DestinationPort->text()
            + " host=" + ui->lineEdit_DestinationIp->text()
            + " sync=" + videoFrameSync
            + " splitter. ! queue ! h264parse ! mpegtsmux "
            + "! filesink location=" + RemoteRecordFilename
            + " > /dev/null 2>/dev/null &";

    return RemoteGStreamerCommand;
}

QString MainWindow::generateLocalGStreamerCommand()
{

// Client command
//    -v udpsrc port=5000 caps="application/x-rtp,media=(string)video,clock-rate=(int)90000,encoding-name=(string)H264"
//    ! rtph264depay ! tee name=splitter splitter.
//    ! queue ! avdec_h264 ! videoconvert ! autovideosink sync=false async=false splitter.
//    ! queue ! mpegtsmux ! filesink location=d:/videos/record_RX_1920x1080_30fps_5000kbps_20150819_145433.ts

    QDateTime dateTime = dateTime.currentDateTime();
    QString LocalRecordFilename = ui->lineEdit_LocalRecordingPath->text()
            + "record_RX_" + ui->lineEdit_ResolutionWidth->text()
            + "x" + ui->lineEdit_ResolutionHeight->text()
            + "_" + ui->spinBox_FPS->text()
            + "fps_" + ui->spinBox_Bitrate->text()
            + "kbps_" + dateTime.toString("yyyyMMddHHmmss")
            + ".ts";

    QString localVideoFrameSync = "false";
    QString asynchronousFrameSync = "false";

    if(ui->checkBox_LocalVideoFrameSync->isChecked())
    {
        localVideoFrameSync = "true";
    }

    if(ui->checkBox_AsynchronousFrameSync->isChecked())
    {
        asynchronousFrameSync = "true";
    }

    QString LocalGStreamerCommand = "gst-launch-1.0 -v udpsrc port=" + ui->spinBox_DestinationPort->text()
    + " caps=\"application/x-rtp,media=(string)video,clock-rate=(int)90000,encoding-name=(string)H264\""
    + " ! rtph264depay ! tee name=splitter splitter. ! queue ! avdec_h264 ! videoconvert"
    + " ! autovideosink sync=" + localVideoFrameSync + " async=" + asynchronousFrameSync + " splitter. ! queue ! mpegtsmux"
    + " ! filesink location=" + LocalRecordFilename;


    return LocalGStreamerCommand;
}

bool MainWindow::checkIfProcessIsRunning(QString process)
{

    QByteArray resultGSTCheck;
    QProcess cmdGSTCheck;
    QString psDump;

    // CHECK IF COMMAND IS ALREADY RUNNING
    //cmdGSTCheck.start("ps -ax\n");
    cmdGSTCheck.start("/bin/bash", QStringList() << "-c" << "ps -ax | grep " + process);

    cmdGSTCheck.waitForStarted();

    while(cmdGSTCheck.state() != QProcess::NotRunning)
    {
        cmdGSTCheck.waitForReadyRead();
        resultGSTCheck = cmdGSTCheck.readAll();
        //qDebug() << resultGSTCheck;
        cmdGSTCheck.waitForFinished(-1);
    }

    psDump = QString::fromUtf8(resultGSTCheck);

    if(psDump.contains(process, Qt::CaseInsensitive))
    {
        qDebug() << process + " is already running... taking actions..." << endl;
        killLocalCommand();
        qDebug() << "Process should be killed." << endl;
        return true;
    }
    else
    {
        qDebug() << "The process is not already running. ()" << endl;
        return false;
    }

}

bool MainWindow::runLocalCommand(QString command)
{

    QByteArray result;
    QProcess cmd;

    checkIfProcessIsRunning("gst-launch-1.0");

    //cmd.setReadChannel(QProcess::StandardOutput);
    //cmd.setProcessChannelMode(QProcess::MergedChannels);
    //cmd->setWorkingDirectory("/Users/fredericlandry");

    //cmd.start("touch /Users/fredericlandry/testfred33333113213123121111113344.txt\n");
    //cmd.start("gst-inspect-1.0 udpsink\n");
    //cmd.startDetached(command + "\n");
    cmd.startDetached("/bin/bash", QStringList() << "-c" << command);

    cmd.waitForStarted();

    log("client", "Running local command. (" + command + ")");

    cmd.closeWriteChannel();   //done Writing

    // exit calling application on called application start
    //connect(process, SIGNAL(started()), this, SLOT(Exit()));
    // receive errors
    //connect(process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(error(QProcess::ProcessError)));

    while(cmd.state() != QProcess::NotRunning)
    {
        cmd.waitForReadyRead();
        result = cmd.readAll();
        //qDebug() << result << endl;
        cmd.waitForFinished(-1);
    }

    //qDebug() << endl << "---end-launch---" << endl;

    return true;

}

bool MainWindow::killLocalCommand()
{

    QByteArray result;
    QProcess cmd;

    //cmd.setReadChannel(QProcess::StandardOutput);
    //cmd.setProcessChannelMode(QProcess::MergedChannels);
    //cmd->setWorkingDirectory("/Users/fredericlandry");

    //cmd.start("touch /Users/fredericlandry/testfred33333113213123121111113344.txt\n");
    //cmd.start("gst-inspect-1.0 udpsink\n");

    qDebug() << "Killing process...!" << endl;

    //cmd.startDetached("pkill gst-launch-1.0\n");
    cmd.start("/bin/bash", QStringList() << "-c" << "pkill gst-launch-1.0");

    log("client", "Killing local command. (pkill gst-launch-1.0\n)");

    while(cmd.state() != QProcess::NotRunning)
    {
        cmd.waitForReadyRead();
        result = cmd.readAll();
        //qDebug() << result;
        cmd.waitForFinished(-1);
    }

    //qDebug() << endl << "---end-kill---" << endl;

    return true;

}

void MainWindow::log(QString where, QString data)
{
    QDateTime dateTime = dateTime.currentDateTime();

    if(where == "server")
    {
        ui->textEdit_ServerLog->insertPlainText(dateTime.toString("[HH:mm:ss] ") + data + "\r\n");
        ui->textEdit_ServerLog->verticalScrollBar()->setValue(ui->textEdit_ServerLog->verticalScrollBar()->maximum());
    }
    else if (where == "client")
    {
        ui->textEdit_ClientLog->insertPlainText(dateTime.toString("[HH:mm:ss] ") + data + "\r\n");
        ui->textEdit_ClientLog->verticalScrollBar()->setValue(ui->textEdit_ClientLog->verticalScrollBar()->maximum());
    }
}

void MainWindow::on_pushButton_Mute_clicked()
{
    qDebug("Bouton Mute clicked");
    log("server", generateRemoteGStreamerCommand());
    log("client", generateLocalGStreamerCommand());

//    livePlayer.setVolume(3);

    qDebug() << "livePlayer isAudioAvailable: " << livePlayer.isAudioAvailable();
    qDebug() << "livePlayer bufferStatus: " << livePlayer.bufferStatus();
    qDebug() << "livePlayer duration: " << livePlayer.duration();
    qDebug() << "livePlayer error: " << livePlayer.error();
    qDebug() << "livePlayer mediaStatus: " << livePlayer.mediaStatus();
    qDebug() << "livePlayer playbackRate: " << livePlayer.playbackRate();
    qDebug() << "livePlayer playlist: " << livePlayer.playlist();
    qDebug() << "livePlayer position: " << livePlayer.position();
    qDebug() << "livePlayer state: " << livePlayer.state();
    qDebug() << "livePlayer volume: " << livePlayer.volume();
}

void MainWindow::on_pushButton_Connect_clicked()
{
    s.doConnect(ui->lineEdit_ServerIp->text(), ui->spinBox_ServerPort->text().toUInt());
    log("server", "Server connect command sent.");
}

void MainWindow::on_pushButton_Disconnect_clicked()
{
    QString disconnect = "DISCONNECT";
    s.writeData(disconnect.toUtf8());
    s.disconnect();
    log("server", "Server disconnect command sent. (" + disconnect + ")");
}

void MainWindow::on_pushButton_Shutdown_clicked()
{
    QString shutdown = "SHUTDOWN";
    s.writeData(shutdown.toUtf8());
    log("server", "Server shutdown command sent. (" + shutdown + ")");
}

void MainWindow::on_pushButton_StartStreaming_clicked()
{

    //runLocalCommand(generateLocalGStreamerCommand());


    //QThread::sleep(1);

    QString startStreaming = "STREAMER: " + generateRemoteGStreamerCommand();
    s.writeData(startStreaming.toUtf8());

    //QThread::sleep(2);

    log("server", "Server start streaming command sent. (" + startStreaming + ")");



}

void MainWindow::on_pushButton_StopStreaming_clicked()
{

    killLocalCommand();

    //Thread.Sleep(1000);

    //sendCommandToServer("STOP");

    //btn_StartStreaming.Enabled = true;
    //btn_StopStreaming.Enabled = false;

    //logClient("Streaming stopped.");

    //QString stopStreaming = "STOP";
    //s.writeData(stopStreaming.toUtf8());

    //log("server", "Server stop streaming command sent. (" + stopStreaming + ")");

}
