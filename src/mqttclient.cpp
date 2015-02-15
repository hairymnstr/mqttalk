#include "mqttclient.hpp"

MQTTClient::MQTTClient(const char *id) : mosquittopp(id) {

}

MQTTClient::~MQTTClient() {

}

void MQTTClient::on_connect(int rc) {

  if(!rc) {
    subscribe(&mid, "#", 0);
  } else {
    std::cout << "Connection failed" << rc << std::endl;
  }
}

void MQTTClient::on_subscribe(uint16_t mid, int qos_count, const uint8_t *granted_qos) {
  std::cout << "Susbscribed (mid: " << mid << "): " << granted_qos[0] << std::endl;
}

void MQTTClient::on_message(const struct mosquitto_message *message) {
  if(message->payloadlen) {
    std::cout << message->topic << ": " << message->payload << std::endl;
  } else {
    std::cout << message->topic << ": (null)" << std::endl;
  }
}

