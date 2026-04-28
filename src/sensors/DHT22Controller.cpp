#include <Adafruit_Sensor.h>
#include <DHT.h>

#include "DHT22Controller.h"

DHT22Controller::DHT22Controller(int pin)
  : dht(pin, DHT22)
{}

DHT22Controller::~DHT22Controller()
{}

bool DHT22Controller::Initialize()
{
  // Initialize device.
  dht.begin();

  PrintTemperatureSensorInfo();
  PrintHumiditySensorInfo();
  return true;
}

void DHT22Controller::PrintTemperatureSensorInfo()
{
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
}

void DHT22Controller::PrintHumiditySensorInfo()
{
  sensor_t sensor;
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
}

float DHT22Controller::GetTemperature()
{
  sensors_event_t event;
  float tm = nan("");

  dht.temperature().getEvent(&event);
  tm = event.temperature;
  if (isnan(tm)) {
    Serial.println(F("Error reading temperature!"));
  }

  return tm;
}

float DHT22Controller::GetHumitidy()
{
  sensors_event_t event;
  float hm = nan("");
  dht.humidity().getEvent(&event);
  hm = event.relative_humidity;

  if (isnan(hm)) {
    Serial.println(F("Error reading humidity!"));
  }

  return hm;
}