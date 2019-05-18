# SCD Message Center (QT C++ Class)

## Description
SCD Message Center is a Qt interprocess communication class.<br>
The purpose of the Message Center is to allow the exchange of messages between your own multithreading application and one or more remote control-monitoring terminals via TCP socket. <br>
This Qt class can be used also for generic interprocess communication through message exchanging.<br>
This class can be easily integrated into your application, it works very well and it's truly reliable
## What you can do with the SCD Message Center
Embedding the SCD Message Center within your application you can:

- Realtime monitoring  of your own application by receiving messages from each thread of your application via tcp Socket, such as log messages, variable values, event messaging etc.
- Send commands to the message center to get status information or request the execution of actions to your application threads
- send custom commands to each thread of your application for performing custom actions, such as disconnecting a client, terminating a thread, changing the value of variables, etc.
