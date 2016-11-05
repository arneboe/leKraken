#pragma once
#include "Wait.h"

struct 
{
  uint8_t offset;
  uint32_t timePassed;
} rainbow;

void initRainbowRampage(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  rainbow.offset = 0;
  meteor.timePassed = 999999999;
}

void updateRainbowRampage(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
               uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  WAIT(map(speed, 255, 0, 0, 600000), rainbow.timePassed, timeSinceLastCall);
  
  FastLED.clear();

  for (int i = 0; i < numPixelsPerTentacle * numTentacles; ++i)
  {
    leds[i].setHue(i + rainbow.offset);
  }

  ++rainbow.offset;
}

