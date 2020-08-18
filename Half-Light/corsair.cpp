#include "stdafx.h"
#include "CUESDK.h"
#include "CUELFX/CUELFX.h"
#include "Shared/LFX.h"
#include "CorsairLFX/CorsairLFX.h"
#include "CorsairLayers/CorsairLayers.h"

#include <iostream>
#include <stdlib.h>
#include <vector>

const char* errorString(CorsairError error)
{
	switch (error) {
	case CE_Success:
		return "Success";
	case CE_ServerNotFound:
		return "Server not found";
	case CE_NoControl:
		return "No control";
	case CE_ProtocolHandshakeMissing:
		return "Protocol handshake missing";
	case CE_IncompatibleProtocol:
		return "Incompatible protocol";
	case CE_InvalidArguments:
		return "Invalid Arguments";
	default:
		return "Unknown error";
	}
}

int keyboardIndex()
{
	int deviceCount = CorsairGetDeviceCount();
	for (int i = 0; i < deviceCount; ++i) {
		CorsairDeviceInfo *info = CorsairGetDeviceInfo(i);
		if (info->type == CDT_Keyboard) {
			return i;
		}
	}

	return -1;
}

int initKeyboard()
{
	// Standard Keyboard setup stuff.
	CorsairPerformProtocolHandshake();
	if (const auto error = CorsairGetLastError()) {
		std::cerr << "Protocol Handshake failed: " << errorString(error) << std::endl;
		system("pause");
		return -1;
	}

	const int deviceIndex = keyboardIndex();
	if (deviceIndex < 0) {
		std::cerr << "Unable to find keyboard index" << std::endl;
		system("pause");
		return -1;
	}

	return 0;
}

int setBaseColor()
{
	CorsairLedPositions* keyboardLeds;
	keyboardLeds = CorsairGetLedPositions();
	CorsairLedColor* ledColors;
	ledColors = new CorsairLedColor[keyboardLeds->numberOfLed];
	//std::vector<CorsairLedColor> ledColors; // Have to use vector because when making arrays the size needs to be const at COMPILE time.
	//vector<CorsairLedPosition> pLeds;

	for (int i = 0; i < keyboardLeds->numberOfLed; ++i) {
		ledColors[i].ledId = keyboardLeds->pLedPosition[i].ledId;
		// Might want to move these values to global variable.
		ledColors[i].r = 255;
		ledColors[i].g = 0;
		ledColors[i].b = 0;
	}

	CorsairSetLedsColors(keyboardLeds->numberOfLed, ledColors);

	return 0;
}