// Include necessary libraries for the Arduino board being used
#include <ArduinoMqttClient.h>
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
#include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
#include <WiFi101.h>
#elif defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#endif

// Define Wi-Fi credentials
const char* wifiSSID = "iPhone";
const char* wifiPassword = "12345666";

// Define the LED pin
int light = 13;

// Initialize Wi-Fi client and MQTT client
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// MQTT broker information
const char broker[] = "mqtt-dashboard.com";
int port = 1883;
const char topic[] = "SIT210Vansh/mywave";

// Function to set up Wi-Fi connection
void setupWiFi() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(wifiSSID, wifiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
}

// Function to set up serial communication
void setupSerial() {
  Serial.begin(9600);
  pinMode(light, OUTPUT);
  while (!Serial) {
    // Wait for the serial port to connect
  }
}

// Function to connect to the MQTT broker
void connectToMQTTBroker() {
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

// Function to subscribe to an MQTT topic
void Subscribe() {
  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();
  // Subscribe to a topic
  mqttClient.subscribe(topic);
  Serial.print("Waiting for messages on topic: ");
  Serial.println(topic);
  Serial.println();
}

void setup() {
  // Initialize serial communication, Wi-Fi, and MQTT connection
  setupSerial();
  setupWiFi();
  connectToMQTTBroker();
  Subscribe();
}

// Function to receive MQTT messages
void recieveMessage() {
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    // We received a message, print out the topic and contents
    Serial.print("Received a message with topic '");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");
  }
}

// Function to control the LED based on MQTT messages
void ledAction() {
  while (mqttClient.available()) {
    Serial.print((char)mqttClient.read());
  }
  Serial.println();
  digitalWrite(light, HIGH);
  delay(200);
  digitalWrite(light, LOW);
  delay(200);
  digitalWrite(light, HIGH);
  delay(200);
  digitalWrite(light, LOW);
  delay(200);
  digitalWrite(light, HIGH);
  delay(200);
  digitalWrite(light, LOW);
  delay(200);
  Serial.println();
}

void loop() {
  // Continuously check for incoming MQTT messages and control the LED
  recieveMessage();
  ledAction();
}
