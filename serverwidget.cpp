#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    socketServer = new QTcpServer(this);

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(startServer()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeServer()));
    ui->connectButton->setEnabled(true);
    ui->closeButton->setEnabled(false);
    ui->textEdit->setReadOnly(true);
}

ServerWidget::~ServerWidget()
{
    delete ui;
    if(socketServer->isListening())
        socketServer->close();
}

void ServerWidget::startServer()
{
    if(socketServer->isListening())
        return;
    if(ui->portEdit->text().isEmpty())
        return;
    bool ok;
    int port = ui->portEdit->text().toInt(&ok);
    if(!ok)
        return;

    QString ip = ui->ipEdit->text();
    QHostAddress add;
    if(ip.isEmpty())
        ok = socketServer->listen(QHostAddress::Any, port);
    else if(!add.setAddress(ip))
    {
        displayInfo("Invalid IP Address!");
        return;
    }
    else
        ok = socketServer->listen(add, port);

    if(!ok)
        displayInfo(socketServer->errorString());
    else
    {
        displayInfo("Listening on "+socketServer->serverAddress().toString()+":"+QString::number(socketServer->serverPort()));
        ui->connectButton->setEnabled(false);
        ui->closeButton->setEnabled(true);
        ui->ipEdit->setEnabled(false);
        ui->portEdit->setEnabled(false);
    }
}

void ServerWidget::closeServer()
{
    socketServer->close();
    while(socketServer->isListening())
        ;
    displayInfo("Socket Server Closed!");
    ui->connectButton->setEnabled(true);
    ui->closeButton->setEnabled(false);
    ui->ipEdit->setEnabled(true);
    ui->portEdit->setEnabled(true);
}

void ServerWidget::getNewConnection()
{

}

void ServerWidget::getSocketError()
{
    displayInfo(socketServer->errorString());
}

void ServerWidget::displayInfo(const QString& info)
{
    ui->textEdit->append(info);
}
