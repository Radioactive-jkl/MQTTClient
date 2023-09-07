# MQTT client
Radioactive *`V1.0`*
<h3 align="center">C4-Network Technology Challenge</h3>

---

<a target="_blank" rel="noopener noreferrer" href="https://www.microsoft.com/zh-cn/windows"><img src="https://camo.githubusercontent.com/b44114213a5a462903bd69611bb6846f1dc41fe6f3230bd37c67c3d4eb65f08c/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d57696e646f77732d626c61636b3f7374796c653d666c61742d737175617265266c6f676f3d77696e646f7773266c6f676f436f6c6f723d626c7565" alt="Windows" data-canonical-src="https://img.shields.io/badge/-Windows-black?style=flat-square&amp;logo=windows&amp;logoColor=blue" style="max-width: 100%;"></a>  [![alibabacloud](https://img.shields.io/badge/Aliyun-FF6A00?logo=alibabacloud&logoColor=white)](https://iot.aliyun.com/) [![Github Actions Badge](https://img.shields.io/badge/-Git%20-2088FF?style=flat&logo=Git&logoColor=white)](https://git-scm.com/)  [![OpenCV](https://img.shields.io/badge/OpenCV-27338e?style=flat-square&logo=OpenCV&logoColor=white)](https://opencv.org/) [![pytorch](https://img.shields.io/badge/PyTorch-EE4C2C?style=flat-square&logo=pytorch&logoColor=white)](https://pytorch.org/)  [![Static Badge](https://img.shields.io/badge/Conda-Python-0099e5?logo=anaconda&logoColor=44A833)](https://radioactive-jkl.github.io/) [![qt](https://img.shields.io/badge/Qt-C%2B%2B-41CD52?logo=qt&logoColor=white)](https://www.qt.io/zh-cn/) [![plc](https://img.shields.io/badge/PLC-009999?logo=siemens&logoColor=white)](https://www.siemens.com/cn/zh.html)

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
