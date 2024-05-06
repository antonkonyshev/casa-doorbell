#pragma once

#include "pinout.h"
#include "CasaLib/journal.h"
#include "preferences.h"

#define MOTION_LED_INDICATION_PERIOD 5000  // Period of led indication after motion detection (in milliseconds)

void setupSensors();
uint64_t sensorsLoop();