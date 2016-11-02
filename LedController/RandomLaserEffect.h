#pragma once
#include "Wait.h"

struct 
{
  uint8_t start;  
  uint8_t h;
  uint32_t timePassed; //in us
} rle;


void initRle(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  const uint16_t numLeds = numPixelsPerTentacle * numTentacles;
  rle.start = rle.start % numLeds; //clamp to range but do not change if already in range
}

void updateRle(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
               uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  WAIT(map(speed, 255, 0, 0, 300000), rle.timePassed, timeSinceLastCall);
  FastLED.clear();
  
  //FIXME not yet working
  FastLED.clear();
  const uint16_t numLeds = numPixelsPerTentacle * numTentacles;
  const uint8_t width = 6;
  const uint8_t end = min(rle.start + width, numLeds - 1);
  rle.start = (rle.start + 1) % numLeds;
  for(int i = rle.start; i < end; ++i)
  { 
    leds[i].setHue(rle.h);
  }
}

