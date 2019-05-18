# SCD Message Center (QT C++ Class)

## Description
SCD Message Center is a Qt interprocess communication class.<br>
The purpose of the Message Center is to allow the exchange of messages between your own multithreading application and one or more remote control-monitoring terminals via TCP socket. <br>
This Qt class can be used also for generic interprocess communication through message exchanging.<br>
This class can be easily integrated into your application, it works very well and it's truly reliable
## What you can do with the SCD Message Center
Embedding the SCD Message Center into your own application you can do:

- Realtime monitoring  of your own application by receiving messages from each thread of your application via tcp Socket, such as log messages, variable values, event messaging etc.
- Send commands to the message center to get status information or request the execution of actions to your application threads
- send custom commands to each thread of your application for performing custom actions, such as disconnecting a client, terminating a thread, changing the value of variables, etc.

## When is it useful to use the message center?
The typical use of the message center is the realtime monitoring and remote control of a multi-threading application.<br>The message center can also be used for remote debugging in real time by controlling variable values, and modifying their value, for example. A very interesting use could be, if the host application allows it, the execution of system commands or the execution of processes.
## Message Center Architecture

Message center consists of two parts:

- The Multithreading Socket Server to accept remote client connections
- The Message center to serialize and exchange message/commands between application thread (sender) and remote clients (commands clients)
<img src="MessageCenter.png"/>
<p align="center"><b>Fig. 1 - Integration of the message center within a really realized multi-thread audio streaming server</b></p>
<p>The Message Center is a message and command exchange center.<br>
The main task of the Message Center is to serialize the requests (Commands and messages) and route its</p>

- Remote client sends comands to Message Center. 
- Message Center send it to destination thread. 
- Destination thread send a reply message to Message Center which route it to client which have requested.
- Application thread sends messages (as log message) to Message Center
- Remote client ask to Message Center to receive messages from specific theread
- Message Center routes messages from thread to remote client which have request for it

Message Center clients can send command to:

- Message Center to receive status message or command menus, 
- a thread of remote application via Message Center (for example to request to execute a specific action).

Remote clients connects to Message Center via TCP socket. You can connect to message center using a TCP socket client terminal as netcat (nc) or telnet, or your own TCP socket client application.

## How To it Work

To use Message Center you must embed message center source code it into your own multitheread application QT project, and start Message Center TCP Server on a specific port. When the message center server is started, it can accept tcp socket connection from a remote client application as nectat (nc).<br>
To allow the message center to monitoring your application, you must follow two step:
 
- The application threads register some senders into message center to self identifying. Doing this, the message center clients can request list of senders id registered to message center, and therefore can request to receive message identified by centain sender id.
- The application threads sends real-time messages identify by an registered sender id: the messages will real-time dispatched to clients which request to receiving messages from the same sender id, otherwise the messages will be discarded by Message Center.

When the clients connect to message center server, they receive the  commands menu, and a command line prompt waiting for commands typing.

To receive messages from remote application theread, the message center clients can:
 
- request list of senders id registered to message center
- request to receive message from specific sender id (if already known): the thread monitoring starts immediately and the client begins to receive messages real-time
- to stop the-realtime thread monitoring the user can press enter to return to console 

## How it works: practical example

## How to install and compile: demo example with complete project source code

- Download or clone project
- Unzip project folder on your develop folder
- Run qt creator (5.9.2 or later) and load project file ‘message-center-demo.pro’ located into folder ‘source’
- Build project and run 
- Alternatively you can make executable from cli (you must before install q5-default on your linux system):

``` 
$ cd message-center
$ ./make-release.sh
```
## Embedding Message Center into your own application source code

You must include into your own project all package files:
```
#include msgcenter.h
#include msgcenter.cpp
#include msgserver.cpp,
#include msgserver.h,
#include msgserverthread.h,
#include msgserverthread.cpp,
#include msgthreadhandler.h
#include msgthreadhandler.cpp
```
In your main() function/class declare message center server and start it (message center is sef allocated):
```
int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);
   . . .
   int mcport = 123456; 
   SCDMsgServer msgServer(mcport,true);  // declare message center server
   msgServer.start(); // start message center server: message center is self allocated by messge server   
   SCDMsgCenter *mc = msgServer.messageCenter(); // get self allocated message center pointer
   myMainClass(mc);    // pass message center pointer to application main class
   . . . 
   return a.exec();   // start application main event loop
}
```

It is strictly recommended to use the self-allocated message center, becose it is already self-connected to message center server. 

You can get it from message server by:
```
SCDMsgCenter *mc = msgServer.messageCenter(); 
```	
You can use this message center in every part of your sigle/multi-threaded application. 
You shuld passing it as a parameter to all classes or functions that will make use of it. 
You have to pass it to all the threads will use it.
```
MyThread *= new myThread(mc,...);
```
On thread main loop you should: 

- Register thread sender: 
- Use PostMessage method to send message to message center
```
void myThread::run() // qt thread main loop
{
   Qstring  threadSenderName = “Thread[1]”;

   mc->addSender(threadSenderName);        // register a new sender to message center

   QString msg = “Welcome to thread loop”;  

   mc→postMessage(msg,threadSenderName);   // send message to message center

   . . .

   exec(); // exec qt thread event loop

   QString msg = “Thread loop has finished...”;  
 
   mc→postMessage(msg,threadSenderName);   // send message to message center 
}
```

<b>Implementing execution of remote clients command</b>
Execution of remote clients command must be implemented by application developer<br>
When Message Center client send a command to specific thread, Message Center emit a signal

```
emit commandToSender_signal(command,sender_id);
```

This signal must be processed by application threads event loop.<br>

In your class that processes thread signals/event (must be live into thread space) create the slot as in demo example
```
void SignalsHandler::onClientCommand(QString cmd, QString sender)
{
   if (sender==socket->objectName())
   {
       mc->postMessage("Comand received: " + cmd,socket->objectName());
   }
}
```
<b>N.B.</b>
Only the specified destination thread (sender param) must be process the message.




