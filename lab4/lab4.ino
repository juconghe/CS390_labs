#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "html_homepage.h"

#define PIN_BUTTON   0
#define PIN_LED     15
#define PIN_BUZZER  13


// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);
ESP8266WebServer server(80);

int r, g, b;
void on_homepage() {
  String html = FPSTR(html_homepage);
  server.send(200, "text/html", html);
}


void on_change_color() {
    r = server.arg("r").toInt();
    g = server.arg("g").toInt();
    b = server.arg("b").toInt();
    pixel.setPixelColor(0, pixel.Color(r, g, b));
    pixel.show();
    server.send(200, "");
}


void on_status() {
  String html = "";
  html += "{\"button\":";
  html += (1-digitalRead(PIN_BUTTON));
  html += ",\"light\":";
  html += (analogRead(A0));
  html += ",\"led\":\"(";
  html += r;
  html += ",";
  html += g;
  html += ",";
  html += b;
  html += ")\"}";

  server.send(200, "text/html", html);
} 

void setup() {
  pixel.begin();
  pixel.show();
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("group3_wifi");
  server.on("/", on_homepage);
  server.on("/js", on_status);
  server.on("/color_change", on_change_color);
  server.begin();
  
}

void loop() {
 server.handleClient();
}

