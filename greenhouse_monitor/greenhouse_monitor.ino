/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_BME280.h>

const char* ssid     = "SerenityGardens";
const char* password = "SerenityGardens5830";

float room_temperature = 0.0;
int humidity = 0;
int soil_moisture1 = 0;
int soil_moisture2 = 0;

const int selectPins[3] = {12, 13, 14}; // S-pins to Arduino pins: S0~2, S1~3, S2~4

Adafruit_BME280 bme; // I2C


void setup() {
  
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  
  Serial.begin(115200);

  Wire.begin();

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (!bme.begin()) {  
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
}


void loop() {
  check_sensors();
  adjust_system();
  send_print_data();
  delay(1000);
}

void check_sensors() {
  soil_moisture1 = read_channel(7);
  soil_moisture2 = read_channel(6);
  room_temperature = bme.readTemperature();
  humidity = bme.readHumidity();
}


void send_print_data() {
  
  Serial.print("The Temp is: ");
  Serial.print(room_temperature);
  Serial.print(". The Humidity is: ");
  Serial.print(humidity);
  Serial.print(". The Soil 1 Moisture is: ");
  Serial.print(soil_moisture1);
  Serial.print(". The Soil 2 Moisture is: ");
  Serial.println(soil_moisture2);
}

void adjust_system() {
  if (room_temperature > 80 && humidity > 45) { digitalWrite(0, HIGH); }
}


int read_channel (int channel) {
  
  if (channel > 7) return -1; // Exit if pin is out of scope
  for (int i=0; i<3; i++)
  {
    if (channel & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }

  return analogRead(A0);
}

