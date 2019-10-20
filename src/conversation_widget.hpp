#include "mosquitto.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QVariant>

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
		void new_message(const QVariantMap&);
};

#endif /* ifndef _CONVERSATION_WIDGET_H */
