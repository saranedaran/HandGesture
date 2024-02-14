#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "ultra.h"
#include "motor.h"
// Update these with values suitable for your network.

DynamicJsonDocument doc(1024);
float d;

const char* ssid = "Saran";
const char* password = "password";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String msg = "";
  for (int i = 0; i < length; i++) {
    // Serial.print((char)payload[i]);
    msg += (char)payload[i];
  }
  Serial.println(msg);

  deserializeJson(doc, msg);
  String device = doc["device"];
  String command = doc["command"];
  if (device == "robo1") {
    if (command == "forward") {
      forward();
    } else if (command == "reverse") {
      reverse();
    } else if (command == "stop") {
      stop();
    } else if (command == "right") {
      right();
    } else if (command == "left") {
      left();
    } else {
      Serial.println("unknown command ");
    }
  } else {
    Serial.println("unknown device");
  }
  d = dist();
  if (d < 10 or d > 1100) {
    Serial.println("object");
    stop();

  }
  else{
    Serial.println("moving");
  }
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("psna/robo/kit", "hello world");
      // ... and resubscribe
      client.subscribe("psna/robo/app");
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
  pinMode(BUILTIN_LED, OUTPUT);  // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  motor_init();
  ultra_init();
  d = dist();
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("psna/robo/kit", msg);
  }
}