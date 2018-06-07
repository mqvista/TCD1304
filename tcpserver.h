#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);

signals:

public slots:
    void newConnection();
    void socketDisconnect();
    void socketGetData();
    void sendNewData(QString value);

private:
    QTcpServer *m_tcpServer;
    quint16 m_port = 20000;
    QTcpSocket *m_tcpSocket;
    bool m_isOnline;

};

#endif // TCPSERVER_H
