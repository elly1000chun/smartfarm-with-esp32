#ifndef _THINGSPEAK_CONTOLLER_H_
#define _THINGSPEAK_CONTOLLER_H_
#include <Arduino.h>
#include <esp_http_client.h>

namespace network
{
void SendDataThingspeak(int temperature, int humidity, int dryness)
{
	char url[256];
	sprintf (url, "http://api.thingspeak.com/update?api_key=%s&field1=%d&field2=%d&field3=%d",
				THINGSPEAK_KEY, temperature, humidity, dryness);
				
	esp_http_client_config_t config = {
		.url = url,
		.method = HTTP_METHOD_GET,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    
     // GET
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        Serial.println("Sensor data was sent successfully. code: " + String(esp_http_client_get_status_code(client)));
    } else {
        Serial.println("Failed to send data. code: " + String(err));
    }
    
    esp_http_client_cleanup(client);
}

} // namespace network

#endif //_THINGSPEAK_CONTOLLER_H_