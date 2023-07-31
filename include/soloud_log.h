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

#include "soloud_config.h"
#include <cstdio>
#include <cstdarg>

namespace SoLoud
{
    enum LogSeverity : int
    {
        Trace = 0,
        Debug = 100,
        Info = 200,
        Warning = 300,
        Error = 400,
        Fatal = 500,
    };

    enum class LogCategory : int
    {
        General = 0,
        PCMLoader,
        NumberOfCategories
    };

    const char* c_LogCategoryToString[] =
    {
        "General",
        "PCMLoader",
    };

    static_assert(sizeof(c_LogCategoryToString) / sizeof(c_LogCategoryToString[0]) == static_cast<int>(LogCategory::NumberOfCategories), "LogCategory and c_LogCategoryToString must be the same size and order");

    inline void LogMessage(const LogSeverity severity, LogCategory category, const char* messageFormat, ...)
    {
    #if SOLOUD_BUILD_TYPE_DEBUG
        va_list args;
        va_start (args, messageFormat);
        vprintf(messageFormat, args);
        va_end (args);
    #endif
    }
} //namespace SoLoud
