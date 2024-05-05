#pragma once

#include "CasaLib/preferences.h"

#define NVS_ENABLE_DISPLAY "enable_display"
#define NVS_ENABLE_DISPLAY_DEFAULT 0
#define NVS_DISPLAY_REFRESH_PERIOD "display_refresh_period"
#define NVS_DISPLAY_REFRESH_PERIOD_DEFAULT 3
#define NVS_ENABLE_PRESENCE_DETECTION "enable_presence_detection"
#define NVS_ENABLE_PRESENCE_DETECTION_DEFAULT 0
#define NVS_JOURNAL_LENGTH "journal_length"
#define NVS_JOURNAL_LENGTH_DEFAULT 10

typedef struct preferences_s {
    int8_t enable_display;
    uint16_t display_refresh_period;
    int8_t enable_presence_detection;
    uint16_t journal_length;

    const char* wifi_ssid;
    const char* wifi_password;

    preferences_s() : enable_display(NVS_ENABLE_DISPLAY_DEFAULT),
        display_refresh_period(NVS_DISPLAY_REFRESH_PERIOD_DEFAULT),
        enable_presence_detection(NVS_ENABLE_PRESENCE_DETECTION_DEFAULT),
        journal_length(NVS_JOURNAL_LENGTH_DEFAULT) {}
} preferences_t;

void saveSettings(preferences_t* prefs);
void setupPreferences();
preferences_t* getPreferences();