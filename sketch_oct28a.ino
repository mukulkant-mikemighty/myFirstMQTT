#include <WiFi.h>
#include<PubSubClient.h>
//HTTPClient http; 
const char* ssid ="Wokwi-GUEST";
const char*  password ="";
const char *mqtt_broker = "test.mosquitto.org";
const char *topic = "Mk";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;
String message="Hi, I am Mukul!!!";

int count=0;
WiFiClient espClient;
PubSubClient client(espClient);
void connectToMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting...");
    if (client.connect("Mukul01", mqtt_username, mqtt_password)) {//Mukul01 is clientID
      Serial.println("connected");
      client.publish(topic, "Hi from Mukul Kant");
      client.subscribe(topic);
    } else {
      Serial.print("Failed. state=");
      Serial.print(client.state());
      Serial.println(" retrying...");
      delay(5000);
    }
  }
}
void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived!!! ");
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
}
//String serverName = "https://webhook.site/#!/view/10f151b1-0c0f-4c85-9ab2-b713be4acd31/" ;
void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.println(".");
    delay(1000);
  }
  
  String IP= WiFi.localIP().toString();
  Serial.println(WiFi.localIP());
  
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  connectToMQTT();
  
  
  //Serial.println("Hello, ESP32-C3!");
  delay(1000);
}



void loop() {
  
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();

  
  message = "Hi, I am Mukul!!! Count: " + String(count);
  client.publish(topic, message.c_str());
  count++;

   
  delay(10); 
}
