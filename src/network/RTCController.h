#ifndef _RTC_CONTOLLER_H_
#define _RTC_CONTOLLER_H_

#include <ThreeWire.h>
#include <RtcDS1302.h>

class RTCController
{
public:
  RTCController(uint8_t ioPin, uint8_t clkPin, uint8_t cePin);
  ~RTCController();

  bool InitializeRTC();
  bool SyncRTCToNTP();
  String GetCurrentTimeString();
  int GetCurrentMinute();

private:
  String GetDateTimeString(const RtcDateTime& dt);

  ThreeWire mywire;
  RtcDS1302<ThreeWire> Rtc;
};

#endif