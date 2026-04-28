#ifndef _DRYNESS_SENSOR_CONTROLLER_H_
#define _DRYNESS_SENSOR_CONTROLLER_H_

#include <Arduino.h>

#define VALUE_OFFSET 0
#define VALUE_MAX 4095

namespace DrynessSensor
{
float GetSoilDryness(int pin)
{
  int potValue = analogRead(pin);  
  float dryness = (double) (potValue - VALUE_OFFSET) / (double)(VALUE_MAX - VALUE_OFFSET) * 100.0;
  if(dryness < 0) dryness = 0;
  if(dryness > 100) dryness = 100;

  return dryness;
}
}

#endif // _DRYNESS_SENSOR_CONTROLLER_H_
