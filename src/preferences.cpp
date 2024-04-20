#include "preferences.h"

wifi_credentials_t* credentials;

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

void cleanWiFiCredentials() {
    while(credentials) {
        wifi_credentials_t* current = credentials;
        credentials = credentials->next;
        delete current;
    }
}
