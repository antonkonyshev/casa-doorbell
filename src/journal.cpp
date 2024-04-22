#include "journal.h"

record_t* journal;

void saveJournalRecord(std::string message, uint8_t priority) {
    preferences_t* preferences = getPreferences();
    if (!preferences->journal_length) {
        return;
    }
    record_t* record = new record_t;
    record->timestamp = millis();
    record->message = message;
    record->priority = priority;
    record->next = journal;
    journal = record;
    uint16_t size = 1;
    record_t* previous;
    while (record->next != NULL) {
        size += 1;
        previous = record;
        record = record->next;
        if (size > preferences->journal_length) {
            delete previous;
        }
    }
    if (size > preferences->journal_length && record) {
        delete record;
    }
}

record_t* getJournal() {
    return journal;
}

void cleanJournal() {
    if (journal->next) {
        record_t* record = journal->next;
        while (record) {
            record_t* previous = record;
            record = record->next;
            delete previous;
        }
    }
    if (journal) {
        delete journal;
    }
}