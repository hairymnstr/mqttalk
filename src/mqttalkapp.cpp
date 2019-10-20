#include <QtGui>
#include <QMetaObject>
#include <iostream>

#include "mqttalkapp.hpp"

MQTTalkApp :: MQTTalkApp() {
	chatWidget = new ConversationWidget;
	connectionStatusLabel = new QLabel;
        mqttalk_client = new MQTTalkClient(QString("hairymnstr"), QString("localhost"), 1883);
	
    const bool connected = connect(mqttalk_client, SIGNAL(new_message(const QVariantMap&)),
            chatWidget, SLOT(new_message(const QVariantMap&)));

    qDebug() << "Connected? " << connected;

	setCentralWidget(chatWidget);

	connectionStatusLabel->setText("Disconnected");

	statusBar()->addPermanentWidget(connectionStatusLabel);
}

