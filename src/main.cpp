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
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    printHardwareInfo();

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

    printMemoryInfo();

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