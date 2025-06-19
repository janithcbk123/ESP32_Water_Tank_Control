<p align="center">
<img src="https://github.com/SEUintern/ESP32_Water_Tank_Control/blob/main/Supportive%20Images/hivemq-logo.png?raw=true">
</p>

## How to use the web server? 

Put the server URL on the web browser. 
- Server URL: 	https://www.hivemq.com/demos/websocket-client/ 

 
### Connection 

<p align="center">
<img width="550" src="https://github.com/SEUintern/ESP32_Water_Tank_Control/blob/main/Supportive%20Images/HiveMQ/Connection.png?raw=true">
</p>
<p align="center">
Figure 1: Connection panel 
</p>

- **Host:** Insert host address for MQTT broker connection. 
- **Port:** Insert the port for MQTT broker connection. 
  - HiveMQ uses port 1883 (for standard MQTT) and 8883 (for MQTT + TLS) by default. 
- **ClientID:** Insert the MQTT Client ID for MQTT broker connection. 
- **Username:** Insert the username for MQTT client authentication. 
- **Password:** Insert the password for MQTT client authentication. 
- **Keep Alive:** Insert the number of seconds that the broker permits between when a client finishes sending one MQTT packet and starts to send the next. 
- **SSL:** Enable/Disable SSL Server. 
- **Clean Session:** Request a non-persistent session. 
- **Last-Will Topic:** Insert the topic that should automatically be published by the broker on their behalf, if or when an unexpected disconnection occurs. 
- **Last-Will QoS:** Set Quality of Service for Last-Will. 
- **Last-Will Retain:** Enable/Disable the storage of last-will message retained. 
- **Last-Will Message:** Insert the message that should automatically be published by the broker on their behalf, if or when an unexpected disconnection occurs. 

#### Water Tank Project MQTT Connection Settings: 

- **Host:** 		_mqtt-dashboard.com_ 
- **Port:** 		_8884_
- **ClientID:** 	_clientId-dvG4snHTZr_ 
- **Username:** 	_<None>_
- **Password:** 	_<None>_
- **Keep Alive:** 	_60_
- **SSL:** 		_Enable SSL Server._
- **Clean Session:** 	_Request a non-persistent session._
- **Last-Will Topic:** 	_<None>_
- **Last-Will QoS:** 	_0_
- **Last-Will Retain:** 	_Disable the storage of last-will message retained._ 
- **Last-Will Message:** _<None>_

 
### Publish 

<p align="center">
<img width="550" src="https://github.com/SEUintern/ESP32_Water_Tank_Control/blob/main/Supportive%20Images/HiveMQ/Publish.png?raw=true">
</p>
<p align="center">
Figure 2: Publish panel  
</p>

- **Topic:** Insert the topic that should be published. 
- **QoS:** Set Quality of Service of publishing message. 
- **Retain:** Enable/Disable the storage of message retained. 
- **Message:** Insert the message that should be published. 

Water Tank Project MQTT Topics: 

- **Tank-1 Water Level	:**_"testtopic/101"_
- **Tank-2 Water Level	:**_"testtopic/102"_ 
- **Solenoid-1			:** _"Solenoid/1"_
- **Solenoid-5			:** _"Solenoid/5"_
- **Solenoid-6			:** _"Solenoid/6"_
- **Solenoid-7			:** _"Solenoid/7"_


### Subscriptions 

<p align="center">
<img width="350" src="https://github.com/SEUintern/ESP32_Water_Tank_Control/blob/main/Supportive%20Images/HiveMQ/Subscriptions.png?raw=true">
</p>
<p align="center">
Figure 3: Subscribe panel 
</p>

1. Click Add New Topic Subscription. 
2. Set the topic and QoS that should be subscribed to in the pop-up window. 
3. Assign a color for the topic. 
4. Repeat for every topic. 

#### Water Tank Project MQTT Topics: 

- **Tank-1 Water Level	:**_"testtopic/101"_
- **Tank-2 Water Level	:**_"testtopic/102"_ 
- **Solenoid-1			:** _"Solenoid/1"_
- **Solenoid-5			:** _"Solenoid/5"_
- **Solenoid-6			:** _"Solenoid/6"_
- **Solenoid-7			:** _"Solenoid/7"_


### Messages 
This panel displays messages of the subscribed topics. 

<p align="center">
<img width="550" src="https://github.com/SEUintern/ESP32_Water_Tank_Control/blob/main/Supportive%20Images/HiveMQ/Messages.png?raw=true">
</p>
<p align="center">
Figure 4: Message panel 
</p>


