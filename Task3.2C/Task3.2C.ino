#include <WiFiNINA.h>

//please enter your sensitive data in the Secret tab
char ssid[] = "iPhone";
char pass[] = "12345666";

WiFiClient client;
const int ldrPin = A0;
char HOST_NAME[] = "maker.ifttt.com";                                                                //Set the host name for IFTTT
String PATH_NAME = "/trigger/SunLightPresent/with/key/phqmslABUAaVa7weS_RRqc97mgk6UXsI93QdH4qzLjV";  // Set the path for sunlight event
bool previousSunlightState = false;

void setup() {
  // initialize WiFi connection
  WiFi.begin(ssid, pass);

  Serial.begin(9600);  // Start serail communication
  while (!Serial)
    ;

  // Connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  } else {  // if not connected:
    Serial.println("connection failed");
  }
}
void loop() {
  check_sensor_value();
}
void check_sensor_value() {
  int Sensorvalue = analogRead(ldrPin);  // Read analog value from LDR sensor
  Serial.println(Sensorvalue);           // Print the Sensor value to the monitor

  bool currSunlightState = Sensorvalue < 100;  // Determine if  sunlight present based on  threshold for LDR value

  if (currSunlightState != previousSunlightState) {
    previousSunlightState = currSunlightState;

    if (currSunlightState) {
      //  Is sunlight present then send HTTP request for sunlight:
      httpRequest(PATH_NAME);  // Call function to send HTTP request for sunlight event
    }
  }
  delay(500);  // Delay for 1/2 second before the next iteration
}
void httpRequest(String PATH_NAME) {
  // make a HTTP request:
  // send HTTP header
  client.println("GET " + PATH_NAME + " HTTP/1.1");
  client.println("Host: " + String(HOST_NAME));
  client.println("Connection: close");
  client.println();  // end HTTP header

  while (client.connected()) {
    if (client.available()) {
      // read an incoming byte from the server and print it to serial monitor:
      char c = client.read();
      Serial.print(c);
    }
  }

  // the server's disconnected, stop the client:
  client.stop();
  Serial.println();
  Serial.println("disconnected");
}