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
        saveSettings(request);
        request->send(200);
        digitalWrite(LED_PIN, LOW);
    });

    server.on("/settings", [](AsyncWebServerRequest* request) {
        digitalWrite(LED_PIN, HIGH);
        char payload[512] = {0};
        serializeSettings(payload);
        request->send(200, "application/json", payload);
        digitalWrite(LED_PIN, LOW);
    });

    server.begin();
}