#pragma once
#include "Wait.h"

#define NUM_STARS 30

struct 
{
  uint8_t i[30];
  int16_t brightness[30];
  uint32_t timePassed; //in us
} rfie;


void initRfie(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  const uint16_t numLeds = numPixelsPerTentacle * numTentacles;
  for(int i = 0; i < NUM_STARS; ++i)
  {
    rfie.brightness[i] = 0;
  }
}

void updateRfie(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
               uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  WAIT(map(speed, 255, 0, 0, 300000), rfie.timePassed, timeSinceLastCall);
  
  FastLED.clear();
  const uint16_t numLeds = numPixelsPerTentacle * numTentacles - 1;
  
  for(int i = 0; i < NUM_STARS; ++i)
  {
    if(rfie.brightness[i] > 0)
    {
      --rfie.brightness[i];
    }
    else if(random(0, 3) == 2)
    {
      rfie.i[i] = random(0, numLeds);
      rfie.brightness[i] = 255;
    }

    leds[rfie.i[i]].setHSV(color, 255, rfie.brightness[i]);
  }
}

