#include "sensors.h"

uint64_t last_motion_detected = 0;
bool is_indicating = false;
bool motion_detected = false;

void IRAM_ATTR motionDetection() {
    detachInterrupt(digitalPinToInterrupt(SR602_PIN));
    motion_detected = true;
}

void setupSensors() {
    pinMode(SR602_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SR602_PIN), motionDetection, RISING);
}

void onMotionDetected() {
    motion_detected = false;
    last_motion_detected = millis();
    is_indicating = true;
    digitalWrite(LED_PIN, HIGH);
}

void onMotionStopped() {
    digitalWrite(LED_PIN, LOW);
    is_indicating = false;
    attachInterrupt(digitalPinToInterrupt(SR602_PIN), motionDetection, RISING);
}

uint64_t sensorsLoop() {
    if (motion_detected) {
        onMotionDetected();
        return last_motion_detected;
    }
    if (is_indicating && (millis() - last_motion_detected) > MOTION_LED_INDICATION_PERIOD) {
        onMotionStopped();
    }
    return 0;
}