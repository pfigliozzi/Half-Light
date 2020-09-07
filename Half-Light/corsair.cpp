#include "stdafx.h"
#include "CUESDK.h"
#include "CUELFX/CUELFX.h"
#include "Shared/LFX.h"
#include "CorsairLFX/CorsairLFX.h"
#include "CorsairLayers/CorsairLayers.h"

#include <iostream>
#include <stdlib.h>
#include <map>
#include <unordered_map>
#include <array>

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
	int totalKeys = keyboardLeds->numberOfLed;
	ledColors = new CorsairLedColor[totalKeys];

	for (int i = 0; i < totalKeys; ++i) {
		ledColors[i].ledId = keyboardLeds->pLedPosition[i].ledId;
		// Might want to move these values to global variable.
		ledColors[i].r = 255;
		ledColors[i].g = 0;
		ledColors[i].b = 0;
	}

	bool corsiarSuccess = CorsairSetLedsColors(totalKeys, ledColors);
	if (corsiarSuccess != true) {
		CorsairGetLastError();
		return -1;
	}

	return 0;
}

// FEEDBACK: Use changeKeyColor in setBaseColor in the for loop to change each key individually.
int changeKeyColor(CorsairLedId ledId)
{
	CorsairLedColor color;
	color.ledId = ledId;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	bool corsairSuccess = CorsairSetLedsColors(1, &color);
	return 0;
}

std::map<int, CorsairLedId> getCorsiarKeyMap()
{
	std::map<int, CorsairLedId> corsairKeyMap;
	corsairKeyMap.insert({ 0x1B, CLK_Escape });
	corsairKeyMap.insert({ 0x70, CLK_F1 });
	corsairKeyMap.insert({ 0x71, CLK_F2 });
	corsairKeyMap.insert({ 0x72, CLK_F3 });
	corsairKeyMap.insert({ 0x73, CLK_F4 });
	corsairKeyMap.insert({ 0x74, CLK_F5 });
	corsairKeyMap.insert({ 0x75, CLK_F6 });
	corsairKeyMap.insert({ 0x76, CLK_F7 });
	corsairKeyMap.insert({ 0x77, CLK_F8 });
	corsairKeyMap.insert({ 0x78, CLK_F9 });
	corsairKeyMap.insert({ 0x79, CLK_F10 });
	corsairKeyMap.insert({ 0x7A, CLK_F11 });
	corsairKeyMap.insert({ 0x7B, CLK_F12 });

	corsairKeyMap.insert({ 0xc0, CLK_GraveAccentAndTilde });
	corsairKeyMap.insert({ 0x31, CLK_1 });
	corsairKeyMap.insert({ 0x32, CLK_2 });
	corsairKeyMap.insert({ 0x33, CLK_3 });
	corsairKeyMap.insert({ 0x34, CLK_4 });
	corsairKeyMap.insert({ 0x35, CLK_5 });
	corsairKeyMap.insert({ 0x36, CLK_6 });
	corsairKeyMap.insert({ 0x37, CLK_7 });
	corsairKeyMap.insert({ 0x38, CLK_8 });
	corsairKeyMap.insert({ 0x39, CLK_9 });
	corsairKeyMap.insert({ 0x30, CLK_0 });
	corsairKeyMap.insert({ 0xBD, CLK_MinusAndUnderscore });
	corsairKeyMap.insert({ 0xbb, CLK_EqualsAndPlus });
	corsairKeyMap.insert({ 0x08, CLK_Backspace });

	corsairKeyMap.insert({ 0x09, CLK_Tab });
	corsairKeyMap.insert({ 0x51, CLK_Q });
	corsairKeyMap.insert({ 0x57, CLK_W });
	corsairKeyMap.insert({ 0x45, CLK_E });
	corsairKeyMap.insert({ 0x52, CLK_R });
	corsairKeyMap.insert({ 0x54, CLK_T });
	corsairKeyMap.insert({ 0x59, CLK_Y });
	corsairKeyMap.insert({ 0x55, CLK_U });
	corsairKeyMap.insert({ 0x49, CLK_I });
	corsairKeyMap.insert({ 0x4F, CLK_O });
	corsairKeyMap.insert({ 0x50, CLK_P });
	corsairKeyMap.insert({ 0xDB, CLK_BracketLeft });
	corsairKeyMap.insert({ 0xDD, CLK_BracketRight });
	corsairKeyMap.insert({ 0xDC, CLK_Backslash });

	corsairKeyMap.insert({ 0x14, CLK_CapsLock });
	corsairKeyMap.insert({ 0x41, CLK_A });
	corsairKeyMap.insert({ 0x53, CLK_S });
	corsairKeyMap.insert({ 0x44, CLK_D });
	corsairKeyMap.insert({ 0x46, CLK_F });
	corsairKeyMap.insert({ 0x47, CLK_G });
	corsairKeyMap.insert({ 0x48, CLK_H });
	corsairKeyMap.insert({ 0x4A, CLK_J });
	corsairKeyMap.insert({ 0x4B, CLK_K });
	corsairKeyMap.insert({ 0x4C, CLK_L });
	corsairKeyMap.insert({ 0xBA, CLK_SemicolonAndColon });
	corsairKeyMap.insert({ 0xDE, CLK_ApostropheAndDoubleQuote });
	// CLK_Enter is implemented in getAmbiguousKeyId

	// CLK_LeftShift is implemented in getShiftLedId
	corsairKeyMap.insert({ 0x5A, CLK_Z });
	corsairKeyMap.insert({ 0x58, CLK_X });
	corsairKeyMap.insert({ 0x43, CLK_C });
	corsairKeyMap.insert({ 0x56, CLK_V });
	corsairKeyMap.insert({ 0x42, CLK_B });
	corsairKeyMap.insert({ 0x4E, CLK_N });
	corsairKeyMap.insert({ 0x4D, CLK_M });
	corsairKeyMap.insert({ 0xBC, CLK_CommaAndLessThan });
	corsairKeyMap.insert({ 0xBE, CLK_PeriodAndBiggerThan });
	corsairKeyMap.insert({ 0xBF, CLK_SlashAndQuestionMark });
	// CLK_RightShift is implemented in getShiftLedId
	
	// CLK_LeftCtrl is implemented in getAmbiguousKeyId
	corsairKeyMap.insert({ 0x5B, CLK_LeftGui });
	// CLK_LeftAlt is implemented in getAmbiguousKeyId
	corsairKeyMap.insert({ 0x20, CLK_Space });
	// CLK_RightAlt is implemented in getAmbiguousKeyId
	corsairKeyMap.insert({ 0x5C, CLK_RightGui });
	corsairKeyMap.insert({ 0x5D, CLK_Application });
	// CLK_RightCtrl is implemented in getAmbiguousKeyId

	corsairKeyMap.insert({ 0x2C, CLK_PrintScreen });
	corsairKeyMap.insert({ 0x91, CLK_ScrollLock });
	corsairKeyMap.insert({ 0x13, CLK_PauseBreak });

	corsairKeyMap.insert({ 0x2D, CLK_Insert });
	corsairKeyMap.insert({ 0x24, CLK_Home });
	corsairKeyMap.insert({ 0x21, CLK_PageUp });

	corsairKeyMap.insert({ 0x2E, CLK_Delete });
	corsairKeyMap.insert({ 0x23, CLK_End });
	corsairKeyMap.insert({ 0x22, CLK_PageDown });

	corsairKeyMap.insert({ 0x26, CLK_UpArrow });
	corsairKeyMap.insert({ 0x25, CLK_LeftArrow });
	corsairKeyMap.insert({ 0x28, CLK_DownArrow });
	corsairKeyMap.insert({ 0x27, CLK_RightArrow });

	corsairKeyMap.insert({ 0x90, CLK_NumLock });
	corsairKeyMap.insert({ 0x6F, CLK_KeypadSlash });
	corsairKeyMap.insert({ 0x6A, CLK_KeypadAsterisk });
	corsairKeyMap.insert({ 0x6D, CLK_KeypadMinus });

	corsairKeyMap.insert({ 0x67, CLK_Keypad7 });
	corsairKeyMap.insert({ 0x68, CLK_Keypad8 });
	corsairKeyMap.insert({ 0x69, CLK_Keypad9 });

	corsairKeyMap.insert({ 0x6B, CLK_KeypadPlus });

	corsairKeyMap.insert({ 0x64, CLK_Keypad4 });
	corsairKeyMap.insert({ 0x65, CLK_Keypad5 });
	corsairKeyMap.insert({ 0x66, CLK_Keypad6 });

	corsairKeyMap.insert({ 0x61, CLK_Keypad1 });
	corsairKeyMap.insert({ 0x62, CLK_Keypad2 });
	corsairKeyMap.insert({ 0x63, CLK_Keypad3 });

	// CLK_KeypadEnter is implemented in getAmbiguousKeyId

	corsairKeyMap.insert({ 0x60, CLK_Keypad0 });
	corsairKeyMap.insert({ 0x6E, CLK_KeypadPeriodAndDelete });

	corsairKeyMap.insert({ 0xB2, CLK_Stop });
	corsairKeyMap.insert({ 0xB1, CLK_ScanPreviousTrack });
	corsairKeyMap.insert({ 0xB3, CLK_PlayPause });
	corsairKeyMap.insert({ 0xB0, CLK_ScanNextTrack });


	return corsairKeyMap;
}

std::map<int, CorsairLedId> corsairKeyMap = getCorsiarKeyMap();

struct LeftAndRightKeyIds
{
	CorsairLedId leftKey;
	CorsairLedId rightKey;
};

std::map<int, LeftAndRightKeyIds> getAmbiguousKeyMap()
{
	std::map<int, LeftAndRightKeyIds> ambiguousKeyMap;

	LeftAndRightKeyIds CTRLKeys;
	CTRLKeys.leftKey = CLK_LeftCtrl;
	CTRLKeys.rightKey = CLK_RightCtrl;
	ambiguousKeyMap.insert({ 0x11, CTRLKeys });

	LeftAndRightKeyIds AltKeys;
	AltKeys.leftKey = CLK_LeftAlt;
	AltKeys.rightKey = CLK_RightAlt;
	ambiguousKeyMap.insert({ 0x12, AltKeys });

	LeftAndRightKeyIds EnterKeys;
	EnterKeys.leftKey = CLK_Enter;
	EnterKeys.rightKey = CLK_KeypadEnter;
	ambiguousKeyMap.insert({ 0x0D, EnterKeys });

	return ambiguousKeyMap;
}

std::map<int, LeftAndRightKeyIds> ambiguousKeyMap = getAmbiguousKeyMap();

std::array<int, 5> ambiguousKeys = { 0x11, 0x12, 0x0D };

bool isAmbiguousKey(RAWINPUT* raw)
{
	for (int i = 0; i < ambiguousKeys.size(); ++i)
	{
		if (raw->data.keyboard.VKey == ambiguousKeys[i]) {
			return true;
		}
	}
	return false;
}

CorsairLedId getAmbiguousKeyId(RAWINPUT* raw)
{
	LeftAndRightKeyIds possibleKeys = ambiguousKeyMap[raw->data.keyboard.VKey];
	if (raw->data.keyboard.Flags == 0x00) {
		return possibleKeys.leftKey;
	}
	else if (raw->data.keyboard.Flags == 0x02) {
		return possibleKeys.rightKey;
	}
}

bool isShiftKey(RAWINPUT* raw)
{
	if (raw->data.keyboard.VKey == 0x10) {
		return true;
	}
	return false;
}

CorsairLedId getShiftLedId(RAWINPUT* raw)
{
	if (raw->data.keyboard.MakeCode == 0x2a) {
		return CLK_LeftShift;
	}
	return CLK_RightShift;
}

// Returns a CorsairLedId given RAWINPUT keyboard message from windows.
// Will use the hard coded values of the VKey codes and the MakeCodes 
// to determin the proper key.
// FEEDBACK Reorder the operations so that the corsairKeyMap check happens first and it will retun nulls for ambiguous keys
//		    and if the NULL is returned then you go into the functions that figures out which shift/ctrl/alt it is.
CorsairLedId getCorsairLedId(RAWINPUT* raw)
{
	if (isShiftKey(raw)) {
		return getShiftLedId(raw);
	}
	else if (isAmbiguousKey(raw)) {
		return getAmbiguousKeyId(raw);
	}
	else
	{
		return corsairKeyMap[raw->data.keyboard.VKey];
	}
	
}