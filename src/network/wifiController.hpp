#ifndef _WIFI_CONTROLLER_H_
#define _WIFI_CONTROLLER_H_

#include <WiFi.h>

#define MAX_TRIAL 20
#define TRIAL_INTERAL 500 // msec

namespace network 
{
int counter = 0;

bool ConnectWifi()
{
  // start connection
  Serial.println(String("Connect try : ") + WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  bool isConnected = true;
  // waiting connection...
  while(WiFi.status() != WL_CONNECTED )
  {
    if(counter > MAX_TRIAL) 
    {
      isConnected = false;
      break;
    }

    delay(TRIAL_INTERAL);
    Serial.println(".");
    counter++;
  }

  // handle result
  if(isConnected == true)
  {
    Serial.print(String("WiFi conneted\n IP : "));
    Serial.println(WiFi.localIP());  
  }
  else
  {
    Serial.print(String("Failed to connect WiFi."));
  }

  return isConnected;
}

} // namespace network

#endif // _WIFI_CONTROLLER_H_