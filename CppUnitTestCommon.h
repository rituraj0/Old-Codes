// This is a part of the VSCppUnit C++ Unit Testing Framework.
// Copyright (C) Microsoft Corporation
// All rights reserved.

#pragma once

#ifndef MS_CPP_UNITTESTFRAMEWORK_COMMON
#define MS_CPP_UNITTESTFRAMEWORK_COMMON

#ifndef WIDEN2
#define WIDEN2(x) L ## x
#endif

#ifndef WIDEN
#define WIDEN(x) WIDEN2(x)
#endif

#ifndef CATNAME2
#define CATNAME2(x, y) x##y
#endif

#ifndef CATNAME
#define CATNAME(x, y) CATNAME2(x, y)
#endif

#ifndef __WFILE__
#define __WFILE__ WIDEN(__FILE__)
#endif

#ifndef __WFUNCTION__
#define __WFUNCTION__ WIDEN(__FUNCTION__)
#endif

#ifndef __WFUNCDNAME__
#define __WFUNCDNAME__ WIDEN(__FUNCDNAME__)
#endif

#define __DW__(x) ((uint32_t)(x))
#define __MAKEVERSION__(MAJOR, MINOR, BUILD, REVISION) __DW__((__DW__(MAJOR) << 24) | (__DW__(MINOR) << 16) | (__DW__(BUILD) << 8) | (__DW__(REVISION)))
#define __CPPUNITTEST_VERSION__ __MAKEVERSION__(11, 0, 0, 0)

#define CALLING_CONVENTION __stdcall
#define EXPORT_METHOD __declspec(dllexport)

// Force a macro to be used only at namespace scope:
#define ONLY_USED_AT_NAMESPACE_SCOPE namespace  ___CUT___ {extern int YOU_CAN_ONLY_DEFINE_TEST_CLASS_AT_NAMESPACE_SCOPE;}
 
#define MS_CPP_UNITTESTFRAMEWORK_MAX_BUF_LENGTH 2048
#define MS_CPP_UNITTESTFRAMEWORK_NEW_LINE L"\r\n"


#include <sdkddkver.h>
#include <cstdlib>
#include <cstdint>
#include <crtdbg.h>

#define CPPUNIT_SET_STA_THREADING int __cli___threading_model = 0; \
extern "C" {\
int __refSTAThread = 0;\
int __refMTAThread = 0;\
}

#if ((defined _M_AMD64) || (defined _AMD64_))
#pragma comment(lib, "amd64\\Microsoft.VisualStudio.TestTools.CppUnitTestFramework.lib")
#elif ((defined _M_ARM) || (defined _ARM_))
#pragma comment(lib, "arm\\Microsoft.VisualStudio.TestTools.CppUnitTestFramework.lib")
#elif ((defined _M_IX86) || (defined _X86_))
#pragma comment(lib, "Microsoft.VisualStudio.TestTools.CppUnitTestFramework.lib")
#else
#error "Not supported architecture"
#endif

#endif /*MS_CPP_UNITTESTFRAMEWORK_COMMON*/
