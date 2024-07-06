#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

#include "ThingSpeak.h"
#include "PubSubClient.h"

Adafruit_ADS1115 ads; /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */
char ssid[] = "Airtel-MyWiFi-AMF-311WW-FBB2";
char pass[] = "31dbdd09";
const char* server = "mqtt3.thingspeak.com";

WiFiClient client;
PubSubClient mqttClient(client);

int port = 1883;

unsigned long myChannelNumber = 2508603;
const char* myWriteAPIKey = "95EZZPOYBBB172Y5";

String myStatus = "";

float a1, a2,a3;

const char* mqttUserName = "DTwXHCAVLBYzPBY1IQwBEx0";

const char* mqttPass = "5yPkgwq0pUOdhCskTgI2/UpP";

const char* clientID="DTwXHCAVLBYzPBY1IQwBEx0";


void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);
  ads.setGain(GAIN_FOUR);
  ads.begin();
  WiFi.mode(WIFI_STA);
  mqttClient.setServer(server,port);
}

void loop() {

  int16_t adc1, adc2;
  float v1, v2;

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println("Sriram");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  adc1 = ads.readADC_Differential_0_1();
  adc2 = ads.readADC_Differential_2_3();

  v1 = ads.computeVolts(adc1);
  v2 = ads.computeVolts(adc2);

  a1 = v1 * 15;
  a2 = v2 * 15;

  Serial.println(a1);
  Serial.println(a2);
  Serial.println("------");
  while(mqttClient.connected()== NULL){
     Serial.println("COnnecting to mqtt...");
     mqttClient.connect(clientID, mqttUserName, mqttPass);
     delay(1000);
  }
  mqttClient.loop();
  // thingspook(a1, a2);
  if(a2<0)
  {
    a3=-a2;
  }
  else
  {
    a3=a2;
  }
  
  String dataString = "field1=" + String(a1) + "&field2=" + String(a3);
  String topicString ="channels/" + String( myChannelNumber ) + "/publish";
  mqttClient.publish( topicString.c_str(), dataString.c_str());

  delay(1000);
}
