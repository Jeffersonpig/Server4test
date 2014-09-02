#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

public slots:
    void startServer();
    void closeServer();
    void getNewConnection();
    void getSocketError();
    void displayInfo(const QString& info);

private:
    Ui::ServerWidget *ui;
    QTcpServer *socketServer;
};

#endif // SERVERWIDGET_H
