/**
 * @class  SCDMsgServer - https://github.com/sc-develop/SCD-MC
 *
 * @author Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com - https://github.com/sc-develop/
 *
 * @brief SCD Message Center Server: Interprocess messaging comunications server
 *
 *        This is a part of SCD Message Center QT Class Library, a realtime messaging/commands system for exchange
 *        of inter-process messages/commands based on Tcp Socket
 *
 *        This file must be distribuited with files:
 *
 *           - msgcenter.cpp,
 *           - msgcenter.h,
 *           - msgserverthread.h,
 *           - msgserverthread.cpp,
 *           - msgthreadhandler.h
 *           - msgthreadhandler.cpp
 *
*/

#include <QString>

#include "msgserver.h"
#include "msgserverthread.h"

/**
 * @brief SCDMsgServer::SCDMsgServer
 * @param parent
 * @param mc
 */
SCDMsgServer::SCDMsgServer(int port, bool verbose, QString logFile, SCDMsgCenter *msgCnt, QObject *parent) : QTcpServer(parent), mc(msgCnt)
{
   Verbose = verbose;

   if (!msgCnt) // if not provided external message center create own message center
   {
      mc = new SCDMsgCenter();
   }

   Port = port;

   if (logFile.isEmpty())
   {
      logFile = "msgserver.log";
   }

   LogErrorFile = logFile;
}

/**
 * @brief SCDMsgServer::StartServer
 */
bool SCDMsgServer::start()
{
   Status = listen(QHostAddress::Any,Port);

   if (Status)    // listen for incoming connections
   {
      QTextStream(stdout) << "\nMessage Center Server is listening on port: " << Port << "" << " for incoming connections..." << endl;
   }
   else
   {
      QTextStream(stdout) << "Could not start the Message Center Server on port: " << Port  << " => " << this->errorString();
   }

   return Status;
}

/**
 * @brief SCDMsgServer::StopServer
 */
void SCDMsgServer::stop()
{
   if (isListening())
   {
      close();
   }
}

/**
 * @brief SCDMsgServer::incomingConnection
 * @param SocketDescriptor
 */
void SCDMsgServer::incomingConnection(qintptr SocketDescriptor)
{
   SCDMsgServerThread *SockThread = new SCDMsgServerThread(SocketDescriptor,this);  // Create a thread for handling client connections passing a socket descrirptor

   connect(SockThread,SIGNAL(finished()),SockThread,SLOT(deleteLater()));     // delete thread when finisced()

   SockThread->start(); // start the thread;
}
