#include "OV7670.h"
#include "BMP.h"
#include "pinout.h"

bool setupCamera();
OV7670* getCamera();
unsigned char* getBmpHeader();