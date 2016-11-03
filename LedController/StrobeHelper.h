#pragma once

/**A class to manage strobe timing */
class StrobeHelper
{
private:
  bool off;//is strobe off?
  unsigned long offTime; //time at which the strobe has been turned off
  unsigned long onTime; //time at wich the strobe has been turned on
  uint16_t strobeOffTime; //how long should the strobe be off inbetween flashes in ms
  uint8_t strobeOnTime; //how long should a flash be in ms
public:
  StrobeHelper() : off(true), offTime(0), onTime(0), strobeOffTime(100), strobeOnTime(4)
  {}

  void update()
  {
    const unsigned long currentTime = millis();
    if (off && currentTime - offTime >= strobeOffTime)
    {
      off = false;
      onTime = currentTime;
    }
    else if (!off && currentTime - onTime >= strobeOnTime)
    {
      off = true;
      offTime = currentTime;
    }
  }

  void setOffTime(const uint16_t t)
  {
    strobeOffTime = t;
  }

  void setOnTime(const uint8_t t)
  {
    strobeOnTime = t;
  }

  bool isOff() const
  {
    return off;
  }
  
};

