#pragma once

#include <Arduino.h>

#include "preferences.h"

typedef struct record_s {
    uint64_t timestamp;
    std::string message;
    uint8_t priority;
    record_s* next;

    record_s() : timestamp(millis()), message(""),
        priority(1), next(NULL) {}
} record_t;

void saveRecord(std::string message, uint8_t priority);
record_t* getJournal();
void cleanJournal();