#pragma once
#include <pixeltypes.h>
#include "RandomLaserEffect.h"
#include "MeteorEffect.h"
#include "SingleTentacleEffect.h"
#include "SweepEffect.h"
#include "RandomBlobs.h"
#include "RandomBlobsFlash.h"
#include "AllOffEffect.h"
#include "UpDownEffect.h"
#include "RandomForwardEffect.h"
#include "RandomFadeIn.h"
#include "RainbowRampageEffect.h"
#include "ColorMassacre.h"

class EffectManager
{
private:
  enum Effect
  {
    ALL_OFF_EFFECT, //0
    TENTACLE_0_ON_EFFECT,//1
    TENTACLE_1_ON_EFFECT,//2
    TENTACLE_2_ON_EFFECT,//3
    TENTACLE_3_ON_EFFECT,//4
    SWEEP_EFFECT,//5
    RANDOM_BLOB_EFFECT,//6
    RANDOM_BLOB_FLASH_EFFECT,//7
    UP_DOWN_EFFECT,//8
    METEOR_EFFECT,//9
    RANDOM_LASER,//10
    RANDOM_FORWARD_EFFECT,//11
    RANDOM_STARS,//12
    RAINBOW_RAMPAGE_EFFECT,//13
    COLOR_MASSACRE_EFFECT,//14
    
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
      Serial.print("Effect: ");
      Serial.println(currentEffect);
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
    initMethods[ALL_OFF_EFFECT] = initAllOff;
    updateMethods[ALL_OFF_EFFECT] = updateAllOff;
        
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

    initMethods[RANDOM_BLOB_EFFECT] = initRandomBlobEffect;
    updateMethods[RANDOM_BLOB_EFFECT] = updateRandomBlobEffect;

    initMethods[RANDOM_BLOB_FLASH_EFFECT] = initRandomBlobFlashEffect;
    updateMethods[RANDOM_BLOB_FLASH_EFFECT] = updateRandomBlobFlashEffect;

    initMethods[UP_DOWN_EFFECT] = initUde;
    updateMethods[UP_DOWN_EFFECT] = updateUde;

    initMethods[RANDOM_LASER] = initRle;
    updateMethods[RANDOM_LASER] = updateRle;

    initMethods[METEOR_EFFECT] = initMeteor;
    updateMethods[METEOR_EFFECT] = updateMeteor; 

    initMethods[RANDOM_FORWARD_EFFECT] = initRfe;
    updateMethods[RANDOM_FORWARD_EFFECT] = updateRfe;

    initMethods[RANDOM_STARS] = initRfie;
    updateMethods[RANDOM_STARS] = updateRfie;

    initMethods[RAINBOW_RAMPAGE_EFFECT] = initRainbowRampage;
    updateMethods[RAINBOW_RAMPAGE_EFFECT] = updateRainbowRampage;

    initMethods[COLOR_MASSACRE_EFFECT] = initColorMassacre;
    updateMethods[COLOR_MASSACRE_EFFECT] = updateColorMassacre;
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

