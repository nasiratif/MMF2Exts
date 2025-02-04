#pragma once

// Do not move XXXEXT after #include of DarkEdif.h!
// #define TGFEXT	// TGF2, Fusion 2.x Std, Fusion 2.x Dev
#define MMFEXT		// Fusion 2.x, Fusion 2.x Dev
// #define PROEXT	// Fusion 2.x Dev only

#define JSON_COMMENT_MACRO Extension::Version

#include "DarkEdif.h"

#include "..\Inc\Windows\ksnd.h"
// Static linking of KSND
#pragma comment(lib, "..\\Lib\\Windows\\ksndstatic.lib")
#pragma comment(lib, "winmm.lib")

#define CheckForPlayer(makeError, funcName, ...) \
	if (!curPlayer) { \
		if constexpr (makeError) \
			CreateError(_T(""## funcName##": No player selected!")); \
		return __VA_ARGS__; \
	}

// edPtr : Used at edittime and saved in the MFA/CCN/EXE files
struct EDITDATA
{
	NO_DEFAULT_CTORS(EDITDATA);
	// Header - required, must be first variable in EDITDATA
	extHeader		eHeader;

	// Object's data

//	short			swidth;
//	short			sheight;

	// Keep DarkEdif variables as last. Undefined behaviour otherwise.
	DarkEdif::Properties Props;
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
