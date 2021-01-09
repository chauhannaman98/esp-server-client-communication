// Import required libraries
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

/*String readTemp() {
  return String(bme.readTemperature());
  //return String(1.8 * bme.readTemperature() + 32);
}*/

String responseMessage = "This is an initial test messsage";

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();

  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/test", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", responseMessage.c_str());
  });

  // Start server
  server.begin();
}

void loop() {
  if(Serial.available() > 0)  {
    responseMessage = Serial.readString();
    Serial.println("Updated response message: "+responseMessage);
  }
}
