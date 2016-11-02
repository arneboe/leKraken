#pragma once
#include "Wait.h"

struct 
{
  uint8_t position;
  uint32_t timePassed;
} meteor;

void initMeteor(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
  meteor.position = 0;
}

void updateMeteor(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
               uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  WAIT(map(speed, 0, 255, 0, 600000), meteor.timePassed, timeSinceLastCall);

  FastLED.clear();

  // TODO: Consider timeSinceLastCall and speed

  const uint8_t newPosition = max(meteor.position * 1.5, 1);
  const uint8_t tailLength = newPosition / 3;
  
  meteor.position = (newPosition <= numPixelsPerTentacle) ? newPosition : 1;

  for (int i = newPosition - tailLength; i < newPosition; ++i)
  {
    for (int offset = 0; offset < numTentacles; ++offset) {
      leds[i + offset * numPixelsPerTentacle].setHSV (color, 255, (i * 255) / newPosition);
    }
  }
}
