/*
        xi - Riemann esp8266 Client Example
*/

const char wifi_ssid[] = "WIFINAME";
const char wifi_pass[] = "WIFIPASSWORD";

const char      riemann_server_url[] = "example.com";
const uint16_t  riemann_server_port  = 5555;

#include <ESP8266WiFi.h>

#include "xi.h"

WiFiClient wifi_client;

Xi riemannClient(&wifi_client);

void connectWiFi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);

  connectWiFi();

  riemannClient.setServer(riemann_server_url, riemann_server_port);
}


void loop() {
  delay(3000);

  RiemannEventMsg riemann_event;

  riemann_event.setHostname("nodemcu");
  riemann_event.setService("test_service");
  riemann_event.setMetricF(3.14);

  riemannClient.sendEvent(riemann_event);
}
