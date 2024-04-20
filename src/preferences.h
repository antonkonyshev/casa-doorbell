#pragma once

#include <string>
#include <nvs_flash.h>

#define NVS_PREFERENCES_STORAGE_NAME "storage"
#define NVS_WIFI_SSID_CREDENTIALS_KEY "wifi_ssid"
#define NVS_WIFI_PASSWORD_CREDENTIALS_KEY "wifi_password"
#define NVS_ENABLE_DISPLAY "enable_display"
#define NVS_ENABLE_DISPLAY_DEFAULT 0
#define NVS_DISPLAY_REFRESH_PERIOD "display_refresh_period"
#define NVS_DISPLAY_REFRESH_PERIOD_DEFAULT 3

typedef struct wifi_credentials_s {
    std::string ssid;
    std::string password;
    wifi_credentials_s* next;

    wifi_credentials_s() : next(nullptr) {}
} wifi_credentials_t;

typedef struct preferences_s {
    int8_t enable_display;
    uint16_t display_refresh_period;
    std::string wifi_ssid;
    std::string wifi_password;

    preferences_s() : enable_display(0), display_refresh_period(3) {}
} preferences_t;

wifi_credentials_t* loadWiFiCredentials();
void saveWiFiCredentials(const char* ssid, const char* password);
void cleanWiFiCredentials();
void saveSettings(preferences_t* prefs);
void setupPreferences();
preferences_t* getPreferences();