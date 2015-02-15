#include <QtGui>

#include "mqttalkapp.hpp"

MQTTalkApp :: MQTTalkApp() {
  chatWidget = new QTextEdit;
  connectionStatusLabel = new QLabel;

  setCentralWidget(chatWidget);

  connectionStatusLabel->setText("Disconnected");

  statusBar()->addPermanentWidget(connectionStatusLabel);
}

void MQTTalkApp::closeEvent(QCloseEvent *event) {
  event->accept();
}

