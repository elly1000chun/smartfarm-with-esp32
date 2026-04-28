#include <Arduino.h>
#include <WiFi.h>
#include "network/thingspeak.hpp"
#include "network/wifiController.hpp"
#include "network/RTCController.h"
#include "display/OledController.h"
#include "sensors/AHT20Controller.h"
#include "sensors/DrynessSensorController.hpp"

#define SOILPIN 33
#define GPIO_RTC_CLK 14
#define GPIO_RTC_DAT 12
#define GPIO_RTC_RST 13
#define SYNC_DATA_INTERVAL_MINUTE 15

OledController oled;
AHT20Controller aht;
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
  oled.PrintLine("Welcome.");
  delay(1000);
  oled.PrintLine("Wi-Fi Connecting...");
 
  int counter = 0;
  isWifiConnected = network::ConnectWifi();

  if(isWifiConnected == true)
  {
    oled.PrintLine("Wi-Fi Connected.");
  }
  else
  {
    oled.PrintLine("Wi-Fi Error.");   
  }

  isRTCAvailable = Rtc.InitializeRTC();
  if(isRTCAvailable && isWifiConnected)
  {
    Rtc.SyncRTCToNTP();
  }

  isAHTAvailable = aht.Initialize();
  if(isAHTAvailable)
  {
    oled.PrintLine("Temp&Hum sensor initialized.");
  }
  else
  {
    oled.PrintLine("Temp&Hum sensor error.");
  }
}

int count = 0;

void loop()
{
  if(isAHTAvailable == false || isDisplayAvailable == false)
  {
    return;
  }

  String currentTime = Rtc.GetCurrentTimeString();

  int temperature = aht.GetTemperature();
  String tem = "Tem: " + String(temperature) + (char)247 + "C";
  int humidity = aht.GetHumitidy();
  String hum = "Hum: " + String(humidity) + "%";
  int dryness = DrynessSensor::GetSoilDryness(SOILPIN);
  String dry = "Dry: " + String(dryness) + "%";

  oled.ClearDisplay();
  oled.SetTextSize(1);
  oled.PrintLine(currentTime);
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
