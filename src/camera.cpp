#include "camera.h"

unsigned char bmpHeader[BMP::headerSize];
OV7670 *camera;

bool setupCamera() {
    camera = new OV7670(OV7670::Mode::QQVGA_RGB565, CAMERA_SIOD, CAMERA_SIOC,
        CAMERA_VSYNC, CAMERA_HREF, CAMERA_XCLK, CAMERA_PCLK, CAMERA_D0,
        CAMERA_D1, CAMERA_D2, CAMERA_D3, CAMERA_D4, CAMERA_D5, CAMERA_D6,
        CAMERA_D7);
    BMP::construct16BitHeader(bmpHeader, camera->xres, camera->yres);
    return true;
}

OV7670* getCamera() {
    return camera;
}

unsigned char* getBmpHeader() {
    return bmpHeader;
}