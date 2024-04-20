#include <string>

typedef struct wifi_credentials_s {
    std::string ssid;
    std::string password;
    wifi_credentials_s* next;

    wifi_credentials_s() : next(nullptr) {}
} wifi_credentials_t;

wifi_credentials_t* loadWiFiCredentials();
void saveWiFiCredentials(const char* ssid, const char* password);
void cleanWiFiCredentials();
