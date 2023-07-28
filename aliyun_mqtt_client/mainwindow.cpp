
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QDateTime>
#include <QtMqtt/qmqttclient.h>
#include <QtWidgets/QMessageBox>
#include "QtMqtt/qmqttmessage.h"
#include "QJsonObject"
#include "QJsonDocument"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditid->setText("XXXXXXXXX.industrialclient|securemode=2,signmethod=hmacsha256,timestamp=1685622980799|");
    ui->lineEditname->setText("industrialclient&XXXXXXXXX");
    ui->lineEditHost->setText("iot-XXXXXXXXX.mqtt.iothub.aliyuncs.com");
    ui->lineEditpswd->setText("XXXXXXXXX");
    ui->lineEditTopic->setText("/sys/XXXXXXXXX/industrialclient/thing/service/property/set");

    ui->label_state->setText(state);
    ui->label_counts->setNum(counts);
    ui->label_badcounts->setNum(badcounts);
    ui->label_rate->setNum(badcounts/double(counts));

    m_client = new QMqttClient(this);
    m_client->setClientId(ui->lineEditid->text());
    m_client->setUsername(ui->lineEditname->text());
    m_client->setHostname(ui->lineEditHost->text());
    m_client->setPassword(ui->lineEditpswd->text());
    m_client->setPort(ui->spinBoxPort->value());


    connect(m_client, &QMqttClient::stateChanged, this, &MainWindow::updateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &MainWindow::brokerDisconnected);

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" Received Topic: ")
                    + topic.name()
                    + QLatin1String(" Message: ")
                    + message
                    + QLatin1Char('\n');
        ui->editLog->insertPlainText(content);
    });

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" PingResponse")
                    + QLatin1Char('\n');
        ui->editLog->insertPlainText(content);
    });

    connect(ui->lineEditHost, &QLineEdit::textChanged, m_client, &QMqttClient::setHostname);
    connect(ui->spinBoxPort, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setClientPort);
    connect(this->m_client,&QMqttClient::messageReceived,[=](const QByteArray &message, const QMqttTopicName &topic = QMqttTopicName()){
            ui->editLog->insertPlainText("\n-------------------------------------\n");
            ui->editLog->insertPlainText("topic:" + topic.name()+"\n");
            ui->editLog->insertPlainText("message:" + message+"\n");
            ui->editLog->insertPlainText("\n-------------------------------------\n");

            QJsonDocument doc = QJsonDocument::fromJson(message);
            QJsonValue params = doc["params"];
            s = params["RunningState"].toInt();
            counts = params["counts"].toInt();
            badcounts = params["badcounts"].toInt();

            ui->label_state->setText(runningstate[s]);
            ui->label_counts->setNum(counts);
            ui->label_badcounts->setNum(badcounts);
            ui->label_rate->setNum(1-badcounts/double(counts));
            qDebug("%d %d %d",s,counts,badcounts);
        });

    updateLogStateChange();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonConnect_clicked()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        ui->lineEditid->setEnabled(false);
        ui->lineEditpswd->setEnabled(false);
        ui->lineEditHost->setEnabled(false);
        ui->lineEditname->setEnabled(false);
        ui->spinBoxPort->setEnabled(false);
        ui->buttonConnect->setText(tr("Disconnect"));
        m_client->connectToHost();
    } else {
        ui->lineEditHost->setEnabled(true);
        ui->spinBoxPort->setEnabled(true);
        ui->buttonConnect->setText(tr("Connect"));
        m_client->disconnectFromHost();
    }
}

void MainWindow::on_buttonQuit_clicked()
{
    QApplication::quit();
}

void MainWindow::updateLogStateChange()
{
    snet = m_client->state();
    switch (snet)
    {
        case 0:state = " 未连接服务器";break;
        case 1:state = " 尝试连接服务器";break;
        case 2:state = " 已连上服务器";break;
    }

    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + state + "\n";
    ui->editLog->insertPlainText(content);


}

void MainWindow::brokerDisconnected()
{
    ui->lineEditHost->setEnabled(true);
    ui->spinBoxPort->setEnabled(true);
    ui->buttonConnect->setText(tr("Connect"));
}

void MainWindow::setClientPort(int p)
{
    m_client->setPort(p);
}

void MainWindow::on_buttonPublish_clicked()
{
    if (m_client->publish(ui->lineEditTopic->text(), ui->lineEditMessage->text().toUtf8()) == -1)
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
}

void MainWindow::on_buttonSubscribe_clicked()
{
    auto subscription = m_client->subscribe(ui->lineEditTopic->text());
    if (!subscription) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }
    else ui->editLog->insertPlainText(QDateTime::currentDateTime().toString()+": 话题订阅成功\n");
}


void MainWindow::on_pushButtonstop_clicked()
{
    if(snet == 2)
    {
        if(s == 0)
        {
            QMessageBox::critical(this, QLatin1String("Error"), "设备未开启");
        }
        else
        {
            QMessageBox::critical(this, "Warning", "正在远程关闭设备");
        }
    }
    else QMessageBox::critical(this, QLatin1String("Error"), "未连接服务器");
}
