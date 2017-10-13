// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#ifndef STDAFX_H_INCLUDED
#define STDAFX_H_INCLUDED

/////////////////////////////////////////////////////////////////////
// Compiler configuration:

// Default to strict compiler checks:
#ifndef STRICT
#define STRICT 1
#endif

// Default to unicode applications:
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

// Define DEBUG when _DEBUG is defined:
#ifdef _DEBUG
#ifndef DEBUG
#define DEBUG
#endif
#endif

/////////////////////////////////////////////////////////////////////
// Platform configuration:

#include "targetver.h"

/////////////////////////////////////////////////////////////////////
// Headers configuration:
//

// Exclude rarely-used components from Windows headers:
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// Exclude COM serial port programming facilities:
#ifndef NOCOMM
#define NOCOMM
#endif

// Include <Windows.h> header:
#include <Windows.h>

/////////////////////////////////////////////////////////////////////
// Embed common controls support in the application:

#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

// embed the manifest dependency in the application:
#if defined(_M_IX86)
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined(_M_X64)
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined(_M_IA64)
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

/////////////////////////////////////////////////////////////////////
// Additional header files:

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit



#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>
#include <atlcrack.h>
#include <atlctrls.h>
#include <atlmisc.h>
#include <atlddx.h>
#include <atlframe.h>

#include <wtlthread.h>

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#include <string>
#include <vector>



// TODO:

//const wchar_t * ConvertToWideChar(const char * c)
//{
//	const size_t cSize = strlen(c) + 1;
//	wchar_t * wc = new wchar_t[cSize];
//	size_t outSize;
//	mbstowcs_s(&outSize, wc, cSize, c, cSize -1);
//	return wc;
//}



#endif // !STDAFX_H_INCLUDED