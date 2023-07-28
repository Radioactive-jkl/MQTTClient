# MQTT client
Radioactive *`V1.0`*
<h3 align="center">C4-Network Technology Challenge</h3>


#### Contents

* [Background](#background)
* [Highlights](#highlights)


## Background

* 临近考试周前，用3天水了一个比赛[*`China Collegiate Computing Contest/Network Technology Challenge/B-EP2`*](http://net.c4best.cn/)
* 然后想把其中**物联网客户端**的代码丢出来，~~其实就是Qt例程小改了一下~~。
  
##### Files
```
mqttclient
  ├── local_machine_code
  |    ├── 懒得整理源码
  |    └── requirements.txt(for Python)
  |
  └── aliyun_mqtt_client
       ├── client.pro
       ├── main.cpp
       ├── mainwindow.ui
       ├── mainwindow.h
       └── mainwindow.cpp
```

## Highlights


##### aliyun_mqtt_client
```
1. C++/QT5.14.2 + mqtt库
2. 用于连接服务器，远程操控工业齿轮缺陷检测系统的运行
3. 远程查看运行状态和云端数据（已检测齿轮数、缺陷齿轮数、良率等）
```

##### local_machine_code
```
1. 工业齿轮缺陷检测系统的本地运行程序（需要配置python运行环境）
2. 连接了PLC工控机对传送带电机等设备进行运动控制
3. 连接了摄像头组进行拍摄和基于深度学习的齿轮检测
4. 有图形化界面实时监视6个摄像头画面和运行效果
```