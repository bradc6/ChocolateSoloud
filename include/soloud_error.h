/*
SoLoud audio engine
Copyright (c) 2013-2014 Jari Komppa

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
#ifndef SOLOUD_ERROR_H
#define SOLOUD_ERROR_H

#ifdef SOLOUD_NO_ASSERTS
#define SOLOUD_ASSERT(x)
#else
#ifdef _MSC_VER
#include <stdio.h> // for sprintf in asserts
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h> // only needed for OutputDebugStringA, should be solved somehow.
#define SOLOUD_ASSERT(x) if (!(x)) { char temp[200]; sprintf(temp, "%s(%d): assert(%s) failed.\n", __FILE__, __LINE__, #x); OutputDebugStringA(temp); __debugbreak(); }
#else
#include <assert.h> // assert
#define SOLOUD_ASSERT(x) assert(x)
#define SOLOUD_ASSERT_MESSAGE(x, m) SOLOUD_ASSERT(x)
#endif
#endif

namespace SoLoud
{
    enum SOLOUD_ERRORCODE : int
	{
		SO_NO_ERROR       = 0, // No error
		INVALID_PARAMETER = 1, // Some parameter is invalid
		FILE_NOT_FOUND    = 2, // File not found
		FILE_LOAD_FAILED  = 3, // File found, but could not be loaded
		DLL_NOT_FOUND     = 4, // DLL not found, or wrong DLL
		OUT_OF_MEMORY     = 5, // Out of memory
		NOT_IMPLEMENTED   = 6, // Feature not implemented
		UNKNOWN_ERROR     = 7  // Other error
	};

    // Translate error number to an asciiz string
    const char * getErrorString(SOLOUD_ERRORCODE aErrorCode);
};
#endif
