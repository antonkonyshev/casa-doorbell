#include "network.h"

WiFiMulti wifiMulti;
AsyncWebServer server(API_PORT);
bool wifiApMode = false;

void setupRouting() {
    server.on("/", [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        AsyncResponseStream* response = request->beginResponseStream("image/bmp");
        response->setCode(200);
        response->write(getBmpHeader(), getBmpHeaderSize());
        response->write(getFrame(), getFrameSize());
        request->send(response);
        digitalWrite(LED_PIN, LOW);
    });

    server.on("/service", [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        // The service endpoint response is a constant for the service, since it doesn't changes within time while the device is working
        request->send(200, "application/json", "{\"service\":\"camera\",\"name\":\"Door\",\"id\":\"apartments-door-1\",\"sensors\":[\"picture\"]}");
        digitalWrite(LED_PIN, LOW);
    });

    server.on("/settings", HTTP_POST, [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        preferences_t* preferences = getPreferences();
        size_t params = request->params();
        for (int i = 0; i < params; i++) {
            AsyncWebParameter* param = request->getParam(i);
            if (param->name() == "enable_display") {
                preferences->enable_display = param->value().toInt();
            } else if (param->name() == "display_refresh_period") {
                preferences->display_refresh_period = param->value().toInt();
            }
        }
        request->send(200);
        saveSettings(preferences);
        ESP_LOGI("preferences_save", "ED: %d DR: %d", preferences->enable_display, preferences->display_refresh_period);
        request->send(200);
        digitalWrite(LED_PIN, LOW);
    });

    server.on("/settings", [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        preferences_t* preferences = getPreferences();
        char buffer[512] = {0};
        snprintf(buffer, 512,
            "{\"enable_display\":%d,\"display_refresh_period\":%d}",
            preferences->enable_display, preferences->display_refresh_period);
        request->send(200, "application/json", buffer);
        ESP_LOGI("preferences_get", "ED: %d DR: %d",
            preferences->enable_display, preferences->display_refresh_period);
        digitalWrite(LED_PIN, LOW);
    });

    server.begin();
}

void indicateSOS() {
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    for (uint8_t idx = 0; idx < 3; idx++) {
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
    }
    delay(600);
    for (uint8_t idx = 0; idx < 3; idx++) {
        digitalWrite(LED_PIN, HIGH);
        delay(600);
        digitalWrite(LED_PIN, LOW);
        delay(600);
    }
    delay(600);
    for (uint8_t idx = 0; idx < 3; idx++) {
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
    }
    delay(1000);
}

void wifiKeepAlive() {
    if (wifiApMode) {
        indicateSOS();
        return;
    }
    uint8_t ledState = LOW;
    uint8_t retries = 0;
    while (wifiMulti.run(WIFI_CONNECTION_TIMEOUT * 1000) != WL_CONNECTED) {
        ledState = ledState == LOW ? HIGH : LOW;
        digitalWrite(LED_PIN, ledState);
        delay(1000);
        retries += 1;
        if (retries > WIFI_STA_CONNECT_RETRIES) {
            break;
        }
    }
    if (retries > WIFI_STA_CONNECT_RETRIES) {
        WiFi.mode(WIFI_MODE_AP);
        WiFi.softAP("home_esp_country_house_room_1");
        ESP_LOGI("home", "Couldn't connect to any available WiFi network. Fallback to access point mode with ssid 'home_esp_.*'. Please, connect to configure the device. After the configuration a reboot will be necessary.");
        wifiApMode = true;
        indicateSOS();
    }
    digitalWrite(LED_PIN, LOW);
}

bool setupWifi() {
    WiFi.mode(WIFI_MODE_STA);
    wifi_credentials_t* credentials = loadWiFiCredentials();
    while (credentials) {
        wifiMulti.addAP(credentials->ssid.c_str(), credentials->password.c_str());
        credentials = credentials->next;
    }
    cleanWiFiCredentials();
    wifiKeepAlive();
    digitalWrite(LED_PIN, HIGH);
    return true;
}
