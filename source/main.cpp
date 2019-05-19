/**

  @author Ing. Salvatore Cerami dev.salvatore.cerami@gmail.com

  @brief SCD Message Center Demo - https://github.com/sc-develop/SCD_MC

         This program demonstrate how to use the SCD Message Center, a Qt C++ inter process communication class library .

*/



#include <QCoreApplication>
#include <QSettings>
#include <msgserver.h>
#include <demoserver.h>

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);

   QSettings cfg("message-center-deno.cfg");

   int port = cfg.value("port",12345).toInt();   // load application server port value and set default  if not exists

   cfg.setValue("port",port);                    // save value

   cfg.beginGroup("MessageCenter");

   int mcport = cfg.value("port",12346).toInt(); // load message center server port value and set default if not exists

   cfg.setValue("port",mcport);                  // save value

   cfg.sync();

   SCDMsgServer msgServer(mcport,true);  // declare message center server

   msgServer.start();                 // start message center server: message center is self allocated by messgae server

   DemoServer server(Q_NULLPTR, port, msgServer.messageCenter()); // declare application server

   server.start();                       // start application server

   return a.exec();                      // start application main event loop
}
