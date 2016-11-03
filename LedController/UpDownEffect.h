#pragma once
#include "Wait.h"

struct 
{
  int8_t start;
  uint32_t timePassed; //in us
  uint8_t width;
  int8_t dir;
} ude;


void initUde(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  ude.width = 7;
  const uint16_t numLeds = numPixelsPerTentacle - ude.width;
  ude.timePassed = 999999999;
  ude.start = ude.start % numLeds;
  ude.dir = 2;
}

void updateUde(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
               uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  WAIT(map(speed, 255, 0, 0, 300000), rle.timePassed, timeSinceLastCall);
  FastLED.clear();

  const int16_t numLeds = numPixelsPerTentacle - ude.width;
  ude.start += ude.dir;

  if(ude.start >= numLeds)
  {
    ude.start = numLeds - 1;
    ude.dir = -2;
  }
  else if(ude.start < 0)
  {
    ude.start = 1;
    ude.dir = 2;
  }


  const uint8_t end = ude.start + ude.width;
  
  for(int i = ude.start; i < end; ++i)
  { 
    leds[i].setHue(color);
    leds[i + numPixelsPerTentacle].setHue(color);
    leds[i + numPixelsPerTentacle + numPixelsPerTentacle].setHue(color);
    leds[i + numPixelsPerTentacle + numPixelsPerTentacle + numPixelsPerTentacle].setHue(color);
  }
}

