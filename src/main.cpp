#include <Arduino.h>
#include <WiFi.h>
#include "network/thingspeak.hpp"
#include "network/wifiController.hpp"
#include "network/RTCController.h"
#include "display/OledController.h"
#include "sensors/DrynessSensorController.hpp"
#include "sensors/DHT22Controller.h"

#define SOILPIN 34
#define GPIO_RTC_CLK 14
#define GPIO_RTC_DAT 12
#define GPIO_RTC_RST 13
#define SYNC_DATA_INTERVAL_MINUTE 15

OledController oled;
DHT22Controller dht(33);
RTCController Rtc(GPIO_RTC_DAT, GPIO_RTC_CLK, GPIO_RTC_RST);

bool isDisplayAvailable = false;
bool isWifiConnected = false;
bool isAHTAvailable = false;
bool isRTCAvailable = false;
bool isFirstTimeSendingData = true;
int prevDataSyncMinute = 0;

void setup() {
  Serial.begin(115200);

  // Init display
  isDisplayAvailable = oled.Initialize();

  oled.SetTextSize(1);
  oled.PrintLine("Welcome.", true);
  delay(1000);
  oled.PrintLine("Wi-Fi Connecting...", true);
 
  int counter = 0;
  isWifiConnected = network::ConnectWifi();

  if(isWifiConnected == true)
  {
    oled.PrintLine("Wi-Fi Connected.", true);
  }
  else
  {
    oled.PrintLine("Wi-Fi Error.", true);
  }

  isRTCAvailable = Rtc.InitializeRTC();
  if(isRTCAvailable && isWifiConnected)
  {
    Rtc.SyncRTCToNTP();
  }

  isAHTAvailable = dht.Initialize();
  if(isAHTAvailable)
  {
    oled.PrintLine("HT Sensor type is AHT20.", true);
    oled.PrintLine("Temp&Hum sensor initialized.", true);
  }
  else
  {
    oled.PrintLine("Temp&Hum sensor error.", true);
  }
}

int count = 0;

void loop()
{
  if(isAHTAvailable == false || isDisplayAvailable == false)
  {
    return;
  }

  int temperature = dht.GetTemperature();
  String tem = "Tem: " + String(temperature) + (char)247 + "C";
  int humidity = dht.GetHumitidy();
  String hum = "Hum: " + String(humidity) + "%";
  int dryness = DrynessSensor::GetSoilDryness(SOILPIN);
  String dry = "Dry: " + String(dryness) + "%";

  oled.ClearDisplay();
  oled.SetTextSize(1);
  if(isRTCAvailable)
  {
    String currentTime = Rtc.GetCurrentTimeString();
    oled.PrintLine(currentTime);
  }
  else
  {
  }
  oled.PrintLine("");

  oled.SetTextSize(2);
  oled.PrintLine(tem);
  oled.PrintLine(hum);
  oled.PrintLine(dry, true);
  
  int minute = Rtc.GetCurrentMinute();

  if(isFirstTimeSendingData || ((minute % SYNC_DATA_INTERVAL_MINUTE == 0) && minute != prevDataSyncMinute))
  {
    Serial.println(Rtc.GetCurrentTimeString());
    if(isWifiConnected)  
    {
      network::SendDataThingspeak(temperature, humidity, dryness);
    }
    isFirstTimeSendingData = false;
    prevDataSyncMinute = minute;
  }

  delay(1000);
  count++;
}