// Library inclusions -------------------------------------------------
#include <WiFiNINA.h>
#include <MQTT.h>
// Global Variables ---------------------------------------------------
const char WIFI_SSID[] = "YOUR_WIFI_NAME";                                // WiFI ssid
const char WIFI_PASS[] = "YOUR_WIFI_PASSWORD";                            // WiFI password
const char MQTTHost[]  = "YOUR_COMPUTER'S_IP";                            // Broker/Computer IP Address
const int  MQTTPort    = 1927;                                            // MQTT Broker port
char printbuf[100];                                                       // Print format buffer
const int photoResistor = A0;
int status = WL_IDLE_STATUS;
// Class instantiations -----------------------------------------------
WiFiClient wifiClient;
MQTTClient mqttClient;
// Base functions -----------------------------------------------------
void setup() {
  Serial.begin(9600);                                                     // Begin Serial monitor
}

void loop() {
  mqttClient.loop();                                                      // Listen for MQTT events
  if (!wifiClient.connected())                                            // Check if we need to reconnect
    connect();
  getLightStatus();                                                       // Read photoresistor
  delay(500);                                                             // Wait 500 ms before next loop
}
// Helper functions ----------------------------------------------------
void connect() {
  while ( status != WL_CONNECTED) {                                       // Check connection, if none, connect
    Serial.print("Connecting to : ");
    Serial.println(WIFI_SSID);
    status = WiFi.begin(WIFI_SSID, WIFI_PASS);                            // Log in with credentials
    delay(5000);                                                          // Wait 5 seconds before reconnecting
  }
  Serial.println("Connected!");
  Serial.print("Connecting to MQTT at ");
  Serial.print(MQTTHost);
  Serial.print(":");
  Serial.print(MQTTPort);
  Serial.println(".");
  mqttClient.begin(MQTTHost, MQTTPort, wifiClient);
  while (!mqttClient.connect("PaloAtloSender")) {                         // Connect to broker as PaloAtloSender
    Serial.print("*");
    delay(500);
  }
  Serial.println("Connected to MQTT");
}

void getLightStatus(){
  Serial.println(analogRead(photoResistor));                              // Print photoresistor value
  sprintf(printbuf, "%d", analogRead(photoResistor));                     // Convert to string
  mqttClient.publish("Light", printbuf);                                  // Publish to light topic
}
