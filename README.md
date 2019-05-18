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
 
- The application threads register some senders into message center to self identifying. Doing this, the message center clients can request list of senders id registered to message center, and therefore can request to recive message identified by centain sender id.
- The application threads sends real-time messages identify by an registered sender id: the messages will real-time dispatched to clients which request to receiving messages from the same sender id, otherwise the message will be discarded by Message Center.

When the clients connect to message center server, they receive the  commands menu, and a command line prompt waiting for commands typing.

To receive messages from remote application theread the message center clients can:
 
request list of senders id registered to message center
request to receive message from specific sender id: the thread monitoring starts immediately and the client begins to receive messages
press enter to stop thread and return to console 
