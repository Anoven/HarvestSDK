/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Sodaq_SHT2x.h>


/*********************************************************************************/
/* Defs for network connfiguration and MQTT Broker */
const char* ssid     = "harvest";
const char* password = "stemyleafy";
const char* mqtt_server = "104.238.164.118";

/* Update Frequency in seconds, this should not be less than one second */
const int sleepTime = 5;        

/* Node Information */
const char* manf = "Harvest Robotics";
const char* nodeId = "d3d170b2";
const char* deployedLocation = "Platform 9 & 3/4";
/*********************************************************************************/
















/*********************************************************************************/
/* System Defs */
RTC_DATA_ATTR int bootCount = 0;
#define uS_TO_S_FACTOR 1000000 
#define addr 0x4A
const char* firmVer = "00.00.001";
/*********************************************************************************/


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[500];
int value = 0;

/* read the battery voltage */
float readBatteryVoltage(){
  
  pinMode(26, OUTPUT);
  digitalWrite (26, LOW);
  delay(1);
  analogReadResolution(12);
  int analogValue = analogRead(34);
  pinMode(26, INPUT);


  return ((float)analogValue /4095.0) * 3.3;
}

/* Setup the WiFi Connection when required */
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/* reconnection */
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "SensorNode-";
    clientId += nodeId;
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 8883);
}

void loop() {
  StaticJsonDocument<500> doc;
  doc["irTemperature"] = SHT2x.GetTemperature();
  doc["batteryVoltage"] = readBatteryVoltage();
  doc["firmwareVersion"] = firmVer;
  doc["manufacturer"] = manf;
  doc["sampleDelay"] = sleepTime;
  doc["deployedLocation"] = deployedLocation;
  doc["nodeId"] = nodeId;
  doc["localIP"] = WiFi.localIP().toString();
  doc["avalibleServices"] = "IR Temperature(C),Battery Voltage(V)";
  
  serializeJson(doc, msg);
 
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish(nodeId, msg);
  
  /* here is the sleepy stuff */
  esp_sleep_enable_timer_wakeup(sleepTime * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}
