#pragma once

// Do not move XXXEXT after #include of DarkEdif.h!
// #define TGFEXT	// TGF2, Fusion 2.x Std, Fusion 2.x Dev
#define MMFEXT		// Fusion 2.x, Fusion 2.x Dev
// #define PROEXT	// Fusion 2.x Dev only

#define JSON_COMMENT_MACRO lacewing::relayclient::buildnum, STRIFY(CONFIG)

// Lacewing-required imports for accessing Windows sockets
#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#pragma comment(lib, "mpr.lib")
#pragma comment(lib, "secur32.lib")
#pragma comment(lib, "crypt32.lib")
#endif

#ifndef _lacewing_static
#error Required Lacewing definitions are not in project settings.
#endif

#include "DarkEdif.h"

#include "../Lib/Shared/Lacewing/Lacewing.h"
#include "LacewingFunctions.h"

#ifdef _WIN32
#pragma comment(lib, "..\\Lib\\Windows\\zlib.lib")
#include "..\Inc\Windows\zlib.h"
#else
#include <zlib.h>
// libz included in project settings
#endif
#include <iomanip>

#include "MultiThreading.h"

// edPtr : Used at edittime and saved in the MFA/CCN/EXE files
struct EDITDATA
{
	NO_DEFAULT_CTORS(EDITDATA);
	// Header - required, must be first variable in EDITDATA
	extHeader			eHeader;

	// Because Lacewing Blue can be interchanged with Lacewing Relay by replacing the MFXes,
	// we don't use DarkEdif's automatic property system (except for the menus), instead
	// matching the Relay's memory layout, and changing Edittime.cpp.

	// Any random edittime stuff? Place here.
	char pad0[5];				// For matching Relay Client extension
	bool automaticClear;
	bool multiThreading;
	bool isGlobal;
	// UTF-8 global ID
	char edGlobalID[255];
	bool timeoutWarningEnabled;
	bool fullDeleteEnabled;
	char pad1[256];

	// Note: To match Lacewing Relay Client, this struct's size must be 544 bytes.
	// NOPROPS is used to manually set the size of this struct and access properties in it.
};

class Extension;

struct RUNDATA
{
	// Main header - required
	HeaderObject rHo;

	// Optional headers - depend on the OEFLAGS value, see documentation and examples for more info
//	rCom			rc;				// Common structure for movements & animations
//	rMvt			rm;				// Movements
//	Sprite			rs;				// Sprite (displayable objects)
//	AltVals			rv;				// Alterable values

	// Required
	Extension * pExtension;

	/*
		You shouldn't add any variables or anything here. Add them as members
		of the Extension class (Extension.h) instead.
	*/
};

#include "Extension.h"
