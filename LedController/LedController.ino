#define LED_TYPE WS2811
#define INTERRUPT_PIN 3 //pin used to tell dmx buffer to send data via i2c

#define LEDS_PER_TENTACLE 60
#define NUM_TENTACLES 4
#define NUM_LEDS (LEDS_PER_TENTACLE * NUM_TENTACLES)
#define LED_COLOR_ORDER RGB
#define TENTACLE_PIN_0 4
#define TENTACLE_PIN_1 5
#define TENTACLE_PIN_2 6
#define TENTACLE_PIN_3 7
#define NUM_DMX_CHANNELS 16

//DMX channels:
#define DMX_EFFECT     0
#define DMX_SPEED      1
#define DMX_STROBE     2
#define DMX_BRIGHTNESS 3
#define DMX_BASE_0_R   4
#define DMX_BASE_0_G   5
#define DMX_BASE_0_B   6
#define DMX_BASE_1_R   7
#define DMX_BASE_1_G   8
#define DMX_BASE_1_B   9
#define DMX_BASE_2_R   10
#define DMX_BASE_2_G   11
#define DMX_BASE_2_B   12
#define DMX_BASE_3_R   13
#define DMX_BASE_3_G   14
#define DMX_BASE_3_B   15

#include <Wire.h>
#include <FastLED.h>
#include "EffectManager.h"



CRGB leds[NUM_LEDS];
uint8_t dmxData[NUM_DMX_CHANNELS];
volatile uint8_t numDmxReceived = 0; //needs to be volatile because it is modified from interrupt
EffectManager effectManager(LEDS_PER_TENTACLE, NUM_TENTACLES, leds);

void setup() 
{
  pinMode(INTERRUPT_PIN, OUTPUT);
  digitalWrite(INTERRUPT_PIN, LOW);
  
  Wire.begin(8);               
  Wire.onReceive(receiveEvent); 

  FastLED.addLeds<LED_TYPE, TENTACLE_PIN_0, LED_COLOR_ORDER>(leds, LEDS_PER_TENTACLE).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, TENTACLE_PIN_1, LED_COLOR_ORDER>(&leds[LEDS_PER_TENTACLE], LEDS_PER_TENTACLE).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, TENTACLE_PIN_2, LED_COLOR_ORDER>(&leds[2 * LEDS_PER_TENTACLE], LEDS_PER_TENTACLE).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, TENTACLE_PIN_3, LED_COLOR_ORDER>(&leds[3 * LEDS_PER_TENTACLE], LEDS_PER_TENTACLE).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  Serial.begin(9600);   //FIXME remove after debug         
}

void debugDmx()
{
  Serial.print("eff: "); Serial.print(dmxData[DMX_EFFECT]);
  Serial.print(" spd: "); Serial.print(dmxData[DMX_SPEED]);
  Serial.print(" str: "); Serial.print(dmxData[DMX_STROBE]);
  Serial.print(" bri: "); Serial.print(dmxData[DMX_BRIGHTNESS]);
  Serial.print(" r0: "); Serial.print(dmxData[DMX_BASE_0_R]);
  Serial.print(" g0: "); Serial.print(dmxData[DMX_BASE_0_G]);
  Serial.print(" b0: "); Serial.print(dmxData[DMX_BASE_0_B]);
  Serial.print(" r1: "); Serial.print(dmxData[DMX_BASE_1_R]);
  Serial.print(" g1: "); Serial.print(dmxData[DMX_BASE_1_G]);
  Serial.print(" b1: "); Serial.print(dmxData[DMX_BASE_1_B]);
  Serial.print(" r2: "); Serial.print(dmxData[DMX_BASE_2_R]);
  Serial.print(" g2: "); Serial.print(dmxData[DMX_BASE_2_G]);
  Serial.print(" b2: "); Serial.print(dmxData[DMX_BASE_2_B]);
  Serial.print(" r3: "); Serial.print(dmxData[DMX_BASE_3_R]);
  Serial.print(" g3: "); Serial.print(dmxData[DMX_BASE_3_G]);
  Serial.print(" b3: "); Serial.print(dmxData[DMX_BASE_3_B]);
  Serial.println("");
}

void loop() 
{
  triggerDmxDataTransfer();
  effectManager.update(dmxData[DMX_EFFECT], dmxData[DMX_SPEED]);
  setBaseColor();
  //TODO implement global strobe effect
  FastLED.setBrightness(dmxData[DMX_BRIGHTNESS]);
  FastLED.show();
}


void setBaseColor()
{
  //FIXME use better loop :)
  
  uint8_t r = dmxData[DMX_BASE_0_R];
  uint8_t g = dmxData[DMX_BASE_0_G];
  uint8_t b = dmxData[DMX_BASE_0_B];
  for(int i = 0; i < LEDS_PER_TENTACLE; ++i)
  {
    leds[i].r = max(leds[i].r, r);
    leds[i].g = max(leds[i].g, g);
    leds[i].b = max(leds[i].b, b);
  }

  r = dmxData[DMX_BASE_1_R];
  g = dmxData[DMX_BASE_1_G];
  b = dmxData[DMX_BASE_1_B];
  for(int i = LEDS_PER_TENTACLE; i < 2 * LEDS_PER_TENTACLE; ++i)
  {
    leds[i].r = max(leds[i].r, r);
    leds[i].g = max(leds[i].g, g);
    leds[i].b = max(leds[i].b, b);
  }  

  r = dmxData[DMX_BASE_2_R];
  g = dmxData[DMX_BASE_2_G];
  b = dmxData[DMX_BASE_2_B];
  for(int i = 2 * LEDS_PER_TENTACLE; i < 3 * LEDS_PER_TENTACLE; ++i)
  {
    leds[i].r = max(leds[i].r, r);
    leds[i].g = max(leds[i].g, g);
    leds[i].b = max(leds[i].b, b);
  }  

  r = dmxData[DMX_BASE_3_R];
  g = dmxData[DMX_BASE_3_G];
  b = dmxData[DMX_BASE_3_B];
  for(int i = 3 * LEDS_PER_TENTACLE; i < 4 * LEDS_PER_TENTACLE; ++i)
  {
    leds[i].r = max(leds[i].r, r);
    leds[i].g = max(leds[i].g, g);
    leds[i].b = max(leds[i].b, b);
  }  
}

/** Asks the dmx handler for new data and blocks until all data is received*/
void triggerDmxDataTransfer()
{
  numDmxReceived = 0;
  //If INTERRUPT_PIN is high the other arduino will know that it should send data
  digitalWrite(INTERRUPT_PIN, HIGH);
  delayMicroseconds(500);
  digitalWrite(INTERRUPT_PIN, LOW);
  
  //spin lock till all data is received
  while(numDmxReceived < NUM_DMX_CHANNELS);
}

/**Receive dmx data via i2c. Is triggered by interrupt */
void receiveEvent(int unused)
{
  while (Wire.available() > 0 && numDmxReceived < NUM_DMX_CHANNELS) 
  { 
    dmxData[numDmxReceived] = Wire.read();
    ++numDmxReceived;       
  }   
}
