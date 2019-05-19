#ifndef SCDSERVERTHREAD_H
#define SCDSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>

#include "msgserver.h"

class SCDMsgServerThread : public QThread
{
  Q_OBJECT

  public:

    explicit SCDMsgServerThread(int socketDescriptor, SCDMsgServer *msgServer);

    ~SCDMsgServerThread();

    void run(); // thread execution

    SCDMsgServer *msgServer() {return srv;}

  signals:

    void error(QTcpSocket::SocketError SocketError);

  public slots:


  private:

    QTcpSocket *Socket;   // socket of current connection

    int SocketDescriptor; // descriptor(handle) of current socket

    SCDMsgServer *srv;
};

#endif // SCDSERVERTHREAD_H
