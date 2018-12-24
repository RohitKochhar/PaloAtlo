// Library inclusions ----------------------------------------------------------
#include <WiFiNINA.h>
#include <MQTT.h>
// Global Variables ------------------------------------------------------------
const char WIFI_SSID[] = "YOUR_WIFI_NAME";                                            // WiFI ssid
const char WIFI_PASS[] = "YOUR_WIFI_PASSWORD";                                        // WiFI password
const char MQTTHost[]  = "YOUR_COMPUTER'S_IP";                                        // Broker/Computer IP Address
int MQTTPort           = 1927;                                                        // MQTT Broker Port
char printbuf[100];                                                                   // Print format string
int status = WL_IDLE_STATUS;
const int NetworkStatusLight = 2;                                                     // Light showing status of network connection
const int LightIsOnLight = 4;                                                         // Light showing status of light sensor
// Class instantiations --------------------------------------------------------
WiFiClient wifiClient;
MQTTClient mqttClient;
// Base functions --------------------------------------------------------------
void setup() {
  Serial.begin(9600);                                                                 // Begin viewing on serial monitor
  pinMode(LightIsOnLight, OUTPUT);                                                    // Set pin 2 as output
  pinMode(NetworkStatusLight, OUTPUT);                                                // Set pin 4 as output
}

void loop() {
  mqttClient.loop();                                                                  // Listen for message publications
  (wifiClient.connected() == 1) ? digitalWrite(NetworkStatusLight, HIGH) : connect(); // Set network light on or reconnect.
  delay(500);                                                                         // Wait 500 ms before between loops.
}

// Helper functions -------------------------------------------------------------
void connect() {
  while ( status != WL_CONNECTED) {                                                   // If no connection is available, create one.
    Serial.print("Connecting to: ");
    Serial.println(WIFI_SSID);
    status = WiFi.begin(WIFI_SSID, WIFI_PASS);                                        // Start network with the credentials provided
    delay(5000);                                                                      // Wait 5 secons before retrying connection
  }
  Serial.println("Connected!");
  Serial.println("Connecting to light sensor.");
  mqttClient.begin(MQTTHost, MQTTPort, wifiClient);                                   // Connect to MQTT broker
  while (!mqttClient.connect("PaloAtloReceiver")) {
    Serial.print("*");
    delay(500);
  }
  Serial.println("Connected to light sensor!");
  mqttClient.subscribe("Light");                                                      // Subscribe to light topic
  mqttClient.onMessage(messageReceived);                                              // Call message received onMessage.
}

void messageReceived(String &topic, String &payload) {
  if (payload.toInt() > 1000){                                                        // Check if analog read of photoresistor is high (Low light returns 1000-1023)
    Serial.println("Light is off");
    digitalWrite(LightIsOnLight, LOW);                                                // Turn red light on
  }
  else {
    Serial.println("Light is on");
    digitalWrite(LightIsOnLight, HIGH);                                               // Turn red light off
  }
}
