#pragma once

// Platform detection
#ifdef _WIN32
    #define CX_PLATFORM_WINDOWS
#else
    #error CompanionX only supports Windows for now!
#endif

// For static library, define API macros as empty
#define CX_API
#define COMPANIONX_API

// If we were building a DLL, we would use this:
/*
// DLL support (for future use)
#ifdef CX_PLATFORM_WINDOWS
    #ifdef CX_BUILD_DLL
        #define CX_API __declspec(dllexport)
        #define COMPANIONX_API __declspec(dllexport)
    #else
        #define CX_API __declspec(dllimport)
        #define COMPANIONX_API __declspec(dllimport)
    #endif
#else
    #define CX_API
    #define COMPANIONX_API
#endif
*/

