#include "server.h"

AsyncWebServer server(API_PORT);

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

    server.on("/journal", [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);

        digitalWrite(LED_PIN, LOW);
    });

    server.on("/service", [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        // The service endpoint response is a constant for the service, since it doesn't changes within time while the device is working
        request->send(200, "application/json", "{\"service\":\"door\",\"name\":\"Door\",\"id\":\"" + String(DEVICE_ID) + "\",\"sensors\":[\"picture\",\"presence\"]}");
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
            } else if (param->name() == "enable_presence_detection") {
                preferences->enable_presence_detection = param->value().toInt();
            } else if (param->name() == "journal_length") {
                preferences->journal_length = param->value().toInt();
            }
        }
        request->send(200);
        saveSettings(preferences);
        ESP_LOGI("preferences_save", "ED: %d DR: %d PD: %d JL: %d", preferences->enable_display,
            preferences->display_refresh_period, preferences->enable_presence_detection,
            preferences->journal_length);
        request->send(200);
        digitalWrite(LED_PIN, LOW);
    });

    server.on("/settings", [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        preferences_t* preferences = getPreferences();
        char buffer[512] = {0};
        snprintf(buffer, 512,
            "{\"enable_display\":%d,\"display_refresh_period\":%d,\"enable_presence_detection\":%d,\"journal_length\":%d}",
            preferences->enable_display, preferences->display_refresh_period, preferences->enable_presence_detection,
            preferences->journal_length);
        request->send(200, "application/json", buffer);
        digitalWrite(LED_PIN, LOW);
    });

    server.begin();
}