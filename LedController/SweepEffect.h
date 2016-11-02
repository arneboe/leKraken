#pragma once
#include "Wait.h"

struct 
{
  int8_t tentacleId;
  int8_t dir;
  uint32_t timePassed; //in us
} se;

void initSweepEffect(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  se.tentacleId = se.tentacleId % numTentacles;
  se.dir = -1;
  se.timePassed = 999999999;
}

void updateSweepEffect(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
                       uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  WAIT(map(speed, 255, 0, 0, 600000), se.timePassed, timeSinceLastCall);
  FastLED.clear();

  se.tentacleId += se.dir;
  
  if(se.tentacleId >= numTentacles)
  {
    se.tentacleId  = numTentacles - 2;
    se.dir *= -1;
  }
  else if(se.tentacleId < 0)
  {
    se.tentacleId = 1;
    se.dir *= -1;
  }
  
  const uint16_t start = se.tentacleId * numPixelsPerTentacle;
  const uint16_t end = (se.tentacleId + 1) * numPixelsPerTentacle;
  for(int i = start; i < end; ++i)
  { 
    leds[i].setHue(color);
  }
}


