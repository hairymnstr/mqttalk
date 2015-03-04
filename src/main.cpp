#include <QApplication>
#include <QThread>
#include "mqtthandler.hpp"
#include "mqttalkapp.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  app.setApplicationName("MQTTalk");

  MQTTalkApp mqttalkApp;

  mqttalkApp.show();
  return app.exec();
}

