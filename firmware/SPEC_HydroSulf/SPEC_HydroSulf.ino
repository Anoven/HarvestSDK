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
const char* nodeId = "339e5d61";
const char* deployedLocation = "Platform 9 & 3/4";
/*********************************************************************************/
















/*********************************************************************************/
/* System Defs */
RTC_DATA_ATTR int bootCount = 0;
#define uS_TO_S_FACTOR 1000000 
#define addr 0x4A
const char* firmVer = "00.00.001";

String SensorSerialNo; 
int H2S;
int Temperature;
int RH;
int RawSensor;
int TempDigital;
int RHDigital;
int Days;
int Hours;
int Minutes;
int Seconds;

#define command_delay 500
#define start_delay 2500
String dataString = "";
String responseString = "";
boolean dataStringComplete = 0;
char inChar;
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
  client.setServer(mqtt_server, port);
  
  // setup for HS sensor
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  Serial2.setTimeout(900);

  dataString.reserve(150);
  responseString.reserve(150);
  delay(1000);
  flush_serial2();
}

void loop() {
  SPEC_Data_read();
  SPEC_parse_data();
  StaticJsonDocument<500> doc;
  doc["temperature"] = (float)Temperature;
  doc["hsLevel"] = H2S;
  doc["hummidity"] = (float)RH;
  doc["batteryVoltage"] = readBatteryVoltage();
  doc["firmwareVersion"] = firmVer;
  doc["manufacturer"] = manf;
  doc["sampleDelay"] = sleepTime;
  doc["deployedLocation"] = deployedLocation;
  doc["nodeId"] = nodeId;
  doc["localIP"] = WiFi.localIP().toString();
  doc["avalibleServices"] = "Temperature(C), H2S(ppb), Hummidity(%RH), Battery Voltage(V)";
  
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

void SPEC_Data_read(){
  // First, we do some initialization
  // dataStringComplete is set as "false", as we don't have any valid data received
  dataStringComplete = 0;
  // Clear the data string
  dataString = "";
  // Now we trigger a measurement
  Serial2.print("\r");
  // We wait for the sensor to respond
  dataString = Serial2.readStringUntil('\n');
  Serial.println(dataString);
}

void SPEC_parse_data(){
  int idx1 = dataString.indexOf(',');
  SensorSerialNo = dataString.substring(0, idx1);
  int idx2 = dataString.indexOf(',', idx1 + 1);
  // Hint: after comma there's a space - it should be ignored
  String S_gas = dataString.substring(idx1 + 2, idx2);
  H2S = S_gas.toInt();
  int idx3 = dataString.indexOf(',', idx2 + 1);
  String S_temp = dataString.substring(idx2 + 2, idx3);
  Temperature = S_temp.toInt();
  int idx4 = dataString.indexOf(',', idx3 + 1);
  String S_humi = dataString.substring(idx3 + 2, idx4);
  RH = S_humi.toInt();
  int idx5 = dataString.indexOf(',', idx4 + 1);
  String S_raw_gas = dataString.substring(idx4 + 2, idx5);
  RawSensor = S_raw_gas.toInt();
  int idx6 = dataString.indexOf(',', idx5 + 1);
  String S_Tdigital = dataString.substring(idx5 + 2, idx6);
  TempDigital = S_Tdigital.toInt();
  int idx7 = dataString.indexOf(',', idx6 + 1);
  String S_RHdigital = dataString.substring(idx6 + 2, idx7);
  RHDigital = S_RHdigital.toInt();
  int idx8 = dataString.indexOf(',', idx7 + 1);
  String S_Days = dataString.substring(idx7 + 2, idx8);
  Days = S_Days.toInt();
  int idx9 = dataString.indexOf(',', idx8 + 1);
  String S_Hours = dataString.substring(idx8 + 2, idx9);
  Hours = S_Hours.toInt();
  int idx10 = dataString.indexOf(',', idx9 + 1);
  String S_Minutes = dataString.substring(idx9 + 2, idx10);
  Minutes = S_Minutes.toInt();
  int idx11 = dataString.indexOf('\r');
  String S_Seconds = dataString.substring(idx10 + 2, idx11);
  Seconds = S_Seconds.toInt();
}

void flush_serial2(){
  // Do we have data in the serial buffer?
  // If so, flush it
  if (Serial2.available() > 0){
    Serial.println ("Flushing serial buffer...");
    while(1){
      inChar = (char)Serial2.read();
      delay(10);
      Serial.print(inChar);
      if (inChar == '\n') break; 
    }
    Serial.println (" ");
    Serial.println ("Buffer flushed!");
  }
}
