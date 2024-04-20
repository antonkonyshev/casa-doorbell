#include "display.h"

TFT_eSPI tft = TFT_eSPI();

bool setupDisplay() {
    tft.init();
    tft.fillScreen(BACKGROUND_COLOR);
    tft.setTextColor(FOREGROUND_COLOR, BACKGROUND_COLOR);
    return true;
}

void displayRGB565(uint8_t* frame, int xres, int yres) {
    tft.setAddrWindow(0, 0, yres - 1, xres - 1);
    int i = 0;
    for (int x = 0; x < xres; x++) {
        for (int y = 0; y < yres; y++) {
            i = (y * xres + x) << 1;
            tft.pushColor((frame[i] | (frame[i+1] << 8)));
        }
    }
}