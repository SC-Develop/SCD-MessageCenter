/**
 * @class  SCDMsgThreadHandler - https://github.com/sc-develop/SCD_MC
 *
 * @author Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com - https://github.com/sc-develop/
 *
 * @brief  Message Center Server: Thread Signal Processing
 *
 *         This is a part of SCD Message Center QT Class Library a realtime messaging/commands system for exchange of
 *         inter-process messages/commands based on Tcp Socket
 *
 *         This file must be distribuited with files:
 *
 *            - msgcenter.cpp,
 *            - msgcenter.h,
 *            - msgserver.h,
 *            - msgserver.cpp,
 *            - msgserverthread.h
 *            - msgserverthread.cpp
 *
*/

#include "QObject"
#include "msgserverthread.h"
#include "msgthreadhandler.h"

#define echo QTextStream(stdout) << "\n" <<

/**
 * @brief SCDMsgThreadHandler::SCDMsgThreadHandler
 * @param Id
 * @param parent
 */
SCDMsgThreadHandler::SCDMsgThreadHandler(int socketDescriptor, SCDMsgServerThread *msgServerThread) :
    SocketDescriptor(socketDescriptor),
    thread(msgServerThread)
{
   mc = msgServerThread->msgServer()->messageCenter();
}

/**
 * @brief SCDMsgThreadHandler::~SCDMsgThreadHandler
 */
SCDMsgThreadHandler::~SCDMsgThreadHandler()
{
   if (Socket)
   {
      delete Socket;
   }
}

/**
 * @brief SCDMsgThreadHandler::start
 * @return
 */
int SCDMsgThreadHandler::start()
{
   Socket = new QTcpSocket();                                          // create the connection socket object

   connect(Socket,SIGNAL(readyRead()),this,SLOT(readyRead()));         // set event for reading data from socket when avalaible
   connect(Socket,SIGNAL(disconnected()),this,SLOT(disconnected()));   // set event for closing connection;

   if (!Socket->setSocketDescriptor(SocketDescriptor)) // Check for socket error
   {
      echo "Socket connection error: " << Socket->error();;

      return 0;
   }

   connect(mc,SIGNAL(messageToClient_signal(QString,int)),this,SLOT(receiveFromMsgCenter(QString,int))); // set the slot to receive message from messge center

   return 1;
}

/**
 * @brief SCDMsgThreadHandler::readyRead
 */
void SCDMsgThreadHandler::readyRead()
{
   QByteArray Buffer;

   Buffer = Socket->readAll(); // Reading incoming data

   mc->sendCommand(Buffer,SocketDescriptor); // send a client command to message center
}

/**
 * @brief SCDMsgThreadHandler::disconnected
 */
void SCDMsgThreadHandler::disconnected()
{
   thread->quit();
}

/**
 * @brief SCDMsgThreadHandler::receiveFromMsgCenter receive a message form message center and writes the message into destination socket connection
 *
 * @param msg
 * @param toSocketDescriptor
 */
void SCDMsgThreadHandler::receiveFromMsgCenter(QString msg, int toSocketDescriptor)
{
   if (toSocketDescriptor==SocketDescriptor)
   {
      if (msg.trimmed()=="exit")
      {
         Socket->close();
      }
      else
      {
         Socket->write(msg.toLatin1());
         Socket->flush();
         Socket->waitForBytesWritten();
      }
   }
}

