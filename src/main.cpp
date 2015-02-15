#include <QApplication>
#include "mqttclient.hpp"
#include "mqttalkapp.hpp"

int main(int argc, char *argv[]) {
  int rc;
  QApplication app(argc, argv);

  app.setApplicationName("MQTTalk");

  MQTTalkApp mqttalkApp;

  MQTTClient *mqttClient = new MQTTClient("test");

  mqttClient->lib_init();

  mqttClient->connect("localhost", 1883, 60, true);

  do {
    rc = mqttClient->loop(-1);
  } while(rc == MOSQ_ERR_SUCCESS);

  mqttClient->disconnect();
  mqttClient->lib_cleanup();

  mqttalkApp.show();
  return app.exec();
}

