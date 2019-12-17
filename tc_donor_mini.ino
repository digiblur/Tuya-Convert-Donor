// Thanks for @marcusone on Discord for putting this together!  
// Flash the bin to your NodeMCU or Wemos D1 mini and just feed it some power. 
// Solid onboard LED means it is connected to vtrust-flash

#include <Arduino.h>
#include <ESP8266WiFi.h>

#define wifi_ssid "vtrust-flash"
#define wifi_password "flashmeifyoucan"

#define LED 2

bool wifiConnected = false;

void blink(int cnt, unsigned long blink_speed) {
  for(int i=0; i < cnt; i++) {
    digitalWrite(LED, LOW);
    delay(blink_speed);
    digitalWrite(LED, HIGH);
    delay(blink_speed);
  }
  return;
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);
  WiFi.persistent(false);
  WiFi.forceSleepWake();
  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    blink(2,250);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(150);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  Serial.println("Start");

  setup_wifi();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();
  if(WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED, LOW);
    if(!wifiConnected) Serial.println("Connected");
    wifiConnected = true;
  } else {
    digitalWrite(LED, HIGH);
    if(wifiConnected) Serial.println("Disconnected!");
    wifiConnected = false;
    blink(2,250);
  }
}
