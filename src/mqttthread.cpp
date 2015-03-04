#include <mosquitto.h>
#include <iostream>
#include "mqttthread.hpp"

const char *offline_message = "offline";
const char *online_message = "online";

MQTTThread::~MQTTThread() {

}

static void _on_connect(struct mosquitto *mosq, void *userdata, int result) {
	((MQTTThread *)userdata)->onConnect(mosq, result);
}

static void _on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
	((MQTTThread *)userdata)->onMessage(mosq, message);
}

static void _on_subscribe(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos) {
	((MQTTThread *)userdata)->onSubscribe(mosq, mid, qos_count, granted_qos);
}

void MQTTThread::onConnect(struct mosquitto *mosq, int result) {
	if(!result) {
		std::cout << "Connected" << std::endl;
		mosquitto_subscribe(mosq, NULL, "#", 2);
	} else {
		std::cerr << "Connection failed" << std::endl;
	}
}

void MQTTThread::onMessage(struct mosquitto *mosq __attribute__((__unused__)),
						   const struct mosquitto_message *message) {
	struct mosquitto_message *msg;
	int err;
	
	msg = (struct mosquitto_message *)malloc(sizeof(struct mosquitto_message));
	
	if(msg == NULL) {
		std::cerr << "Malloc() failed" << std::endl;
	}
	
	if((err = mosquitto_message_copy(msg, message)) == MOSQ_ERR_SUCCESS) {	
		emit messageReceived(msg);
	} else {
		std::cout << "Message Copy Failed: " << err << std::endl;
	}
	
	if(message->payloadlen) {
		std::cout << message->topic << ": " << (char *)message->payload << std::endl;
	} else {
		std::cout << message->topic << ": (null)" << std::endl;
	}
}

void MQTTThread::onSubscribe(struct mosquitto *mosq, int mid, int qos_count, const int *granted_qos) {
	int i;
	std::cout << "Subscribed (mid " << mid << "): " << granted_qos[0];
	for(i=1;i<qos_count;i++) {
		std::cout << ", " << granted_qos[i];
	}
	std::cout << std::endl;
}

void MQTTThread::stop() {
	stopThread = true;
}

void MQTTThread::startUp(QString hostname, int port, QString username) {
	int rc;
	struct mosquitto *mosq = NULL;

	stopThread = false;
	
	mosquitto_lib_init();
	
	mosq = mosquitto_new("MQTTalk", true, this);
	if(!mosq) {
		std::cerr << "Error: out of memory." << std::endl;
		return;
	}
	
	mosquitto_connect_callback_set(mosq, &_on_connect);
	mosquitto_message_callback_set(mosq, &_on_message);
	mosquitto_subscribe_callback_set(mosq, &_on_subscribe);
	
	QString online_topic = QString("/user/") + username + QString("/status");
	if((rc = mosquitto_will_set(mosq, online_topic.toStdString().c_str(), 
						  strlen(offline_message),
						  (const void *)offline_message, 1, true)) != MOSQ_ERR_SUCCESS) {
		std::cerr << "setting will failed " << rc << std::endl;
	}

	if(mosquitto_connect(mosq, hostname.toStdString().c_str(), port, 60)) {
		std::cerr << hostname.toStdString().c_str() << ":" << port << std::endl;
		std::cerr << username.toStdString().c_str() << std::endl;
		std::cerr << "Connect failed" << std::endl;
		return;
	}
	
	mosquitto_publish(mosq, NULL, online_topic.toStdString().c_str(),
					  strlen(online_message),
					  (const void *)online_message, 1, true);
	
	while(!mosquitto_loop(mosq, -1, 1)) { 
		if(stopThread) break;
	}
	
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
}
