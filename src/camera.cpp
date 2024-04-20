#include "camera.h"

OV7670 *camera;
uint8_t bmpHeader[BMP::headerSize];
size_t frameSize;

bool setupCamera() {
    camera = new OV7670(OV7670::Mode::QQVGA_RGB565, CAMERA_SIOD, CAMERA_SIOC,
        CAMERA_VSYNC, CAMERA_HREF, CAMERA_XCLK, CAMERA_PCLK, CAMERA_D0,
        CAMERA_D1, CAMERA_D2, CAMERA_D3, CAMERA_D4, CAMERA_D5, CAMERA_D6,
        CAMERA_D7);
    BMP::construct16BitHeader(bmpHeader, camera->xres, camera->yres);
    frameSize = camera->xres * camera->yres * 2;
    return true;
}

uint8_t* getFrame() {
    camera->oneFrame();
    return camera->frame;
}

uint8_t* getBmpHeader() {
    return bmpHeader;
}

size_t getFrameSize() {
    return frameSize;
}

size_t getBmpHeaderSize() {
    return BMP::headerSize;
}

int getCameraXRes() {
    return camera->xres;
}

int getCameraYRes() {
    return camera->yres;
}