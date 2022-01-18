/**
 * Simple Arduino program for an ESP286 microcontroller
 * that polls temperature and humidity values from a
 * DHT22 sensor and transmits them via HTTP POST as
 * a JSON document.
 */

#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

#include "parameters.h"

#define CONTENT_TYPE "application/json"
#define LED_PIN 2

// Enable ESP.getVCC()
ADC_MODE(ADC_VCC);

// DHT driver
DHT dht(DHT_GPIO_PIN, DHT_TYPE);

// HTTP Client
#if WIFI_ENABLED
WiFiClient wifiClient;
HttpClient httpClient = HttpClient(wifiClient, HTTP_ADDRESS, HTTP_PORT);
#endif

//
int counter = 0;
float vcc;
float temp;
float humid;

// Setup function
void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println();
    Serial.println("....");
    delay(15);
    Serial.println("*****************************");
    Serial.println("Starting up");
    Serial.println("*****************************");
    Serial.println();

    setup_wifi();
    dht.begin();
    pinMode(LED_PIN, OUTPUT);
}

// Connect to WiFi network
void setup_wifi(){
#if WIFI_ENABLED
  Serial.println();
  Serial.print("HTTP Server address: ");
  Serial.print(HTTP_ADDRESS);
  Serial.print(" port: ");
  Serial.println(HTTP_PORT);
  
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.print("WiFi connected, IP: ");  
  Serial.println(WiFi.localIP());
  Serial.println();
#else
  Serial.println("No WiFi support compiled in");
#endif
}

// Main loop
void loop(){
    digitalWrite(LED_PIN, LOW);

    read_state();
    //  dump_state();

    Serial.print("JSON: ");
    String json = get_json();
    Serial.print(json);
    send_json(json);

    counter++;

    digitalWrite(LED_PIN, HIGH);

    delay(MAIN_INTERVAL);
}

void read_state(){
  vcc   = ESP.getVcc();
  humid = dht.readHumidity();
  temp  = dht.readTemperature();
}

//void dump_state(){
//  Serial.print("c=");    Serial.print(counter);
//  Serial.print(" vcc="); Serial.print(vcc);
//  Serial.print(" t=");   Serial.print(temp);
//  Serial.print(" h=");   Serial.print(humid);
//  Serial.println();
//}

String get_json(){
    const int json_capacity = JSON_OBJECT_SIZE(4);
    StaticJsonDocument<json_capacity> json_doc;

    json_doc["counter"].set(counter);
    json_doc["vcc"].set(vcc);
    json_doc["temp"].set(temp);
    json_doc["humid"].set(humid);

    // TODO: use static memory allocation
    String json = "";
    serializeJson(json_doc, json);

    return json;
}

void send_json(String json){
#if WIFI_ENABLED
  Serial.print("Sending data... ");
  httpClient.beginRequest();
  httpClient.post(HTTP_PATH);
  httpClient.sendHeader("Content-Type", CONTENT_TYPE);
  httpClient.sendHeader("Content-Length", json.length());
  //httpClient.sendHeader("X-Custom-Header", "custom-header-value");
  httpClient.beginBody();
  httpClient.print(json);
  httpClient.endRequest();

  int statusCode  = httpClient.responseStatusCode();
  String response = httpClient.responseBody();

  Serial.print("status=");      Serial.print(statusCode);
  Serial.print(", response=");  Serial.println(response);
#endif
}
