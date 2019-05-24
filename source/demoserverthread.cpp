/**
 * @class  DemoServerThread - https://github.com/sc-develop/SCD-MC
 *
 * @author Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com - https://github.com/sc-develop/
 *
 * @brief SCD Message Center Demo: Application Server Thread
 *
 *        This is a this part of SCD Message Center Demo Program
 *
*/

#include <QHostAddress>
#include "demoserverthread.h"

/**
 * @brief DemoServerThread::DemoServerThread constructor
 * @param Id
 * @param parent
 */
DemoServerThread::DemoServerThread(QObject *parent, qintptr socketDescriptor, SCDMsgCenter *mc) :
    QThread(parent),
    socketDescriptor(socketDescriptor),
    mc(mc)
{

}

/**
 * @brief DemoServerThread::run => thread main function
 */
void DemoServerThread::run()
{
   qDebug() << "Starting connection thread: " << socketDescriptor;

   QTcpSocket *socket = new QTcpSocket();                            // allocates new socket object (live into a thread memory space)

   QString sockSender = "sock." + QString::number(socketDescriptor); // set name of socket connection

   socket->setObjectName(sockSender);                                // assigan soc ket connection name to socket object

   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   mc->addSender(sockSender); // register a new sender to message center

   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   if (socket->setSocketDescriptor(socketDescriptor))  // set a socket descriptor of new allocated socket object
   {
       SignalsHandler sh(socket,mc);

       socket->write("\n\nDemo server v1.0\n\nType something: you will receive the typing echo\n\n> ");

       QString msg;

       QTextStream(&msg) << "Accepted connection from host: "
                          << socketDescriptor
                          << " Address: "
                          << socket->peerAddress().toString()
                          << " Port: "
                          << socket->peerPort();

       // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

       mc->postMessage(msg,sockSender); // post a message to message center as sockSender

       // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

       exec(); // starts event loop and waits until event loop exits
   }
   else
   {
      qDebug() << "Error: Unable to set socket descriptor " << socket->error();
   }

   delete socket; // explict socket deleting

   qDebug() << "Connection thread end: " << socketDescriptor;

   // Thread end ------------------

   QString msg = "Thread end";

   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   mc->postMessage(msg,sockSender);   // posts a message to message center as sockSender

   mc->postMessage(msg,"Server");     // posts a message to message center as "Server"

   mc->removeSender(sockSender);      // remove thread sender sockSender from message center

   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

/**
 * @brief SignalsHandler::SignalsHandler
 * @param socket
 * @param mc
 */
SignalsHandler::SignalsHandler(QTcpSocket *socket, SCDMsgCenter *mc): socket(socket),mc(mc)
{
   connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
   connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
   connect(mc,SIGNAL(commandToSender_signal(QString,QString)),this,SLOT(onClientCommand(QString,QString)));
}

/**
 * @brief SignalsHandler::readyRead read data if available
 */
void SignalsHandler::readyRead()
{
   QByteArray msg;

   msg = socket->readAll();

   QString mesg = "Receiving from socket " + QString::number(socket->socketDescriptor()) + ":" + msg;

   qDebug() << mesg;

   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   mc->postMessage(msg,socket->objectName()); // post a message to message center from socket thread

   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   msg = "\n" + msg + "\n> ";

   socket->write(msg); // echo message to application client
}

/**
 * @brief SignalsHandler::disconnected exit from event thread loop (thread end)
 */
void SignalsHandler::disconnected()
{
   qDebug() << "Client disconnected: " << socket->objectName();

   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   mc->postMessage("Client disconnected!",socket->objectName()); // post a message to message center from socket thread

   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   thread()->quit(); //exit(0); => exit from thread event loop
}

/**
 * @brief SignalsHandler::onClientCommand process client command signals
 * @param cmd
 * @param sender
 */
void SignalsHandler::onClientCommand(QString cmd, QString sender)
{
   if (sender==socket->objectName())
   {
       mc->postMessage("Command received: " + cmd,socket->objectName());
   }
}
