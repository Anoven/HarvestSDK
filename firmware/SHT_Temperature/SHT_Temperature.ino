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


/*********************************************************************************/
/* Defs for network connfiguration and MQTT Broker */
const char* ssid     = "VIRGIN253";
const char* password = "97523E59";
const char* mqtt_server = "138.197.156.151";
int port = 1883;

/* Update Frequency in seconds, this should not be less than one second */
const int sleepTime = 5;        

/* Node Information */
const char* manf = "Harvest Robotics";
#define NODE_ID "cae7032a"
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

/* read the temperature data from the sensor */
float readSTS21()
{
  Wire.begin();
  unsigned int data[2];

  // Start I2C Transmission
  Wire.beginTransmission(addr);
  // Select no hold master
  Wire.write(0xF3);
  // End I2C Transmission
  Wire.endTransmission();
  delay(300);

  // Request 2 bytes of data
  Wire.requestFrom(addr, 2);

  // Read 2 bytes of data
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data
  int rawtmp = data[0] * 256 + data[1];
  int value = rawtmp & 0xFFFC;
  double cTemp = -46.85 + (175.72 * (value / 65536.0));
  double fTemp = cTemp * 1.8 + 32;
  
  return cTemp;
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
    clientId += NODE_ID;
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
  client.setServer(mqtt_server, port);
}

void loop() {
  StaticJsonDocument<500> doc;
//  char test[500]= "test";
  doc["temperature"] = readSTS21();
  doc["batteryVoltage"] = readBatteryVoltage();
  doc["firmwareVersion"] = firmVer;
  doc["manufacturer"] = manf;
  doc["sampleDelay"] = sleepTime;
  doc["deployedLocation"] = deployedLocation;
  doc["nodeId"] = NODE_ID;
  doc["localIP"] = WiFi.localIP().toString();
  doc["avalibleServices"] = "Temperature, Battery Voltage";
  
  int num_written = serializeJson(doc, msg);
  client.loop();
 
  if (!client.connected()) {
    reconnect();
  }

  long now = millis();
  
  Serial.print("Publish message: ");
//  Serial.print(num_written);
  for (int x = 0; x<num_written;x++){
    Serial.print(msg[x], HEX);
    Serial.print(" ") ;
  }
  Serial.println();
  
  client.publish(NODE_ID, msg);
  
  /* here is the sleepy stuff */
  esp_sleep_enable_timer_wakeup(sleepTime * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}
