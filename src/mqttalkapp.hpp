#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>

class MQTTalkApp : public QMainWindow {
  Q_OBJECT

  public:
    MQTTalkApp();

  protected:
    void closeEvent(QCloseEvent *event);

  private:
    QTextEdit *chatWidget;
    QLabel *connectionStatusLabel;
};

