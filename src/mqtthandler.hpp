#include <QObject>
#include <QThread>
#include "mqttthread.hpp"

#ifndef _MQTTHANDLER_H
#define _MQTTHANDLER_H

class MQTTHandler : public QObject {
	Q_OBJECT

public:
	MQTTHandler();
	~MQTTHandler();
	MQTTThread *mqtt_client;
	
signals:
	void connection_failed(int rc);
	
private:
	QThread *client_thread;
};

#endif /* ifndef _MQTTHANDLER_H */
