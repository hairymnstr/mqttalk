#include "conversation_widget.hpp"
#include <iostream>
ConversationWidget::ConversationWidget() {
	conversation = new QTextEdit;
	layout = new QVBoxLayout;
	
	layout->addWidget(conversation);
	
	setLayout(layout);
}

void ConversationWidget::new_message(struct mosquitto_message* message) {
	
	std::cout << message->topic << ": " << (char *)message->payload << std::endl;
	conversation->append(QString((const char *)message->topic));
	conversation->append(QString("\n"));
	conversation->append(QString((const char *)message->payload));
	conversation->append(QString("\n"));
	
	mosquitto_message_free(&message);
}
