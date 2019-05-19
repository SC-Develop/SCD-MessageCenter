#ifndef DEMOSERVERTHREAD_H
#define DEMOSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <msgcenter.h>

class DemoServerThread : public QThread
{
    Q_OBJECT

    public:

      explicit DemoServerThread(QObject *parent = 0, qintptr socketDescriptor=-1, SCDMsgCenter *mc=0);

      void run(); // thread execution

      qintptr getSocketDescriptor() {return socketDescriptor;}

    signals:

      void error(QTcpSocket::SocketError SocketError);

    private:

      qintptr socketDescriptor; // descriptor(handle) of current socket

      SCDMsgCenter *mc;
};

class SignalsHandler : public QObject
{
    Q_OBJECT

    public:

      explicit SignalsHandler(QTcpSocket *socket, SCDMsgCenter *mc);

    signals:

    public slots:

      void readyRead();
      void disconnected();
      void onClientCommand(QString cmd, QString sender);

    private:

      QTcpSocket *socket;   // current connection socket

      SCDMsgCenter *mc;
};


#endif // DEMOSERVERTHREAD_H
