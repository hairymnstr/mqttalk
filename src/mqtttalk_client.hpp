#include <QThread>
#include <QString>
#include "mosquitto.h"
#include "mqttthread.hpp"

class MQTTalkClient : public QObject {
  Q_OBJECT

  public:
    MQTTalkClient(QString username, QString hostname, int port);

public slots:
	void messageReceived(struct mosquitto_message *message);
	
  private:
	QString username;
	QString hostname;
	int port;
	MQTTThread *mqtt_client;
	QThread *client_thread;
};