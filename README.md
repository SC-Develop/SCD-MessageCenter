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

## Why use the message center?
The typical use of the message center is the realtime monitoring and remote control of a multi-threading application.<br>The message center can also be used for remote debugging in real time by controlling variable values, and modifying their value, for example. A very interesting use could be, if the host application allows it, the execution of system commands or the execution of processes.
## Message Center Architecture

Message center consists of two parts:

- The Multithreading Socket Server to accept remote client connections
- The Message center to serialize and exchange message/commands between application thread (sender) and remote clients (commands clients)
<img src="MessageCenter.png"/>
<p align="center"><b>Example of integration of the message center into an application actually created by me</b></p>
