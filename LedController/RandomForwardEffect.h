#pragma once
#include "Wait.h"

struct 
{
  uint8_t starts[30];
  uint32_t timePassed; //in us
} rfe;


void initRfe(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  const uint16_t numLeds = numPixelsPerTentacle * numTentacles;
  rfe.timePassed = 999999999;
  for(int i = 0; i < 30; ++i)
  {
    rfe.starts[i] = random(0, numLeds);
  }
}

void updateRfe(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
               uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  WAIT(map(speed, 255, 0, 0, 300000), rfe.timePassed, timeSinceLastCall);
  FastLED.clear();
  const uint16_t numLeds = numPixelsPerTentacle * numTentacles;
  for(int i = 0; i < 30; ++i)
  {
    rfe.starts[i] = (rfe.starts[i] + 1) % numLeds;
    leds[rfe.starts[i]].setHue(color);
  }
}

