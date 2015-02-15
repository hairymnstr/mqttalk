#include <mosquittopp.h>
#include <iostream>

#ifndef MQTTCLIENT_H_
#define MQTTCLIENT_H_

class MQTTClient : public mosquittopp::mosquittopp {

public:
  MQTTClient(const char *id);
  virtual ~MQTTClient();

private:
  uint16_t mid;

  void on_connect(int rc);
  void on_subscribe(uint16_t mid, int qos_count, const uint8_t *granted_qos);
  void on_message(const struct mosquitto_message *message);
};

#endif /* ifndef MQTTCLIENT_H_ */

