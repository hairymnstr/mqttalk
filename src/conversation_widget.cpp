#include "conversation_widget.hpp"
#include <iostream>

ConversationWidget::ConversationWidget() {
	conversation = new QTextEdit;
	conversation->setReadOnly(true);
	
	layout = new QVBoxLayout;
	
	layout->addWidget(conversation);
	
	setLayout(layout);
}

void ConversationWidget::new_message(struct mosquitto_message* message) {
	char *msg;
	
	msg = (char *)malloc(message->payloadlen + 1);
	memcpy(msg, message->payload, message->payloadlen);
	msg[message->payloadlen] = 0;
	
	std::cout << message->topic << ": " << msg << std::endl;
	
	conversation->append(QString((const char *)message->topic));
	conversation->append(QString(msg));
	
	mosquitto_message_free(&message);
}
