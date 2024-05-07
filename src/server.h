#pragma once

#include <ESPAsyncWebServer.h>

#include "CasaLib/server.h"
#include "camera.h"

#define API_PORT 80

void serviceInfoResponsePayload(char* buffer);
void setupRouting();