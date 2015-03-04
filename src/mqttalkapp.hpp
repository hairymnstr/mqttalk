#include <QMainWindow>
#include <QLabel>

#include "mqtttalk_client.hpp"
#include "conversation_widget.hpp"

class MQTTalkApp : public QMainWindow {
  Q_OBJECT

  public:
    MQTTalkApp();

  private:
    ConversationWidget *chatWidget;
    QLabel *connectionStatusLabel;
    MQTTalkClient *mqttalk_client;
};

