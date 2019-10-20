#include <QtGui>
#include <QMetaObject>
#include <iostream>
#include <qjson/parser.h>

#include "mqtttalk_client.hpp"

MQTTalkClient::MQTTalkClient(QString username, QString hostname, int port) {
	client_thread = new QThread;
	mqtt_client = new MQTTThread;
	mqtt_client->moveToThread(client_thread);
	
	client_thread->start();
	
	this->username = username;
	this->hostname = hostname;
	this->port = port;

	connect(mqtt_client, SIGNAL(messageReceived(struct mosquitto_message*)),
		    this, SLOT(messageReceived(struct mosquitto_message *)));
  
	QMetaObject::invokeMethod(mqtt_client, "startUp", Qt::QueuedConnection,
							  Q_ARG(QString, hostname), Q_ARG(int, port), Q_ARG(QString, username));
}

void MQTTalkClient::messageReceived(struct mosquitto_message *message) {
        
        QByteArray json = QByteArray((const char *)message->payload, message->payloadlen);

        QJson::Parser parser;
        
        bool ok;
        
        QVariantMap result = parser.parse(json, &ok).toMap();
        
        if(ok) {
            qDebug() << "message id " << result["message_id"].toString();
            qDebug() << "time" << result["time"].toString();
            qDebug() << "sender" << result["sender"].toString();
            qDebug() << "message" << result["message"].toString();

            qDebug() << "emitting...";
            emit new_message(result);
        }
	
	std::cout << message->topic << ": " << QString(json).toStdString() << std::endl;
	
	mosquitto_message_free(&message);
}
