#ifndef SCDSERVERTHREAD_H
#define SCDSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>

#include "msgserver.h"

class SCDMsgServerThread : public QThread
{
  Q_OBJECT

  public:

    explicit SCDMsgServerThread(int socketDescriptor, SCDMsgCenter *mc = 0, QObject *parent = 0);

    ~SCDMsgServerThread();

    void run(); // thread execution

  signals:

    void error(QTcpSocket::SocketError SocketError);

  public slots:


  private:

    int SocketDescriptor; // descriptor(handle) of current socket

    SCDMsgCenter *mc;

    QTcpSocket *Socket;   // socket of current connection
};

#endif // SCDSERVERTHREAD_H
