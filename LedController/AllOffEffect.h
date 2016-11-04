#pragma once


void initAllOff(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles)
{
}


void updateAllOff(CRGB* leds, uint8_t numPixelsPerTentacle, uint8_t numTentacles,
                uint16_t timeSinceLastCall, uint8_t speed, uint8_t color)
{
  FastLED.clear();
}


