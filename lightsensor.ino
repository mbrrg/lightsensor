#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define HA_URL      "http://xxxxxx/api/states/sensor.light_level"
#define WIFI_SSID   "xxxxxxx"
#define WIFI_PSK    "xxxxxxx"

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Initiating wifi connection.");

  WiFi.begin(WIFI_SSID, WIFI_PSK);
  WiFi.setAutoReconnect(true);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection");
  }  
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int value = analogRead(A0);
    String payload = "{\"state\": \"";
    payload = payload + value;
    payload = payload + "\", \"attributes\": {\"unit_of_measurement\": \"units\", \"friendly_name\": \"Light\"}}";
   
    HTTPClient http;  
    http.begin(HA_URL);
    http.addHeader("Content-Type", "application/json");
      
    int status = http.POST(payload);    

    if (status >= 400) {
      Serial.println("HA http status:");
      Serial.println(status);
    }
  
    http.end();  
  }

  delay(30000);
}
