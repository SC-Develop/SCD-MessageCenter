#ifndef SCDMESSAGETHREADHANDLER_H
#define SCDMESSAGETHREADHANDLER_H

#include <QThread>
#include <QTcpSocket>

#include "msgserverthread.h"

class SCDMsgThreadHandler: public QObject
{
    Q_OBJECT

  public:

    explicit SCDMsgThreadHandler(int socketDescriptor,  SCDMsgServerThread *msgServerThread);

    ~SCDMsgThreadHandler();

    int start();

  signals:

    void error(QTcpSocket::SocketError SocketError);

  public slots:

    void readyRead();
    void disconnected();
    void receiveFromMsgCenter(QString msg, int toSocketDescriptor);

  private:

    int SocketDescriptor;     // descriptor(handle) of current socket

    SCDMsgServerThread *thread;

    SCDMsgCenter *mc;

    QTcpSocket *Socket;   // socket of current connection
};

#endif // SCDMESSAGETHREADHANDLER_H
