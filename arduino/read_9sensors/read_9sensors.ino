#include <ArduinoJson.h>  // https://arduinojson.org/
// These constants won't change. They're used to give names to the pins used:
const int analogInPin1 = A0;  // Analog input pin that the potentiometer is attached to MQ-3    : Alcohol , Ethanol, Smoke
const int analogInPin2 = A1;  // Analog input pin that the potentiometer is attached to MQ-135  : Nox
const int analogInPin3 = A2;  // Analog input pin that the potentiometer is attached to MQ-138  : Acetone,Benzene,Hydrogen,Toluene,Formaldehyde,Alcoho
const int analogInPin4 = A3;  // Analog input pin that the potentiometer is attached to MQ-136  : H2S
const int analogInPin5 = A4;  // Analog input pin that the potentiometer is attached to TGS2611 : Methane
const int analogInPin6 = A5;  // Analog input pin that the potentiometer is attached to MG-811  : Carbon Dioxide(CO2)
const int analogInPin7 = A6;  // Analog input pin that the potentiometer is attached to MQ-137  : Ammonia
const int analogInPin8 = A7;  // Analog input pin that the potentiometer is attached to MQ-5    : LPG,Methane
const int analogInPin9 = A8;  // Analog input pin that the potentiometer is attached to MQ-131  : Ozone

int sensorValue1 = 0;        // value read from the pot
int sensorValue2 = 0;        // value read from the pot
int sensorValue3 = 0;        // value read from the pot
int sensorValue4 = 0;        // value read from the pot
int sensorValue5 = 0;        // value read from the pot
int sensorValue6 = 0;        // value read from the pot
int sensorValue7 = 0;        // value read from the pot
int sensorValue8 = 0;        // value read from the pot
int sensorValue9 = 0;        // value read from the pot

StaticJsonDocument<200> doc;  // <- a little more than 200 bytes in the stack

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);


}

void show_sesor(){
  // print the results to the Serial Monitor:
  Serial.print (" s1 = ");
  Serial.print ( sensorValue1);
  Serial.print (" s2 = ");
  Serial.print ( sensorValue2);
  Serial.print (" s3 = ");
  Serial.print ( sensorValue3);
  Serial.print (" s4 = ");
  Serial.print ( sensorValue4);
  Serial.print (" s5 = ");
  Serial.print ( sensorValue5);
  Serial.print (" s6 = ");
  Serial.print ( sensorValue6);
  Serial.print (" s7 = ");
  Serial.print ( sensorValue7);
  Serial.print (" s8 = ");
  Serial.print ( sensorValue8);
  Serial.print (" s9 = ");
  Serial.println ( sensorValue9);
}

void loop() {
  // read the analog in value:
  sensorValue1 = analogRead(analogInPin1);
  sensorValue2 = analogRead(analogInPin2);
  sensorValue3 = analogRead(analogInPin3);
  sensorValue4 = analogRead(analogInPin4);
  sensorValue5 = analogRead(analogInPin5);
  sensorValue6 = analogRead(analogInPin6);
  sensorValue7 = analogRead(analogInPin7);
  sensorValue8 = analogRead(analogInPin8);
  sensorValue9 = analogRead(analogInPin9);

  doc["sensor"] = "gas";
  doc["time"]   = millis();  //go back to zero after approximately 50 days
  doc["data"][0] = sensorValue1;
  doc["data"][1] = sensorValue2;
  doc["data"][2] = sensorValue3;
  doc["data"][3] = sensorValue4;
  doc["data"][4] = sensorValue5;
  doc["data"][5] = sensorValue6;
  doc["data"][6] = sensorValue7;
  doc["data"][7] = sensorValue8;
  doc["data"][8] = sensorValue9;

  serializeJson(doc, Serial);
  Serial.println ();

  // wait 100 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(100);
}
