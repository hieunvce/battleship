#include <ESP8266WiFi.h>
#include "SocketIOClient.h"

const int deviceID = 0;
const String deviceIDStr="0";
int button = 0;
const byte RX=D1;
const byte TX=D2;

SocketIOClient client;

//----------------Wifi Setup--------------------
const char* ssid = "wifi_ssid";
const char* password = "wifi_password";
//----------------------------------------------

//----------------Server setup------------------
char host[] = "192.168.200.145";
int port = 3000;
//----------------------------------------------

extern String RID;
extern String Rfull;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Baudrate for computer
  delay(10);

  // Connect to Wifi
  Serial.print("Connecting to wifi...");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print('.');
  }
  // Wifi connected
  Serial.println();
  Serial.println(F("Wifi connected"));
  Serial.println(F("IP Address of ESP8266 (Socket Client ESP8266): "));
  Serial.println(WiFi.localIP());

  // Connect to server
  if (!client.connect(host,port)){
    Serial.println(F("Connect to server failed!"));
    return;
  }
  // Server connected
  client.send("connection","message",deviceIDStr);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Receive button signal from NUC140

  // Send button message to server
  if (button==1 || button == 2 || button==3 || button==4 || button==5 || button==6){
    String buttonStr = String(button);
    String json_message = "{\"deviceID\":\""+deviceIDStr+"\",\"button\":\""+buttonStr+"\"}";
    client.send("button",json_message);
  }

  // Read message from server
  if (client.monitor()){
    // Print to computer console
    Serial.println(RID);
    Serial.print(' ');
    Serial.println(Rfull);

    // Send to Arduino
    
  }

  // Reconnect if disconnected
  if (!client.connected()){
    client.reconnect(host,port);
  }
}
