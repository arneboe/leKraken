#pragma once


void initAllOn(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
}


void updateAllOn(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
                uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  FastLED.clear();

  const uint16_t end = numTentacles * numPixelsPerTentacle;
  for(int i = 0; i < end; ++i)
  { 
    leds[i].setHue(color);
  }
}


