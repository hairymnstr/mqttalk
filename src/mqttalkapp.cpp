#include <QtGui>
#include <QMetaObject>
#include <iostream>

#include "mqttalkapp.hpp"

MQTTalkApp :: MQTTalkApp() {
	chatWidget = new ConversationWidget;
	connectionStatusLabel = new QLabel;
        mqttalk_client = new MQTTalkClient(QString("hairymnstr"), QString("localhost"), 1883);
	  
	setCentralWidget(chatWidget);

	connectionStatusLabel->setText("Disconnected");

	statusBar()->addPermanentWidget(connectionStatusLabel);
}

