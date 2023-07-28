
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMqtt/qmqttclient.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QString state = " 未连接服务器";
    int s = 0, snet = 0;
    QString runningstate[2] = {"停止运行","正在运行"};
    int counts = 0;
    int badcounts = 0;

public slots:
    void setClientPort(int p);

private slots:
    void on_buttonConnect_clicked();
    void on_buttonQuit_clicked();
    void updateLogStateChange();

    void brokerDisconnected();

    void on_buttonPublish_clicked();

    void on_buttonSubscribe_clicked();


    void on_pushButtonstop_clicked();

private:
    Ui::MainWindow *ui;
    QMqttClient *m_client;
};

#endif // MAINWINDOW_H
