
#include <ArduinoJson.h> 
#include "lr_model.h"
Eloquent::ML::Port::LogisticRegression clf;


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

int sensor_mq3 = 0;        // value read from the pot
int sensor_mq135 = 0;        // value read from the pot
int sensor_mq138 = 0;        // value read from the pot
int sensor_mq136 = 0;        // value read from the pot
int sensor_tgs2611 = 0;        // value read from the pot
int sensor_mg811 = 0;        // value read from the pot
int sensor_mq137 = 0;        // value read from the pot
int sensor_mq5 = 0;        // value read from the pot
int sensor_mq131 = 0;        // value read from the pot

StaticJsonDocument<200> doc;  // <- a little more than 200 bytes in the stack

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);


}


void show_sesor(){
  // print the results to the Serial Monitor:
  Serial.print (" s1 = ");
  Serial.print ( sensor_mq3);
  Serial.print (" s2 = ");
  Serial.print ( sensor_mq135);
  Serial.print (" s3 = ");
  Serial.print ( sensor_mq138);
  Serial.print (" s4 = ");
  Serial.print ( sensor_mq136);
  Serial.print (" s5 = ");
  Serial.print ( sensor_tgs2611);
  Serial.print (" s6 = ");
  Serial.print ( sensor_mg811);
  Serial.print (" s7 = ");
  Serial.print ( sensor_mq137);
  Serial.print (" s8 = ");
  Serial.print ( sensor_mq5);
  Serial.print (" s9 = ");
  Serial.print ( sensor_mq131);
}

void loop() {
  // read the analog in value:
  char const *predicted_label;
  float feature[7] ;
  
  sensor_mq3 = analogRead(analogInPin1);
  sensor_mq135 = analogRead(analogInPin2);
  sensor_mq138 = analogRead(analogInPin3);
  sensor_mq136 = analogRead(analogInPin4);
  sensor_tgs2611 = analogRead(analogInPin5);
  sensor_mg811 = analogRead(analogInPin6);
  sensor_mq137 = analogRead(analogInPin7);
  sensor_mq5 = analogRead(analogInPin8);
  sensor_mq131 = analogRead(analogInPin9);

  doc["sensor"] = "gas";
  doc["time"]   = millis();  //go back to zero after approximately 50 days
  doc["data"][0] = sensor_mq3;
  doc["data"][1] = sensor_mq135;
  doc["data"][2] = sensor_mq138;
  doc["data"][3] = sensor_mq136;
  doc["data"][4] = sensor_tgs2611;
  doc["data"][5] = sensor_mg811;
  doc["data"][6] = sensor_mq137;
  doc["data"][7] = sensor_mq5;
  doc["data"][8] = sensor_mq131;

//  feature[0]=sensor_mq3;
//  feature[1]=sensor_mq135;
//  feature[2]=sensor_mq138;
//  feature[3]=sensor_mq136;
//  feature[4]=sensor_tgs2611;
//  feature[5]=sensor_mg811;
//  feature[6]=sensor_mq137;
//  feature[7]=sensor_mq5;
//  feature[8]=sensor_mq131; 

  feature[0]=sensor_mq3;
  feature[1]=sensor_mq135;
  feature[2]=sensor_tgs2611;
  feature[3]=sensor_mq137;
  feature[4]=sensor_mq5;
  feature[5]=sensor_mq136;
 

  /* float dummy[9] = {384,378,431,568,497,95,746,744,320};
  for( int  k=0; k <9; k++  ){
    feature[k] = dummy[k] ;
  }
  */
  
  predicted_label = clf.predictLabel(feature);
  doc["prediction"] = predicted_label;

  serializeJson(doc, Serial);
  Serial.println ();

  // wait 100 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(100);
}
