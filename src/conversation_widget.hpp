#include "mosquitto.h"
#include <QTextEdit>
#include <QVBoxLayout>

#ifndef _CONVERSATION_WIDGET_H
#define _CONVERSATION_WIDGET_H

class ConversationWidget : public QWidget {
	Q_OBJECT
	
	public:
		ConversationWidget();
		
	private:
		QTextEdit *conversation;
		QVBoxLayout *layout;
		
	public slots:
		void new_message(struct mosquitto_message *message);
};

#endif /* ifndef _CONVERSATION_WIDGET_H */
