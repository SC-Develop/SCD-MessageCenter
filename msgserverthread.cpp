/**
 * @class  SCDMsgServerThread - https://github.com/SC-Develop/SCD_MC
 *
 * @author Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com - https://github.com/SC-Develop/
 *
 * @brief  Message Center Server Thread Managent
 *
 *         This is a part of SCD Message Center QT Class Library
 *
 *         This is the Message Center Server Thread Management of a realtime messaging/commands system for exchange of
 *         inter-process messages/commands based on Tcp Socket
 *
 *         This file must be distribuited with files:
 *
 *            - msgcenter.cpp,
 *            - msgcenter.h,
 *            - msgserver.h,
 *            - msgserver.cpp,
 *            - msgthreadhandler.h
 *            - msgthreadhandler.cpp
 *
*/

#include "QObject"
#include "msgserverthread.h"
#include "msgserver.h"
#include "msgthreadhandler.h"

/**
 * @brief SCDMsgServerThread::SCDMsgServerThread
 * @param Id
 * @param parent
 */
SCDMsgServerThread::SCDMsgServerThread(int socketDescriptor, SCDMsgCenter *mc, QObject *parent) :
    QThread(parent), SocketDescriptor(socketDescriptor), mc(mc)
{

}

/**
 * @brief SCDMsgServerThread::~SCDMsgServerThread
 */
SCDMsgServerThread::~SCDMsgServerThread()
{

}

/**
 * @brief SCDMsgServerThread::run starts remote client connection thread
 */
void SCDMsgServerThread::run()
{
   SCDMsgThreadHandler *tev = new SCDMsgThreadHandler(SocketDescriptor, mc); // Thread handler class live into thread

   if (tev->start()) // start socket connection and set the socket signal handler slot
   {
      if (mc)
      {
         mc->addClient(SocketDescriptor); // register client to message center. client can receive message from application message senders
      }

      exec(); //  start thared event loop e do not return until quit or exit is not called (on socket disconnect, exits from event loop)

      if (mc) // remove client from message center client list
      {
         mc->removeClient(SocketDescriptor);
      }
   }

   delete tev; // delete thread event loop object and associated socket
}
