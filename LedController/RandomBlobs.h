#pragma once
#include "Wait.h"

struct 
{
  uint32_t timePassed; //in us
  uint8_t i;
  uint8_t width;
} rdb;

void initRandomBlobEffect(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  rdb.timePassed = 999999999;
  rdb.i = rdb.i % (numPixelsPerTentacle * numTentacles);
  rdb.width = 10;
}

void updateRandomBlobEffect(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
                            uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  WAIT(map(speed, 255, 0, 0, 600000), rdb.timePassed, timeSinceLastCall);
  FastLED.clear();

  rdb.i = random(0, numPixelsPerTentacle * numTentacles - rdb.width);
  
  const uint16_t start = rdb.i;
  const uint16_t end = rdb.i + rdb.width;
  for(int i = start; i < end; ++i)
  { 
    leds[i].setHue(color);
  }
}


