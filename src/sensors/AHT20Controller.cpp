#include "AHT20Controller.h"

AHT20Controller::AHT20Controller()
  : aht_humidity(nullptr)
  , aht_temp(nullptr)
{}

AHT20Controller::~AHT20Controller()
{}

bool AHT20Controller::Initialize()
{
  // Initialize device.
  bool bBegin = aht.begin();

  if(bBegin == false)
  {
    Serial.println("Failed to find AHT10/AHT20 chip");
    return false;
  }

  PrintTemperatureSensorInfo();
  PrintHumiditySensorInfo();
  return bBegin;
}

void AHT20Controller::PrintTemperatureSensorInfo()
{
  Serial.println("AHT10/AHT20 Found!");
  aht_temp = aht.getTemperatureSensor();
  if(aht_temp)
  {
    aht_temp->printSensorDetails();
  }
}

void AHT20Controller::PrintHumiditySensorInfo()
{
  aht_humidity = aht.getHumiditySensor();
  if(aht_humidity)
  {
    aht_humidity->printSensorDetails();
  }
}

float AHT20Controller::GetTemperature()
{
  sensors_event_t temp;
  float tm = nan("");
  aht_temp = aht.getTemperatureSensor();
  if(aht_temp)
  {
    aht_temp->getEvent(&temp);
    tm = temp.temperature;
  }

  if (isnan(tm)) {
    Serial.println(F("Error reading temperature!"));
  }

  return tm;
}

float AHT20Controller::GetHumitidy()
{
  sensors_event_t humidity;
  float hm = nan("");
  aht_humidity = aht.getHumiditySensor();
  if(aht_humidity)
  {
    aht_humidity->getEvent(&humidity);
    hm = humidity.relative_humidity;
  }
 
  if (isnan(hm)) {
    Serial.println(F("Error reading humidity!"));
  }

  return hm;
}