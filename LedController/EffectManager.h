#pragma once
#include <pixeltypes.h>
#include "RandomLaserEffect.h"
#include "MeteorEffect.h"

class EffectManager
{
private:
  enum Effect
  {
    METEOR_EFFECT,
    RANDOM_LASER,
    //add effect ids before NUM_EFFECTS
    NUM_EFFECTS
  };

  // parameters: leds, numPixelsPerTentacle, numTentacles, timeSinceLastCall (in micros), speed, 
  typedef void (*UpdatePtr)(CRGB*, uint8_t, uint8_t, uint16_t, uint8_t, uint8_t);
  //parameters: leds, numPixelsPerTentacle, numTentacles
  typedef void (*InitPtr)(CRGB*, uint8_t, uint8_t);
  
  UpdatePtr updateMethods[NUM_EFFECTS];
  InitPtr initMethods[NUM_EFFECTS];

  const uint8_t numPixelsPerTentacle;
  const uint8_t numTentacles;
  Effect currentEffect;
  Effect lastEffect;
  CRGB* leds;
  
  
public:

  EffectManager(int numPixelsPerTentacle, int numTentacles,
                CRGB* leds) : numPixelsPerTentacle(numPixelsPerTentacle),
    numTentacles(numTentacles), currentEffect((Effect)0), lastEffect((Effect)0),
    leds(leds)
  {
    loadEffects();
  }

  void update(const uint8_t effectId, const uint8_t speed, const uint8_t effectColor)
  {
    currentEffect = (Effect)map(effectId, 0, 255, 0, NUM_EFFECTS - 1);

    if(currentEffect != lastEffect)
    {
      lastEffect = currentEffect;
      initMethods[currentEffect](leds, numPixelsPerTentacle, numTentacles);
    }
    updateMethods[currentEffect](leds, numPixelsPerTentacle, numTentacles,
                                 getTimeSinceLastCall(), speed, effectColor);
  }

  private:

  /** Initializes the effect pointers */
  void loadEffects()
  {
    initMethods[RANDOM_LASER] = initRle;
    updateMethods[RANDOM_LASER] = updateRle;

    initMethods[METEOR_EFFECT] = initMeteor;
    updateMethods[METEOR_EFFECT] = updateMeteor;   
  }

  /** Returns the time since the last call to this method in micro seconds */
  uint16_t getTimeSinceLastCall()
  {
  static unsigned long lastTime = 0;
  const unsigned long currentTime = micros();
  const uint16_t diff = currentTime - lastTime;
  lastTime = currentTime;
  return diff;
  }
};

