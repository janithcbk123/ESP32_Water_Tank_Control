#include <WiFi.h>
#include <PubSubClient.h>

#define Solenoid_1 5
#define Solenoid_2 17
#define Solenoid_3 16
#define Solenoid_4 4
#define Solenoid_5 0
#define Solenoid_6 2
#define Solenoid_7 15

#define S1_trigPin 23
#define S1_echoPin 22
#define S2_trigPin 19
#define S2_echoPin 18

#define Internet_Indicator 32
#define MQTT_Indicator 33


long duration_1;
long duration_2;
int distance_1;
int distance_2;

bool Solenoid_1_status;
bool Solenoid_2_status;
bool Solenoid_3_status;
bool Solenoid_4_status;
bool Solenoid_5_status;
bool Solenoid_6_status;
bool Solenoid_7_status;

// WiFi
const char *ssid = "Wokwi-GUEST"; // Enter your Wi-Fi name
const char *password = "";  // Enter Wi-Fi password

// MQTT Broker
const char *mqtt_broker = "broker.mqttdashboard.com";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

const char *MQTT_TOPIC_1 = "testtopic/101";
const char *MQTT_TOPIC_2 = "testtopic/102";

const char *MQTT_SOLENOID_1 = "Solenoid/1";
const char *MQTT_SOLENOID_2 = "Solenoid/5";
const char *MQTT_SOLENOID_3 = "Solenoid/6";
const char *MQTT_SOLENOID_4 = "Solenoid/7";

int Tank_1_Uplimit    = 350;
int Tank_1_Downlimit  = 100;
int Tank_2_Uplimit    = 350;
int Tank_2_Downlimit  = 100;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    // Set software serial baud to 115200;
    Serial.begin(115200);

    // put your setup code here, to run once:
    pinMode(S1_trigPin, OUTPUT); // Sets the S1 trigPin as an Output
    pinMode(S2_trigPin, OUTPUT); // Sets the S2 trigPin as an Output
    pinMode(S1_echoPin, INPUT); // Sets the S1 echoPin as an Input
    pinMode(S2_echoPin, INPUT); // Sets the S2 echoPin as an Input

    pinMode(Solenoid_1, OUTPUT); // Sets the trigPin as an Output
    pinMode(Solenoid_2, OUTPUT); // Sets the trigPin as an Output
    pinMode(Solenoid_3, OUTPUT); // Sets the trigPin as an Output
    pinMode(Solenoid_4, OUTPUT); // Sets the trigPin as an Output
    pinMode(Solenoid_5, OUTPUT); // Sets the trigPin as an Output
    pinMode(Solenoid_6, OUTPUT); // Sets the trigPin as an Output
    pinMode(Solenoid_7, OUTPUT); // Sets the trigPin as an Output

    pinMode(Internet_Indicator, OUTPUT);  // Sets the Internet Indicator pin as an Output
    pinMode(MQTT_Indicator, OUTPUT);      // Sets the MQTT Indicator pin as an Output

    digitalWrite(Internet_Indicator, LOW);
    digitalWrite(MQTT_Indicator, LOW);

    // Connecting to a WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the Wi-Fi network");
    digitalWrite(Internet_Indicator, HIGH);
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public EMQX MQTT broker connected");
            digitalWrite(MQTT_Indicator, HIGH);
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            digitalWrite(MQTT_Indicator, LOW);
            delay(2000);
        }
    }
    // Publish and subscribe
    client.subscribe(MQTT_SOLENOID_1);
    client.subscribe(MQTT_SOLENOID_2);
    client.subscribe(MQTT_SOLENOID_3);
    client.subscribe(MQTT_SOLENOID_4);

    
}

void callback(char *topic, byte *payload, unsigned int length){
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    String messageTemp;
  
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      messageTemp += (char)payload[i];
    }

    Serial.println();
    if (String(topic) == MQTT_SOLENOID_1) {
      Serial.print("Changing output to ");
      if(messageTemp == "on"){
        Serial.println("on");
        Solenoid_1_status = true;
        digitalWrite(Solenoid_1, HIGH);
      }
      else if(messageTemp == "off"){
        Serial.println("off");
        Solenoid_1_status = false;
        digitalWrite(Solenoid_1, LOW);
      }
    }
    if (String(topic) == MQTT_SOLENOID_2) {
      Serial.print("Changing output to ");
      if(messageTemp == "on"){
        Serial.println("on");
        Solenoid_5_status = true;
        digitalWrite(Solenoid_5, HIGH);
      }
      else if(messageTemp == "off"){
        Serial.println("off");
        Solenoid_5_status = false;
        digitalWrite(Solenoid_5, LOW);
      }
    }
    if (String(topic) == MQTT_SOLENOID_3) {
      Serial.print("Changing output to ");
      if(messageTemp == "on"){
        Serial.println("on");
        Solenoid_6_status = true;
        digitalWrite(Solenoid_6, HIGH);
      }
      else if(messageTemp == "off"){
        Serial.println("off");
        Solenoid_6_status = false;
        digitalWrite(Solenoid_6, LOW);
      }
    }
    if (String(topic) == MQTT_SOLENOID_4) {
      Serial.print("Changing output to ");
      if(messageTemp == "on"){
        Serial.println("on");
        Solenoid_7_status = true;
        digitalWrite(Solenoid_7, HIGH);
      }
      else if(messageTemp == "off"){
        Serial.println("off");
        Solenoid_7_status = false;
        digitalWrite(Solenoid_7, LOW);
      }
    }
    Serial.println("-----------------------");
}

void loop() {
    client.loop();
    measure_distance();

    measure_distance();

    get_message();

}

void measure_distance(){
  // Clears the trigPin
  digitalWrite(S1_trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(S1_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(S1_trigPin, LOW);


  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_1 = pulseIn(S1_echoPin, HIGH);

  // Calculating the distance
  distance_1 = duration_1 * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  //Serial.print("Distance 1: ");
  //Serial.println(distance_1);


  digitalWrite(S2_trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(S2_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(S2_trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds

  duration_2 = pulseIn(S2_echoPin, HIGH);

  // Calculating the distance
  distance_2 = duration_2 * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  //Serial.print("Distance 2: ");
  //Serial.println(distance_2);
}

void get_message(){
  // Convert the value to a char array
  char Dis1String[8];
  dtostrf(distance_1, 1, 2, Dis1String);
  Serial.print("Distance 1: ");
  Serial.println(Dis1String);
  client.publish(MQTT_TOPIC_1, Dis1String);
    
  char Dis2String[8];
  dtostrf(distance_2, 1, 2, Dis2String);
  Serial.print("Distance 2: ");
  Serial.println(Dis2String);
  client.publish(MQTT_TOPIC_2, Dis2String);
}