#ifndef _OLED_CONTROLLER_H
#define _OLED_CONTROLLER_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OledController
{
public:
  OledController();
  ~OledController();
  bool Initialize();

  void SetTextSize(int size);
  void PrintLine(String string, bool bUpdate = false);
  void ClearDisplay(bool bUpdate = false);

private: 
  Adafruit_SSD1306 display;
};

#endif