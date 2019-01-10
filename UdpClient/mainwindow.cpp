#include "mainwindow.h"
#include "ui_mainwindow.h"


#define SEND "Wysłane"
#define SEND_ERR "Połączenie: Błąd"
#define SEND_OK "Połączenie: Ok"

/* Client
 * Nadanie danych do serwera - wpisanych w polu tekstowym
 * Obsługiwany protokuł; UDP
 * Datagramy
 * Interaktywność
 */


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->installEventFilter(this);

};

MainWindow::~MainWindow()
{
    delete ui;
}

ClientUdp::ClientUdp()
{
    udpSocketClient = new QUdpSocket(this);
    udpSocketClient->connectToHost(QHostAddress::LocalHost, 1200);
    
}

ClientUdp::~ClientUdp()
{
    udpSocketClient->close();
}

void ClientUdp::processPendingDatagrams(QString &string)
{
    
    QByteArray datagramByts;
   
    datagramByts.append(string);

    udpSocketClient->writeDatagram(datagramByts, QHostAddress::LocalHost, 1200);
    resultReady(SEND);
}


void ClientUdp::removeConnection()
{

}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
    qDebug("Program ClientUDP został zakmnięty poprawnie");
}

//Metoda odpowiedzialna za wpisywanie tekstu
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    
}



/* metoda - sygnał; resultReady
 * przekazanie argumenu getString do odpowiedniego slotu
 * w serwerze
 * lineEdit->text() - pobranie wpisanej wartości z pola tekstowego
 * odwołanie "przycisku" do wcześniej zdefiniowanej metody lineEdit()
 */

void MainWindow::on_pushButton_3_clicked()
{
    QString getString;

    udpClient = new ClientUdp();
    connect(udpClient, &ClientUdp::resultReady, this, &MainWindow::on_textBrowser_windowIconTextChanged);

    getString = ui->lineEdit->text();
    udpClient->processPendingDatagrams(getString);
}

void MainWindow::on_textBrowser_windowIconTextChanged(const QString &iconText)
{
    ui->textBrowser->append(iconText);
}

bool MainWindow::eventFilter(QObject * obj, QEvent * event)
{
    if(obj == ui->lineEdit && event->type() == Qt::Key_Enter)
    {
        QKeyEvent * event;
		if (Qt::Key_Enter == event->key())
			return; 
    }
}

void MainWindow::on_lineEdit_returnPressed()
{
    udpClient = new ClientUdp();
    connect(udpClient, &ClientUdp::resultReady, this, &MainWindow::on_textBrowser_windowIconTextChanged);

    qDebug() << "Enter";
    qDebug() << Qt::Key_Enter;


    QString getString;
    getString = ui->lineEdit->text();
    udpClient->processPendingDatagrams(getString);

}



