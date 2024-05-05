#include "preferences.h"

preferences_t* preferences;

void setupPreferences() {
    preferences = new preferences_t;
    #ifdef ESP32_DEVICE

    openPreferencesStorage();
    loadPreference(NVS_ENABLE_DISPLAY, &preferences->enable_display, NVS_ENABLE_DISPLAY_DEFAULT);
    loadPreference(NVS_DISPLAY_REFRESH_PERIOD, &preferences->display_refresh_period, (uint16_t) NVS_DISPLAY_REFRESH_PERIOD_DEFAULT);
    loadPreference(NVS_ENABLE_PRESENCE_DETECTION, &preferences->enable_presence_detection, (uint16_t) NVS_ENABLE_PRESENCE_DETECTION_DEFAULT);
    loadPreference(NVS_JOURNAL_LENGTH, &preferences->journal_length, NVS_JOURNAL_LENGTH_DEFAULT);
    closePreferencesStorage();

    #endif
    #ifdef ESP8266_DEVICE

    loadPreference(preferences);

    #endif
}

void saveSettings(preferences_t* prefs) {
    #ifdef ESP32_DEVICE

    openPreferencesStorage();
    if (prefs->wifi_ssid) {
        savePreference(NVS_WIFI_SSID_CREDENTIALS_KEY, prefs->wifi_ssid);
        savePreference(NVS_WIFI_PASSWORD_CREDENTIALS_KEY, prefs->wifi_password);
    }
    savePreference(NVS_ENABLE_DISPLAY, prefs->enable_display);
    savePreference(NVS_DISPLAY_REFRESH_PERIOD, prefs->display_refresh_period);
    savePreference(NVS_ENABLE_PRESENCE_DETECTION, prefs->enable_presence_detection);
    savePreference(NVS_JOURNAL_LENGTH, prefs->journal_length);
    closePreferencesStorage();

    #endif
    #ifdef ESP8266_DEVICE

    savePreference(prefs);

    #endif
}

preferences_t* getPreferences() {
    return preferences;
}