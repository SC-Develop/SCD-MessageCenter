#ifndef SCDMSGSERVER_H
#define SCDMSGSERVER_H

#include <QTcpServer>

#include <msgcenter.h>

class SCDMsgServer : public QTcpServer
{
    Q_OBJECT

  private:

    SCDMsgCenter *mc;

    int  Port;
    int Status=0;

  public:

    explicit SCDMsgServer(int port = 33331, bool verbose=true, QString logFile="msgserver.log", SCDMsgCenter *msgCnt = 0, QObject *parent = 0);

    bool start(); // Start tcp server for incoming connections
    void stop();
    bool status() {return Status;}

    bool Verbose;

    QString LogErrorFile;

    SCDMsgCenter *messageCenter() {return mc;}

  signals:

  public slots:

  protected:

     void incomingConnection(qintptr SocketDescriptor);
};

#endif // SCDMSGSERVER_H
