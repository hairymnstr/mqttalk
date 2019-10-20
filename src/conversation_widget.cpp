#include <QtGui>
#include "conversation_widget.hpp"
#include <iostream>

ConversationWidget::ConversationWidget() {
	conversation = new QTextEdit;
	conversation->setReadOnly(true);
	
	layout = new QVBoxLayout;
	
	layout->addWidget(conversation);
	
	setLayout(layout);
}

void ConversationWidget::new_message(const QVariantMap & message) {
    qDebug() << "received signal...";
	std::cout << message["sender"].toString().toStdString() << ": " << message["message"].toString().toStdString() << std::endl;
	
    conversation->append(message["sender"].toString());
    conversation->append(QString(": "));
	conversation->append(message["message"].toString());
}
