#pragma once
#include <pixeltypes.h>
#include "RandomLaserEffect.h"
#include "MeteorEffect.h"
#include "SingleTentacleEffect.h"
#include "SweepEffect.h"

class EffectManager
{
private:
  enum Effect
  {
    TENTACLE_0_ON_EFFECT,
    TENTACLE_1_ON_EFFECT,
    TENTACLE_2_ON_EFFECT,
    TENTACLE_3_ON_EFFECT,
    SWEEP_EFFECT,
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
      //Serial.print("Effect: ");
     //Serial.println(currentEffect);
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
    initMethods[TENTACLE_0_ON_EFFECT] = initSte0;
    updateMethods[TENTACLE_0_ON_EFFECT] = updateSte;
    initMethods[TENTACLE_1_ON_EFFECT] = initSte1;
    updateMethods[TENTACLE_1_ON_EFFECT] = updateSte;
    initMethods[TENTACLE_2_ON_EFFECT] = initSte2;
    updateMethods[TENTACLE_2_ON_EFFECT] = updateSte;
    initMethods[TENTACLE_3_ON_EFFECT] = initSte3;
    updateMethods[TENTACLE_3_ON_EFFECT] = updateSte;

    initMethods[SWEEP_EFFECT] = initSweepEffect;
    updateMethods[SWEEP_EFFECT] = updateSweepEffect;
    

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

