#include "mqtthandler.hpp"

MQTTHandler::MQTTHandler() {
	mqtt_client = new MQTTThread;
	client_thread = new QThread;
	mqtt_client->moveToThread(client_thread);
	
	client_thread->start();
  
// 	QMetaObject::invokeMethod(mqtt_client, "mainLoop", Qt::QueuedConnection);
}

MQTTHandler::~MQTTHandler() {
	client_thread->quit();
	client_thread->wait();
}
