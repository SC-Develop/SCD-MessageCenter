/**
 * @class  DemoServer - https://github.com/sc-develop/SCD-MC
 *
 * @author Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com - https://github.com/sc-develop/
 *
 * @brief SCD Message Center Demo: Application Server
 *
 *        This is a this part of SCD Message Center Demo Program
 *
*/

#include "demoserver.h"
#include "demoserverthread.h"

/**
 * @brief DemoServer::DemoServer constructor
 * @param parent
 */
DemoServer::DemoServer(QObject *parent, int port, SCDMsgCenter *mc) : QTcpServer(parent), port(port), mc(mc)
{
}

/**
 * @brief DemoServer::start start demo server
 */
void DemoServer::start()
{
   if (!this->listen(QHostAddress::Any,port))
   {
      qDebug() << "Unable to start the server on port:" << port <<  this->errorString();
   }
   else
   {
      qDebug() << "Server Listening on port:" << port << " for incoming connections..." ;

      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

      mc->addSender("server"); // register the sender "Server" on message center

      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   }
}

/**
 * @brief DemoServer::threadDestroyed handle signal threadDestroyed emit when client thared is destroyed
 * @param obj
 */
void DemoServer::threadDestroyed(QObject *obj)
{
    DemoServerThread *thd = (DemoServerThread*) obj;

    QString msg;

    QTextStream mess(&msg);

    mess  << "Thread destroyed ID: " << thd->getSocketDescriptor();

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    mc->postMessage(msg,"server"); // post a messge identified by sender id "Server" to message center

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

/**
 * @brief DemoServer::incomingConnection
 * @param SocketDescriptor
 */
void DemoServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "New socket connection: " << socketDescriptor;

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    mc->postMessage("New incoming connections ID:  " + QString::number(socketDescriptor),"server"); // post a message to message center

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    DemoServerThread *sckThread = new DemoServerThread(this,socketDescriptor,mc);

    connect(sckThread,SIGNAL(finished()),sckThread,SLOT(deleteLater()));
    connect(sckThread,SIGNAL(destroyed(QObject*)),this,SLOT(threadDestroyed(QObject*)));

    sckThread->start();
}
