#ifndef SCDMSGCENTER_H
#define SCDMSGCENTER_H

#include <QObject>
#include <QTcpSocket>
#include <QMutex>

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

    QMutex mutex;

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

    /**
     * @brief commandToSender_signal send a command to sender: shuld be only processed by sender thread
     * @param command
     * @param toSender Sender wich should be receive command
     */
    void commandToSender_signal(QString command, QString toSender);

    /**
     * @brief messageToClient_signal send a message to client: shuld be only processed by client thread
     * @param msg
     * @param socketDescriptor destionation client socket descriptor
     */
    void messageToClient_signal(QString msg, int socketDescriptor);

  protected:

    void registerClient(int socketDescriptor);
    void unregisterClient(int socketDescriptor);

    void registerMessageSender(QString sender);
    void unregisterMessageSender(QString sender);

    void processCommand(QString cmd, int clientSocketDescriptor);
    void processMessage(QString msg, QString sender);
};

#endif // SCDMSGCENTER_H
