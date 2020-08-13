#include "CUESDK.h"
#include "CUELFX/CUELFX.h"
#include "Shared/LFX.h"
#include "CorsairLFX/CorsairLFX.h"
#include "CorsairLayers/CorsairLayers.h"

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