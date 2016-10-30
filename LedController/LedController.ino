#include <Wire.h>

#define INTERRUPT_PIN 3

void setup() {
  pinMode(INTERRUPT_PIN, OUTPUT);
  digitalWrite(INTERRUPT_PIN, LOW);
  Wire.begin(8);               
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600);           
}

void loop() {
  delay(100);
  triggerDmxDataTransfer();
}

void triggerDmxDataTransfer()
{
  digitalWrite(INTERRUPT_PIN, HIGH);
  delayMicroseconds(500);
  digitalWrite(INTERRUPT_PIN, LOW);
}

void receiveEvent(int howMany) {
  while (Wire.available() > 0) 
  { 
    int x = Wire.read();
    Serial.print(x);
    Serial.print("\t");         
  }
  Serial.println();    
}
