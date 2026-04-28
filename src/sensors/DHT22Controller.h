#ifndef _DHT22_CONTROLLER_H_
#define _DHT22_CONTROLLER_H_

#include <DHT_U.h>

class DHT22Controller
{
public:
  DHT22Controller(int pin);
  ~DHT22Controller();
  bool Initialize();
  void PrintTemperatureSensorInfo();
  void PrintHumiditySensorInfo();

  float GetTemperature();
  float GetHumitidy();

private:
  DHT_Unified dht;
};

#endif //_DHT22_CONTROLLER_H_
