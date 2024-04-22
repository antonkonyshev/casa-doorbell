#pragma once

#include "OV7670.h"
#include "BMP.h"
#include "pinout.h"

bool setupCamera();
uint8_t* getFrame();
uint8_t* getBmpHeader();
size_t getFrameSize();
size_t getBmpHeaderSize();
int getCameraXRes();
int getCameraYRes();