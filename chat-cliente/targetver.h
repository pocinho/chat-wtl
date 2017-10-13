#pragma once
#ifndef TARGETVER_H_INCLUDED
#define TARGETVER_H_INCLUDED

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

/////////////////////////////////////////////////////////////////////
// Windows Operating System internal platform version.
// http://msdn.microsoft.com/en-us/library/6sehtctf.aspx

// Target Windows XP and above:
#ifndef TARGETVER_WINDOWS_XP
#define TARGETVER_WINDOWS_XP 0x0501
#endif
// Target Windows Server 2003 and above:
#ifndef TARGETVER_WINDOWS_SERVER2003
#define TARGETVER_WINDOWS_SERVER2003 0x0502
#endif
// Target Windows Vista and above:
#ifndef TARGETVER_WINDOWS_VISTA
#define TARGETVER_WINDOWS_VISTA 0x0600
#endif
// Target Windows 7 and above:
#ifndef TARGETVER_WINDOWS_7
#define TARGETVER_WINDOWS_7 0x0601
#endif
// Target Windows 8 and above:
#ifndef TARGETVER_WINDOWS_8
#define TARGETVER_WINDOWS_8 0x0602
#endif
// Target Windows 8.1 and above:
#ifndef TARGETVER_WINDOWS_8_1
#define TARGETVER_WINDOWS_8_1 0x0603
#endif
// Target Windows 10 and above:
#ifndef TARGETVER_WINDOWS_10
#define TARGETVER_WINDOWS_10 0x0A00
#endif

/////////////////////////////////////////////////////////////////////
// Define TARGETVER to target minimum platform version.
#define TARGETVER TARGETVER_WINDOWS_7

#if defined(TARGETVER)
#include <WinSDKVer.h>
#define _WIN32_WINNT TARGETVER
#endif

#include <SDKDDKVer.h>

#endif // !TARGETVER_H_INCLUDED
