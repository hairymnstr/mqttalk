#include <QObject>

#ifndef MQTTTHREAD_H_
#define MQTTTHREAD_H_

class MQTTThread : public QObject {
	Q_OBJECT
	
public:
	virtual ~MQTTThread();
	void onConnect(struct mosquitto *mosq, int result);
	void onMessage(struct mosquitto *mosq, const struct mosquitto_message *message);
	void onSubscribe(struct mosquitto *mosq, int mid, int qos_count, const int *granted_qos);
	
public slots:
	void mainLoop();
	
private:
};

#endif /* ifndef MQTTTHREAD_H_ */
