#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QKeyEvent>
#include <QEvent>


namespace Ui {
class MainWindow;
}

class ClientUdp : public QMainWindow
{
    Q_OBJECT
    public:
        ClientUdp();
        ~ClientUdp();
    public slots:
        void processPendingDatagrams(QString &string);
        void removeConnection();
    signals:
        void resultReady(const QString &s);
    private:
        QUdpSocket * udpSocketClient;

};


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

protected:
        bool eventFilter(QObject *obj, QEvent * event);

    private slots:
        void on_pushButton_2_clicked();
        void on_lineEdit_textChanged(const QString &arg1);
        void on_pushButton_3_clicked();
        void on_textBrowser_windowIconTextChanged(const QString &iconText);

        void on_lineEdit_returnPressed();

signals:
        void resultReady(const QString &string);
    private:
        Ui::MainWindow *ui;
        ClientUdp * udpClient;
        QKeyEvent * event;
};
#endif // MAINWINDOW_H
