// Import libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

//Define blinking LED pin
#define LED 2

// Create WiFiMulti instance
ESP8266WiFiMulti WiFiMulti;

// AP credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

// IP address or domain name with URL path
const char* serverNameTemp = "http://192.168.4.1/test";

String response;

unsigned long previousMillis = 0;
const long interval = 4000;  // time in milliseconds
int errorCount = 0;

void setup() {
  // Start serial monitor for debugging
  Serial.begin(115200);
  Serial.println();

  pinMode(LED, OUTPUT); // Initialize the LED pin as an output
  digitalWrite(LED, HIGH);

  // Connect to ESP8266 server
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
  while ((WiFiMulti.run() == WL_CONNECTED)) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Check WiFi connection status
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      response = httpGETRequest(serverNameTemp);
      Serial.println("Response: " + response);

      // save the last HTTP GET Request
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  // IP address with path or Domain name with URL path
  http.begin(client, serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "--";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    digitalWrite(LED, LOW); // turn LED on
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    digitalWrite(LED, HIGH);  // turn LED off
  }
  // Free resources
  http.end();

  return payload;
}
