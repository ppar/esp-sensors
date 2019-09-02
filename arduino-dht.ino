/**
 *
 *
 */

#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include "parameters.h"

//
// "application/x-www-form-urlencoded"
#define CONTENT_TYPE "application/json"
#define LED_PIN 2

// Enable ESP.getVCC()
ADC_MODE(ADC_VCC);

// DHT driver
DHT dht(DHT_GPIO_PIN, DHT_TYPE);

// HTTP Client
WiFiClient wifiClient;
HttpClient httpClient = HttpClient(wifiClient, HTTP_ADDRESS, HTTP_PORT);

//
int counter = 0;
float vcc;
float temp;
float humid;

// Setup function
void setup() {
  Serial.begin(115200);
  delay(10);
  setup_wifi();
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
}

// Connect to WiFi network
void setup_wifi(){
  Serial.println();
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
}

// Main loop
void loop(){ 
  digitalWrite(LED_PIN, LOW);

  read_state();
  dump_state();
  
  String json = get_json();
  Serial.print("JSON: ");  Serial.println(json);
  send_json(json);

  counter++;

  digitalWrite(LED_PIN, HIGH);

  delay(10000);
}

void read_state(){
  vcc   = ESP.getVcc();
  humid = dht.readHumidity();
  temp  = dht.readTemperature();
}

void dump_state(){
  Serial.print("c=");    Serial.print(counter);
  Serial.print(" vcc="); Serial.print(vcc);
  Serial.print(" t=");   Serial.print(temp);
  Serial.print(" h=");   Serial.print(humid);    
  Serial.println();
}

String get_json(){
  String json = "{";

  json += "\"counter\":\"";   json += counter;
  json += ",\"vcc\":";        json += vcc;
  json += ",\"temp\":";       json += temp;
  json += ",\"humid\":";      json += humid;

  json += "\}";

  return json;
}

void send_json(String json){
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
}

