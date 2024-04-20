// #include "Arduino.h"
#define PIN_PWDN -1
#define PIN_RESET -1
#define PIN_SIOD 21
#define PIN_SIOC 22
#define PIN_VSYNC 34
#define PIN_HREF 35
#define PIN_XCLK 32
#define PIN_PCLK 33
#define PIN_D0 27
#define PIN_D1 17
#define PIN_D2 16
#define PIN_D3 15
#define PIN_D4 14
#define PIN_D5 13
#define PIN_D6 12
#define PIN_D7 4
/*
    esp_err_t camera_example_init(){
        return esp_camera_init(&camera_example_config);
    }

    esp_err_t camera_example_capture(){
        //capture a frame
        camera_fb_t * fb = esp_camera_fb_get();
        if (!fb) {
            ESP_LOGE(TAG, "Frame buffer could not be acquired");
            return ESP_FAIL;
        }

        //replace this with your own function
        display_image(fb->width, fb->height, fb->pixformat, fb->buf, fb->len);

        //return the frame buffer back to be reused
        esp_camera_fb_return(fb);

        return ESP_OK;
    }
*/


#include "esp_camera.h"
#include "ESPAsyncWebServer.h"

void setupWebServer();