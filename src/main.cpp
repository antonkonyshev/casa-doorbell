#include "main.h"

void setup() {
    Serial.begin(9600);
    delay(100);
    Serial.println("");
    Serial.println("--------------------------------- Camera ---------------------------------");

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    btStop();
    setupCamera();
    setupDisplay();
    setupWifi();
    setupRouting();

    Serial.println("");
    Serial.printf("Total  heap: %8d bytes     |     Free  heap: %8d bytes\n", ESP.getHeapSize(), ESP.getFreeHeap());
    Serial.printf("Total PSRAM: %8d bytes     |     Free PSRAM: %8d bytes\n", ESP.getPsramSize(), ESP.getFreePsram());
    Serial.printf("Sketch size: %8d bytes     |     Free space: %8d bytes\n", ESP.getSketchSize(), ESP.getFreeSketchSpace());
    Serial.println("");

    digitalWrite(LED_PIN, LOW);
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    displayRGB565(getFrame(), getCameraXRes(), getCameraYRes());
    delay(1000);
    wifiKeepAlive();
    digitalWrite(LED_PIN, LOW);
}