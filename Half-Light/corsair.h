#pragma once
#include "CUESDK.h"
#include "CUELFX/CUELFX.h"
#include "Shared/LFX.h"
#include "CorsairLFX/CorsairLFX.h"
#include "CorsairLayers/CorsairLayers.h"

#include <iostream>
#include <map>

const char* errorString(CorsairError error);
int keyboardIndex();
int initKeyboard();
int setBaseColor();
std::map<int, CorsairLedId> getCorsiarKeyMap();
int changeKeyColor(CorsairLedId ledId);
CorsairLedId getCorsairLedId(RAWINPUT* raw);