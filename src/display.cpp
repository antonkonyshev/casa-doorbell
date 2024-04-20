#include "display.h"

TFT_eSPI tft = TFT_eSPI();

bool setupDisplay() {
    tft.init();
    tft.fillScreen(BACKGROUND_COLOR);
    tft.setTextColor(FOREGROUND_COLOR, BACKGROUND_COLOR);
    return true;
}