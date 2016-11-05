#pragma once
#include "Wait.h"

struct 
{
  uint32_t timePassed;
} massacre;

void initColorMassacre(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  massacre.timePassed = 999999999;
}

void updateColorMassacre(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
               uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  WAIT(map(speed, 255, 0, 0, 600000), massacre.timePassed, timeSinceLastCall);
  
  FastLED.clear();

  for (int i = 0; i < numPixelsPerTentacle * numTentacles; ++i)
  {
    leds[i].setHue(random(0, 255));
  }
}
