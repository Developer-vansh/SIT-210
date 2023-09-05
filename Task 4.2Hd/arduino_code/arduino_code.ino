#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>

const char* ssid = "iPhone";
const char* password = "12345666";
const char* serverAddress = "172.20.10.4";
const int serverPort = 3000;
const int ledPinRed = 2;   // Define the pin for the red LED
const int ledPinGreen = 3; // Define the pin for the green LED
const int ledPinBlue = 4;  // Define the pin for the blue LED

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(ledPinRed, OUTPUT);   // Set the red LED pin as an output
  pinMode(ledPinGreen, OUTPUT); // Set the green LED pin as an output
  pinMode(ledPinBlue, OUTPUT);  // Set the blue LED pin as an output

  // Connect to Wi-Fi
  connectToWiFi();
}

void loop() {
  // Make an HTTP GET request to your server
  String response = sendGetRequest("/send");

  // Process the response data
  Serial.println("Response from server:");
  Serial.println(response);

  // Parse boolean values for red, green, and blue
  bool redValue = response.indexOf("red\":true") != -1;
  bool greenValue = response.indexOf("green\":true") != -1;
  bool blueValue = response.indexOf("blue\":true") != -1;
Serial.print("RedLight-");
Serial.println(redValue);
Serial.print("GreenLight-");
Serial.println(greenValue);
Serial.print("BlueLight-");
Serial.println(blueValue);
  // Control the LEDs based on boolean values
  digitalWrite(ledPinRed, redValue ? HIGH : LOW);     // Turn on/off the red LED
  digitalWrite(ledPinGreen, greenValue ? HIGH : LOW); // Turn on/off the green LED
  digitalWrite(ledPinBlue, blueValue ? HIGH : LOW);   // Turn on/off the blue LED

  delay(2000); // Adjust the delay as needed
}

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
}

String sendGetRequest(String endpoint) {
  WiFiClient client;
  if (client.connect(serverAddress, serverPort)) {
    // Make an HTTP GET request
    client.print("GET " + endpoint + " HTTP/1.1\r\n");
    client.print("Host: " + String(serverAddress) + "\r\n");
    client.print("Connection: close\r\n\r\n");

    // Wait for a response
    while (!client.available()) {
      delay(100);
    }

    // Read and discard the headers
    while (client.available()) {
      String line = client.readStringUntil('\r');
      if (line == "\n") {
        break; // Headers end with a blank line
      }
    }

    // Read the content
    String response = "";
    while (client.available()) {
      char c = client.read();
      response += c;
    }

    client.stop();

    // Return only the content part
    return response;
  } else {
    Serial.println("Failed to connect to the server.");
    return "";
  }
}
