#include <ESP8266WiFi.h>

void setup() {
  pinMode(2, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(0, INPUT);
  Serial.begin(115200);
  digitalWrite(15, LOW);

  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
}
 
void loop() {
  digitalWrite(2, LOW);
  delay(500);
  int light = analogRead(A0);
  Serial.println(light);
  if (light < 600) { 
    digitalWrite(15, HIGH);
    digitalWrite(2, LOW);
    delay(3600000000);
    }
  else { ESP.deepSleep(3600000000); }
}
