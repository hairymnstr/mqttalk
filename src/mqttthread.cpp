#include <mosquitto.h>
#include <iostream>
#include "mqttthread.hpp"

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

void MQTTThread::onMessage(struct mosquitto *mosq, const struct mosquitto_message *message) {
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

void MQTTThread::mainLoop() {
	int rc;
	const char *hostname = "localhost";
	int port = 1883;
	struct mosquitto *mosq = NULL;
	int maj, min, patch;

	mosquitto_lib_init();
	
	mosquitto_lib_version(&maj, &min, &patch);
	
	std::cout << "Mosquitto version: " << maj << "." << min << "." << patch << std::endl;
	
	mosq = mosquitto_new("MQTTalk", true, this);
	if(!mosq) {
		std::cerr << "Error: out of memory." << std::endl;
		return;
	}
	
	mosquitto_connect_callback_set(mosq, &_on_connect);
	mosquitto_message_callback_set(mosq, &_on_message);
	mosquitto_subscribe_callback_set(mosq, &_on_subscribe);
	
	if(mosquitto_connect(mosq, hostname, port, 60)) {
		std::cerr << "Connect failed" << std::endl;
		return;
	}
	
	while(!mosquitto_loop(mosq, -1, 1)) { ;}
	
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
}
