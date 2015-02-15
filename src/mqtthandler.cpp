#include "mqttclient.hpp"
#include "mqtthandler.hpp"

MQTTHandler::~MQTTHandler()
{

}

void MQTTHandler::beginSession() {
	int rc;
	const char *hostname = "localhost";
	int port = 1883;
	MQTTClient *mqttClient = new MQTTClient("test");

	mqttClient->lib_init();

	mqttClient->connect(hostname, port, 60, true);

	do {
		rc = mqttClient->loop(-1);
	} while(rc == MOSQ_ERR_SUCCESS);

	mqttClient->disconnect();
	mqttClient->lib_cleanup();
	
	emit connection_failed(rc);
}
