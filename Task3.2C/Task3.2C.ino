#include <WiFiNINA.h>

//please enter your sensitive data in the Secret tab
char ssid[] = "iPhone";
char pass[] = "12345666";

WiFiClient client;

char   HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME   = "/trigger/SunLightPresent/with/key/phqmslABUAaVa7weS_RRqc97mgk6UXsI93QdH4qzLjV"; // change your EVENT-NAME and YOUR-KEY
const int SensorPin = A0; 
bool prevSunlightState = false;

void setup() {
  // initialize WiFi connection
  WiFi.begin(ssid, pass);

  Serial.begin(9600);
  while (!Serial);

  // connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  }
  else {// if not connected:
    Serial.println("connection failed");
  }

}

void loop() {
  int Sensorvalue = analogRead(SensorPin);  // Read analog value from LDR sensor
  Serial.println(Sensorvalue);  // Print the Sensor value to the monitor

  bool currSunlightState = Sensorvalue < 100;  // Determine if it's currently sunlight based on LDR value threshold

  if (currSunlightState != prevSunlightState) {
    prevSunlightState = currSunlightState;

    if (currSunlightState) {
      //  Is sunlight present then send HTTP request for sunlight:
      httpRequest(PATH_NAME);  // Call function to send HTTP request for sunlight event
    } 
  }
  delay(500);  // Delay for 1/2 second before the next iteration
}
void httpRequest(String PATH_NAME){

    // make a HTTP request:
    // send HTTP header
    client.println("GET " + PATH_NAME + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header

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