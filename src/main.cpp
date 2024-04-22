#include "main.h"

hw_timer_t* display_timer = NULL;
bool perform_display_refresh = false;
bool is_presence_detection_enabled = false;

void performDisplayRefresh() {
    perform_display_refresh = true;
}

void setupTimers() {
    display_timer = timerBegin(0, 8000, true);
    timerAttachInterrupt(display_timer, &performDisplayRefresh, true);
    timerAlarmWrite(display_timer, getPreferences()->display_refresh_period * 10000, true);
    timerAlarmEnable(display_timer);
}

void setup() {
    Serial.begin(9600);
    delay(100);
    Serial.println("");
    Serial.println("--------------------------------- Camera ---------------------------------");

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    btStop();
    setupPreferences();
    preferences_t* preferences = getPreferences();
    setupCamera();
    if (preferences->enable_display > 0) {
        setupDisplay();
    }
    setupWifi();
    setupRouting();
    if (preferences->enable_display > 0) {
        setupTimers();
    }
    is_presence_detection_enabled = bool(preferences->enable_presence_detection > 0);
    if (is_presence_detection_enabled > 0) {
        setupSensors();
    }

    Serial.println("");
    Serial.printf("Total  heap: %8d bytes     |     Free  heap: %8d bytes\n", ESP.getHeapSize(), ESP.getFreeHeap());
    Serial.printf("Total PSRAM: %8d bytes     |     Free PSRAM: %8d bytes\n", ESP.getPsramSize(), ESP.getFreePsram());
    Serial.printf("Sketch size: %8d bytes     |     Free space: %8d bytes\n", ESP.getSketchSize(), ESP.getFreeSketchSpace());
    Serial.println("");

    digitalWrite(LED_PIN, LOW);
}

void loop() {
    if (perform_display_refresh) {
        digitalWrite(LED_PIN, HIGH);
        perform_display_refresh = false;
        displayRGB565(getFrame(), getCameraXRes(), getCameraYRes());
        wifiKeepAlive();
        digitalWrite(LED_PIN, LOW);
    }
    if (is_presence_detection_enabled) {
        sensorsLoop();
    }
}