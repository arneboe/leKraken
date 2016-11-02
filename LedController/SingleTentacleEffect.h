#pragma once
#include "Wait.h"

struct 
{
  uint8_t tentacleId;
} ste;

void initSte0(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  ste.tentacleId = 0;
}
void initSte1(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  ste.tentacleId = 1;
}
void initSte2(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  ste.tentacleId = 2;
}
void initSte3(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  ste.tentacleId = 3;
}

void updateSte(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
               uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  FastLED.clear();
  
  const uint16_t numLeds = numPixelsPerTentacle * numTentacles;
  const uint16_t start = ste.tentacleId * numPixelsPerTentacle;
  const uint16_t end = (ste.tentacleId + 1) * numPixelsPerTentacle;
  for(int i = start; i < end; ++i)
  { 
    leds[i].setHue(color);
  }
}


