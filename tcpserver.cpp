#include "tcpserver.h"

TCPServer::TCPServer(QObject *parent) : QObject(parent)
{
    m_tcpServer = new QTcpServer(this);
    if (!m_tcpServer->listen(QHostAddress::Any, m_port))
    {
        qDebug()<< "TCP Server create error:" << m_tcpServer->errorString();
    }
    else
    {
        connect(m_tcpServer, &QTcpServer::newConnection, this, &TCPServer::newConnection);
        qDebug() << "Tcp Server init successful";
    }
    m_isOnline = false;
}

void TCPServer::newConnection()
{
    qDebug() << "Client connected";
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    // 用户连接进来后，connect 各种数据信号
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &TCPServer::socketGetData);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &TCPServer::socketDisconnect);
    m_isOnline = true;
}

void TCPServer::socketDisconnect()
{
    qDebug() << "Client Dissconnected";
    // 断开所有连接
    disconnect(m_tcpSocket, 0, this, 0);
    m_tcpSocket = nullptr;
    m_isOnline = false;
}

void TCPServer::socketGetData()
{
    QByteArray buffer;
    buffer = m_tcpSocket->readAll();
    if (!buffer.isEmpty())
    {
        QString dataStr = buffer;
        qDebug() << "Get New data:" << dataStr;
    }
}

void TCPServer::sendNewData(QString value)
{
    if (m_isOnline)
    {
        m_tcpSocket->write(value.toUtf8());
    }
}



