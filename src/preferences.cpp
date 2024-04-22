#include "preferences.h"

wifi_credentials_t* credentials;
preferences_t* preferences;

void appendToCredentials(const char* ssid, const char* password) {
    wifi_credentials_t* additional = new wifi_credentials_t;
    additional->ssid = ssid;
    additional->password = password;
    if (credentials) {
        wifi_credentials_t* current = credentials;
        while(current->next) {
            current = current->next;
        }
        current->next = additional;
    } else {
        credentials = additional;
    }
}

wifi_credentials_t* loadWiFiCredentials() {
    if (credentials) {
        return credentials;
    }
    nvs_handle_t storage;
    size_t value_size;
    nvs_open(NVS_PREFERENCES_STORAGE_NAME, NVS_READWRITE, &storage);
    nvs_get_str(storage, NVS_WIFI_SSID_CREDENTIALS_KEY, NULL, &value_size);
    if (value_size && value_size < 512) {
        credentials = new wifi_credentials_t;
        char buffer[value_size] = {0};
        nvs_get_str(storage, NVS_WIFI_SSID_CREDENTIALS_KEY, buffer, &value_size);
        credentials->ssid = buffer;
        nvs_get_str(storage, NVS_WIFI_PASSWORD_CREDENTIALS_KEY, NULL, &value_size);
        if (value_size && value_size < 512) {
            char buffer[value_size] = {0};
            nvs_get_str(storage, NVS_WIFI_PASSWORD_CREDENTIALS_KEY, buffer, &value_size);
            credentials->password = buffer;
        }
    }
    nvs_close(storage);

    #ifdef DEFAULT_WIFI_SSID_1
    appendToCredentials(DEFAULT_WIFI_SSID_1, DEFAULT_WIFI_PASSWORD_1);
    #endif
    #ifdef DEFAULT_WIFI_SSID_2
    appendToCredentials(DEFAULT_WIFI_SSID_2, DEFAULT_WIFI_PASSWORD_2);
    #endif
    #ifdef DEFAULT_WIFI_SSID_3
    appendToCredentials(DEFAULT_WIFI_SSID_3, DEFAULT_WIFI_PASSWORD_3);
    #endif

    return credentials;
}

void saveWiFiCredentials(const char* ssid, const char* password) {
    nvs_handle_t storage;
    nvs_open(NVS_PREFERENCES_STORAGE_NAME, NVS_READWRITE, &storage);
    nvs_set_str(storage, NVS_WIFI_SSID_CREDENTIALS_KEY, ssid);
    nvs_set_str(storage, NVS_WIFI_PASSWORD_CREDENTIALS_KEY, password);
    nvs_close(storage);
}

void cleanWiFiCredentials() {
    while(credentials) {
        wifi_credentials_t* current = credentials;
        credentials = credentials->next;
        delete current;
    }
}

void setupPreferences() {
    preferences = new preferences_t;
    nvs_handle_t storage;
    nvs_open(NVS_PREFERENCES_STORAGE_NAME, NVS_READWRITE, &storage);
    preferences->enable_display = NVS_ENABLE_DISPLAY_DEFAULT;
    nvs_get_i8(storage, NVS_ENABLE_DISPLAY, &(preferences->enable_display));
    preferences->display_refresh_period = NVS_DISPLAY_REFRESH_PERIOD_DEFAULT;
    nvs_get_u16(storage, NVS_DISPLAY_REFRESH_PERIOD, &(preferences->display_refresh_period));
    preferences->enable_presence_detection = NVS_ENABLE_PRESENCE_DETECTION_DEFAULT;
    nvs_get_i8(storage, NVS_ENABLE_PRESENCE_DETECTION, &(preferences->enable_presence_detection));
    preferences->journal_length = NVS_JOURNAL_LENGTH_DEFAULT;
    nvs_get_u16(storage, NVS_JOURNAL_LENGTH, &(preferences->journal_length));
    nvs_close(storage);
}

void saveSettings(preferences_t* prefs) {
    nvs_handle_t storage;
    nvs_open(NVS_PREFERENCES_STORAGE_NAME, NVS_READWRITE, &storage);
    // if (prefs->wifi_ssid.size() > 0) {
    //     nvs_set_str(storage, NVS_WIFI_SSID_CREDENTIALS_KEY, prefs->wifi_ssid.c_str());
    // }
    // if (prefs->wifi_password.size() > 0) {
    //     nvs_set_str(storage, NVS_WIFI_PASSWORD_CREDENTIALS_KEY, prefs->wifi_password.c_str());
    // }
    if (prefs->enable_display || prefs->enable_display == 0) {
        nvs_set_i8(storage, NVS_ENABLE_DISPLAY, prefs->enable_display);
    }
    if (prefs->display_refresh_period) {
        nvs_set_u16(storage, NVS_DISPLAY_REFRESH_PERIOD, prefs->display_refresh_period);
    }
    if (prefs->enable_presence_detection || prefs->enable_presence_detection == 0) {
        nvs_set_i8(storage, NVS_ENABLE_PRESENCE_DETECTION, prefs->enable_presence_detection);
    }
    if (prefs->journal_length || prefs->journal_length == 0) {
        nvs_set_u16(storage, NVS_JOURNAL_LENGTH, prefs->journal_length);
    }
    nvs_close(storage);
}

preferences_t* getPreferences() {
    return preferences;
}