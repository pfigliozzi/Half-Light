#pragma once
#include "CUESDK.h"
#include "CUELFX/CUELFX.h"
#include "Shared/LFX.h"
#include "CorsairLFX/CorsairLFX.h"
#include "CorsairLayers/CorsairLayers.h"

#include <iostream>

const char* errorString(CorsairError error);
int keyboardIndex();
int initKeyboard();
int setBaseColor();
