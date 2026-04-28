#ifndef _AHT20_CONTROLLER_H_
#define _AHT20_CONTROLLER_H_

#include <Adafruit_AHTX0.h>

class AHT20Controller
{
public:
  AHT20Controller();
  ~AHT20Controller();
  bool Initialize();
  void PrintTemperatureSensorInfo();
  void PrintHumiditySensorInfo();

  float GetTemperature();
  float GetHumitidy();

private:
  Adafruit_AHTX0 aht;
  Adafruit_Sensor *aht_humidity, *aht_temp;
};

#endif
