#pragma once
#include "Wait.h"

struct 
{
  uint8_t start;  
  uint32_t timePassed; //in us
  uint8_t width;
} rle;


void initRle(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  const uint16_t numLeds = numPixelsPerTentacle * numTentacles;
  rle.start = rle.start % numLeds; //clamp to range but do not change if already in range
  rle.timePassed = 999999999;
  rle.width = 6;
}

void updateRle(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
               uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  WAIT(map(speed, 255, 0, 0, 300000), rle.timePassed, timeSinceLastCall);
  FastLED.clear();

  const uint8_t numLeds = numPixelsPerTentacle * numTentacles - rle.width;
  rle.start = (rle.start + 1) % numLeds;
  const uint8_t end = rle.start + rle.width;
  
  for(int i = rle.start; i < end; ++i)
  { 
    leds[i].setHue(color);
  }
}

