#ifndef DEMOSERVER_H
#define DEMOSERVER_H

#include <QTcpServer>
#include <msgcenter.h>

class DemoServer : public QTcpServer
{
   Q_OBJECT

   private:

     int port;

     SCDMsgCenter *mc;

   public:

     explicit DemoServer(QObject *parent = 0, int port=123456, SCDMsgCenter *mc = 0);

     void start(); // Start tcp server for incoming connections

   signals:

   public slots:

     void threadDestroyed(QObject *obj);

   protected:

     void incomingConnection(qintptr SocketDescriptor);

};

#endif // DEMOSERVER_H
