#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QNetworkDatagram>


namespace Ui {
class MainWindow;
}

class ServerUdp : public QObject
{
    Q_OBJECT
    public:
        ServerUdp();
        ~ServerUdp();
    public slots:

        //void removeconnection();
        void processPendingDatagrams();
        void readPendingDatagrams();
    signals:
        void resultReady(const QString &string);
        void result_ready(const QString &stringText);
    private:
        QUdpSocket * udpSocketServer;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void on_textBrowser_windowIconTextChanged(const QString &iconText);
        void on_textBrowser_2_windowIconTextChanged(const QString &text);
    private:
        Ui::MainWindow *ui;
        ServerUdp * udpServer;
};

#endif // MAINWINDOW_H
