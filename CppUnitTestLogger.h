// This is a part of the VSCppUnit C++ Unit Testing Framework.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This class in this file may be used to write informational messages to the log file.

#pragma once

#ifndef MS_CPP_UNITTESTFRAMEWORK_LOGGER
#define MS_CPP_UNITTESTFRAMEWORK_LOGGER

#include "CppUnitTestCommon.h"

namespace Microsoft{ namespace VisualStudio {namespace CppUnitTestFramework
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /// Logger
    class Logger
    {
    public:
        static void WriteMessage(const wchar_t* message)
        {
            WriteMessageImplW(reinterpret_cast<const unsigned short*>(message));
        }

        static void WriteMessage(const char* message)
        {
            WriteMessageImplA(message);
        }

    private:
        static __declspec(dllexport) void __stdcall WriteMessageImplW(const unsigned short* messpage);

        static __declspec(dllexport) void __stdcall WriteMessageImplA(const char* messpage);
    };
}}}

#endif /*MS_CPP_UNITTESTFRAMEWORK_LOGGER*/