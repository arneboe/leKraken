#pragma once

#define WAIT(waitTime, accumulator, timePassed) \
  accumulator += timePassed; \
  if(accumulator > waitTime) \
  { \
    accumulator = 0; \
  } \
  else \
  { \
    return; \
  }

