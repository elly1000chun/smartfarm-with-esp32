#include <Arduino.h>
#include "RTCController.h"

const char *ntpServer = "pool.ntp.org";
uint8_t timeZone = 9;
uint8_t summerTime = 0; // 3600

RTCController::RTCController(uint8_t ioPin, uint8_t clkPin, uint8_t cePin)
    : mywire(ioPin, clkPin, cePin), Rtc(mywire)
    , RTCAvailable(false)
{
}

RTCController::~RTCController()
{
  // do nothing
}

bool RTCController::InitializeRTC()
{
  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  String timestamp = GetDateTimeString(compiled);
  Serial.println(timestamp);

  if (!Rtc.IsDateTimeValid())
  {
    Serial.println("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
    Serial.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled)
  {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }

  if (!Rtc.GetIsRunning() || !Rtc.IsDateTimeValid())
  {
    return false;
  }

  RTCAvailable = true;
  return true;
}

bool RTCController::SyncRTCToNTP()
{
  if(RTCAvailable == false) return false;

  configTime(3600 * timeZone, 3600 * summerTime, ntpServer); // init and get the time
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return false;
  }

  time_t now;
  time(&now);
  uint64_t serverUnix = now + 3600 * timeZone;
  uint64_t rtcUnix = Rtc.GetDateTime().Unix64Time();

  RtcDateTime rtctime = Rtc.GetDateTime();
  Serial.print("NTP Unix: ");
  Serial.println(serverUnix);

  Serial.print("RTC Unix: ");
  Serial.println(rtcUnix);

  int diffTime = serverUnix - rtcUnix;
  if (abs(diffTime) > 60)
  {
    Serial.println(String("RTC time synced."));
    Serial.println(String("Diff time: ") + String(diffTime));
    Serial.println(String("RTC time: ") + GetDateTimeString(rtctime));

    RtcDateTime serverRtc = RtcDateTime(
      timeinfo.tm_year+1900,
      timeinfo.tm_mon+1,
      timeinfo.tm_mday,
      timeinfo.tm_hour,
      timeinfo.tm_min,
      timeinfo.tm_sec
    );
    Rtc.SetDateTime(serverRtc);
    Serial.println(String("Synced RTC time: ") + GetDateTimeString(serverRtc));
  }
  else
  {
    Serial.println(String("RTC time is correct."));
  }

  return true;
}

bool RTCController::isRTCAvailable()
{
  return RTCAvailable;
}

String RTCController::GetCurrentTimeString()
{
  String timeString = "";
  if (RTCAvailable)
  {
    if (!Rtc.IsDateTimeValid())
    {
      Serial.println("RTC lost confidence in the DateTime!");
    }
    else
    {
      timeString = GetDateTimeString(Rtc.GetDateTime());
    }
  }
  else
  {
    timeString = GetDateTimeString(GetCurrentNTPTime());
  }

  return timeString;
}

RtcDateTime RTCController::GetCurrentNTPTime()
{
  configTime(3600 * timeZone, 3600 * summerTime, ntpServer);
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return RtcDateTime();
  }

  RtcDateTime ntpTime = RtcDateTime(timeinfo.tm_year + 1900,
             timeinfo.tm_mon + 1,
             timeinfo.tm_mday,
             timeinfo.tm_hour,
             timeinfo.tm_min,
             timeinfo.tm_sec);

  return ntpTime;
}

String RTCController::GetDateTimeString(const RtcDateTime &dt)
{
  char datestring[20];
  snprintf_P(datestring,
             countof(datestring),
             PSTR("%04u/%02u/%02u %02u:%02u:%02u"),
             dt.Year(),
             dt.Month(),
             dt.Day(),
             dt.Hour(),
             dt.Minute(),
             dt.Second());

  return String(datestring);
}

int RTCController::GetCurrentMinute()
{
  int min = -1;
  if (RTCAvailable)
  {
    RtcDateTime rtctime = Rtc.GetDateTime();
    min = rtctime.Minute();
  }
  else
  {
    configTime(3600 * timeZone, 3600 * summerTime, ntpServer);
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
      Serial.println("Failed to obtain time");
      return -1;
    }
    min = timeinfo.tm_min;
  }

  return min;
}