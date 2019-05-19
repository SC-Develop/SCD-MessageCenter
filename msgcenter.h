#ifndef SCDMSGCENTER_H
#define SCDMSGCENTER_H

#include <QObject>
#include <QTcpSocket>

class SCDMsgCenter : public QObject
{
    Q_OBJECT

  private:

    struct Client
    {
       QString name;         // connection name
       QString user;         // username
       QString Sender;       // sender id from which to receive the messages
       int mode;             // operating  mode (0: command console, 1: realtime messages receiving)
       int admin;            // admin user (can see others user info)
       int index;            // index on clients list
       int socketDescriptor; // client socket connection descriptor
    };

    const char CR = 0x0D;
    const char LF = 0x0A;

    QVector<Client> clients; // list of client socket

    QStringList senders;       // list of message senders

    void notifyRemovedSender();

    Client getClient(int socketDescriptor);

    QStringList getSenderList();

    QString getHelpString();

    QString getPrompt(int socketDescriptor);

    void sendMessageToClient(QString msg, int clientSocketDescriptor);

  public:

    explicit SCDMsgCenter(QObject *parent = nullptr);

    void addClient(int socketDescriptor);

    void removeClient(int socketDescriptor);

    void addSender(QString sender);

    void removeSender(QString sender);

    void sendCommand(QString message, int clientSocketDescriptor);

    void postMessage(QString msg, QString sender, bool prependNewLine=true);

  signals:

    // internal connected signal ---------------------------------------------------------------------

    void registerClient_signal(int socketDescriptor);
    void removeClient_signal(int socketDescriptor);

    void registerSender_signal(QString sender);
    void removeSender_signal(QString sender);

    /**
      * @brief command  this signal must be emit to send the command 'command' to message center.
      *                 Message center process it automatically, and forward message destinate to sender,
      *                 emmitting, appropriated singnal (commandToSender_signal)
      * @param command  command string
      * @param toSender sender to send command to
      */
    void command_signal(QString command, int socketDescriptor);

    /**
     * @brief message_signal sender send a message to message center.
     *                       messages are intended for all clients,
     *                       but only those clients who request them will receive it
     * @param msg
     * @param sender
     */
    void message_signal(QString msg, QString sender);

    // external connected signal ----------------------------------------------------------------

    /**
     * @brief commandToSender_signal send a command to sender: shuld be processed by sender thread
     * @param command
     * @param toSender Sender wich should be receive command
     */
    void commandToSender_signal(QString command, QString toSender);

    /**
     * @brief messageToClient_signal send a message to client: shuld be processed by client thread
     * @param msg
     * @param socketDescriptor destionation client socket descriptor
     */
    void messageToClient_signal(QString msg, int socketDescriptor);

  private slots:

    void registerClient_slot(int socketDescriptor);
    void removeClient_slot(int socketDescriptor);

    void registerSender_slot(QString sender);
    void removeSender_slot(QString sender);

    void command_slot(QString cmd, int clientSocketDescriptor);
    void message_slot(QString msg, QString sender);    
};

#endif // SCDMSGCENTER_H
