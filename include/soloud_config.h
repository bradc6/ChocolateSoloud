#pragma once
/*
SoLoud audio engine
Copyright (c) 2013-2020 Jari Komppa

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

//********************************
//********************************
//Build information
//********************************
//********************************
#if !defined(SOLOUD_BUILD_TYPE_DEBUG)
#define SOLOUD_BUILD_TYPE_DEBUG 1
#endif

#if !defined(SOLOUD_VERSION)
#define SOLOUD_VERSION 202002
#endif

//********************************
//********************************
//Error Handling
//********************************
//********************************

//********************************
//********************************
//Platform Detection
//********************************
//********************************
#if defined(__linux__)
    #define SOLOUD_TARGET_PLATFORM_LINUX 1
#else
    #define SOLOUD_TARGET_PLATFORM_LINUX 0
#endif

//Any undefined platform is false
#if defined(_WIN32)
    #define SOLOUD_TARGET_PLATFORM_WINDOWS 1
#else
    #define SOLOUD_TARGET_PLATFORM_WINDOWS 0
#endif

#if !defined(SOLOUD_TARGET_PLATFORM_LINUX)
#define SOLOUD_TARGET_PLATFORM_LINUX 0
#endif

//*********************************************
//*********************************************
//Enable/Disable features
//*********************************************
//*********************************************
#if !defined(SOLOUD_FEATURE_THREADED_LOADER)
#define SOLOUD_FEATURE_THREADED_LOADER 1
#endif

#if !defined(DISABLE_SIMD)
#if defined(__x86_64__) || defined( _M_X64 ) || defined( __i386 ) || defined( _M_IX86 )
#define SOLOUD_SSE_INTRINSICS 1
#else
#define SOLOUD_SSE_INTRINSICS 0
#endif
#else
#define SOLOUD_SSE_INTRINSICS 0
#endif
