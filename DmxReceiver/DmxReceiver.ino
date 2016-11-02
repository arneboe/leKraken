#include <Wire.h>
#include "Conceptinetics.h"

#define INTERRUPT_PIN 4
#define MIN_TIME_BETWEEN_INTERRUPTS_MS 1
#define DMX_SLAVE_CHANNELS 18 //18 because index zero is ignored


DMX_Slave dmx_slave (DMX_SLAVE_CHANNELS);

void setup() {          
  dmx_slave.enable();  
  dmx_slave.setStartAddress(1);
  
  pinMode(INTERRUPT_PIN, INPUT);
  Wire.begin(); // join i2c bus (address optional for master)
}

void loop() 
{
  static unsigned long currentTime;
  static unsigned long lastSend = 0;
  currentTime = millis();
  const unsigned long timeDiff = currentTime - lastSend;

  if(currentTime - lastSend > MIN_TIME_BETWEEN_INTERRUPTS_MS &&
     digitalRead(INTERRUPT_PIN) == HIGH)
  {
      lastSend = currentTime;
      sendDmxData();
  }  
}

void sendDmxData()
{
  Wire.beginTransmission(8); // transmit to device #8
  //the dmx library starts ad adress 1. dmx channel 0 is always 0 and is ignored
  for(int i = 1; i < DMX_SLAVE_CHANNELS; ++i)
  {
    Wire.write(dmx_slave.getChannelValue(i));
  }
  Wire.endTransmission();    // stop transmitting
}

