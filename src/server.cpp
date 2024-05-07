#include "server.h"

AsyncWebServer server(API_PORT);

void serviceInfoResponsePayload(char* buffer) {
    sprintf(buffer, "{\"service\":\"door\",\"name\":\"Door\",\"id\":\"%s\",\"sensors\":[\"picture\",\"presence\"]}", DEVICE_ID);
}

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

    server.on("/journal", handleJournalRequest);
    server.on("/service", handleServiceInfoRequest);
    server.on("/settings", HTTP_POST, handleSettingsEditRequest);
    server.on("/settings", handleSettingsReadRequest);

    server.begin();
}