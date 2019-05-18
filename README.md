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
<p>The Message Center is a message and command exchange center.The main task of the message center is to serialize the requests (Commands and messages) and route its</p>

- Remote client sends comands to message center. 
- Message center send it to destination thread. 
- Destination thread send a reply message to message center which route it to client which have requested.
- Application thread sends messages (as log message) to message center
- Remote client ask to message center to receive messages from specific theread
- Message Center routes messages from thread to remote client which have request for it

Message Center clients can send command to:

- Message Center to receive status message or command menus, 
- a thread of remote application via Message Center (for example to request to execute a specific action).

Remote clients connects to Message Center via TCP socket. You can connect to message center using a TCP ocket client terminal as netcat (nc) or telnet, or your own TCP socket client application.
