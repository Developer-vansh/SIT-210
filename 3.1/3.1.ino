#include <DHT.h>
#include <ThingSpeak.h>
#include <WiFiNINA.h>

#define SENSOR_PIN 3
#define SENSOR_TYPE DHT11
DHT sensor(SENSOR_PIN, SENSOR_TYPE);

char wifiSSID[] = "iPhone";
char wifiPassword[] = "12345666";
WiFiClient wifiClient;

 int channelNumber = 2249427;
const char *channelAPIKey = "EBR8OAZUH0L8MRJ1";

void setup() {
  Serial.begin(9600);
  connectWiFi();
  sensor.begin();
  ThingSpeak.begin(wifiClient);
}

void loop() {
  delay(3000);

  float tempCelsius = sensor.readTemperature();
  float humidityPercent = sensor.readHumidity();

  if (!isnan(tempCelsius) && !isnan(humidityPercent)) {
    sendSensorDataToThingSpeak(tempCelsius, humidityPercent);
  } else {
    Serial.println("Failed to read data from sensor!");
  }
  
  delay(30000);
}

void connectWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(wifiSSID, wifiPassword);
    delay(1000);
  }
  Serial.println("Succesfully Connected to WiFi");
}

void sendSensorDataToThingSpeak(float temp, float humid) {
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, humid);
  
  int statusCode = ThingSpeak.writeFields(channelNumber, channelAPIKey);

  if (statusCode == 200) {
    Serial.println("Sending Data to Thingspeak");
  } else {
    Serial.println("Failed to send data to Thingspeak");
  }
}
