#include <QObject>

class MQTTHandler : public QObject {
	Q_OBJECT

public:
	virtual ~MQTTHandler();
	
public slots:
	void beginSession();
	
signals:
	void connection_failed(int rc);
};
