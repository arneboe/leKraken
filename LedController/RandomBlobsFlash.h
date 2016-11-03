#pragma once
#include "Wait.h"
#include "StrobeHelper.h"

struct 
{
  StrobeHelper strobe;
  uint8_t i;
  uint8_t width;
} rdbf;

void initRandomBlobFlashEffect(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  rdbf.strobe.setOnTime(6);
  rdbf.i = rdbf.i % (numPixelsPerTentacle * numTentacles);
  rdbf.width = 10;
}

void updateRandomBlobFlashEffect(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
                            uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  rdbf.strobe.setOffTime(map(speed, 255, 0, 6, 600000));
  rdbf.strobe.update();
  if(rdbf.strobe.isOff())
  {
    FastLED.clear();
  }
  else
  {
   rdbf.i = random(0, numPixelsPerTentacle * numTentacles - rdbf.width);
    
    const uint16_t start = rdbf.i;
    const uint16_t end = rdbf.i + rdbf.width;
    for(int i = start; i < end; ++i)
    { 
      leds[i].setHue(color);
    }
  }
}


