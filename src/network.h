#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>

#include "pinout.h"
#include "preferences.h"
#include "camera.h"
#include "esp_camera.h"

#define API_PORT 80

#define WIFI_CONNECTION_TIMEOUT 60  // seconds
#define WIFI_STA_CONNECT_RETRIES 30

void wifiKeepAlive();
void setupRouting();
bool setupWifi();
AsyncWebServer* getServer();