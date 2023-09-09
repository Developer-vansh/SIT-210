#include <ArduinoMqttClient.h>  // Include the Arduino MQTT client library

// Check the board type and include the appropriate WiFi library
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
#include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
#include <WiFi101.h>
#elif defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#endif

// Define your WiFi credentials
const char* wifiSSID = "iPhone";
const char* wifiPassword = "12345666";

// Define the pins for the ultrasonic sensor
const int trigPin = 2;
const int echoPin = 3;

float duration, distance;

// Create WiFi client and MQTT client instances
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// Define MQTT broker information
const char mqttBroker[] = "mqtt-dashboard.com";
int mqttPort = 1883;
const char mqttTopic[] = "SIT210Vansh/mywave";

// Define the measurement interval and variables to track time
const long measurementInterval = 1000;
unsigned long previousMillis = 0;

// Setup function for initializing serial communication
void setupSerial() {
  Serial.begin(9600);
  while (!Serial) {
    // Wait for the serial port to connect
  }
}

// Setup function for connecting to WiFi
void setupWiFi() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(wifiSSID, wifiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
}

// Function to connect to the MQTT broker
void connectToMQTTBroker() {
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(mqttBroker);

  if (!mqttClient.connect(mqttBroker, mqttPort)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  Serial.println("Connected to the MQTT broker!");
  Serial.println();
}

void setup() {
  setupSerial();        // Initialize serial communication
  setupWiFi();          // Connect to WiFi
  connectToMQTTBroker();  // Connect to the MQTT broker
}

void loop() {
  mqttClient.poll();  // Poll the MQTT client

  unsigned long currentMillis = millis();

  if (  measurementInterval<=currentMillis - previousMillis) {
    previousMillis = currentMillis;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration * 0.0343) / 2;
    Serial.print("Distance: ");
    Serial.println(distance);

    if (distance < 25) {
      mqttClient.beginMessage(mqttTopic);
      mqttClient.print("Wave detected, Distance: ");
      mqttClient.print(distance);
      mqttClient.endMessage();
      delay(1000);
    }

    Serial.println();

  }
}
