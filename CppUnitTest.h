// This is a part of the VSCppUnit C++ Unit Testing Framework.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This file defines the macros that are used to create VSCppUnit test cases.

#pragma once

#ifndef MS_CPP_UNITTESTFRAMEWORK
#define MS_CPP_UNITTESTFRAMEWORK

#include "CppUnitTestCommon.h"
#include "CppUnitTestAssert.h"
#include "CppUnitTestLogger.h"

#ifdef WIN32_LEAN_AND_MEAN 
#include <stdlib.h>
#endif


////////////////////////////////////////////////////////////
/* USAGE EXAMPLE
// The following is an example of VSCppUnit usage.
// It includes examples of attribute metadata, fixtures,
// unit tests with assertions, and custom logging.


#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

BEGIN_TEST_MODULE_ATTRIBUTE()
	TEST_MODULE_ATTRIBUTE(L"Date", L"2010/6/12")
END_TEST_MODULE_ATTRIBUTE()


TEST_MODULE_INITIALIZE(ModuleInitialize)
{
	Logger::WriteMessage("In Module Initialize");
}

TEST_MODULE_CLEANUP(ModuleCleanup)
{
	Logger::WriteMessage("In Module Cleanup");
}



TEST_CLASS(Class1)
{
public:
	Class1()
	{
		Logger::WriteMessage("In Class1");
	}
	~Class1()
	{
		Logger::WriteMessage("In ~Class1");
	}

  

	TEST_CLASS_INITIALIZE(ClassInitialize)
	{
		Logger::WriteMessage("In Class Initialize");
	}
	TEST_CLASS_CLEANUP(ClassCleanup)
	{
		Logger::WriteMessage("In Class Cleanup");
	}

	
	BEGIN_TEST_METHOD_ATTRIBUTE(Method1)
        TEST_OWNER(L"OwnerName")
        TEST_PRIORITY(1)
	END_TEST_METHOD_ATTRIBUTE()

	TEST_METHOD(Method1)
	{   
		Logger::WriteMessage("In Method1");
		Assert::AreEqual(0, 0);
	}

	TEST_METHOD(Method2)
	{
		Assert::Fail(L"Fail");
	}
};
*/


///////////////////////////////////////////////////////////////////////////////////////////
//Macros for creating sections in the binary file.
#pragma section("testvers$", read, shared)
#pragma section("testdata$_A_class", read, shared)
#pragma section("testdata$_B_method", read, shared)
#pragma section("testdata$_C_attribute", read, shared)

#define ALLOCATE_TESTDATA_SECTION_VERSION __declspec(allocate("testvers$"))
#define ALLOCATE_TESTDATA_SECTION_CLASS __declspec(allocate("testdata$_A_class"))
#define ALLOCATE_TESTDATA_SECTION_METHOD __declspec(allocate("testdata$_B_method"))
#define ALLOCATE_TESTDATA_SECTION_ATTRIBUTE __declspec(allocate("testdata$_C_attribute"))


///////////////////////////////////////////////////////////////////////////////////////////
// Macro to define your test class. 
// Note that you can only define your test class at namespace scope,
// otherwise the compiler will raise an error.
#define TEST_CLASS(className) \
ONLY_USED_AT_NAMESPACE_SCOPE class className : public ::Microsoft::VisualStudio::CppUnitTestFramework::TestClass<className>

///////////////////////////////////////////////////////////////////////////////////////////
//Macro for creating test methods.
#define TEST_METHOD(methodName)\
	static const EXPORT_METHOD ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo* CALLING_CONVENTION CATNAME(__GetTestMethodInfo_, methodName)()\
	{\
		__GetTestClassInfo();\
		__GetTestVersion();\
		ALLOCATE_TESTDATA_SECTION_METHOD\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodMetadata s_Metadata = {L"TestMethodInfo", L#methodName, reinterpret_cast<unsigned char*>(__FUNCTION__), reinterpret_cast<unsigned char*>(__FUNCDNAME__), __WFILE__, __LINE__};\
\
		static ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo s_Info = {::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo::TestMethod, NULL, &s_Metadata};\
		s_Info.method.pVoidMethod = static_cast<::Microsoft::VisualStudio::CppUnitTestFramework::TestClassImpl::__voidFunc>(&methodName);\
		return &s_Info;\
	}\
	void methodName() 

///////////////////////////////////////////////////////////////////////////////////////////
// Macros for creating the initialization/cleanup fixture methods for a test module.
#define TEST_MODULE_INITIALIZE(methodName)\
	void CALLING_CONVENTION methodName();\
	const EXPORT_METHOD ::Microsoft::VisualStudio::CppUnitTestFramework::GlobalMethodInfo* CALLING_CONVENTION YOU_CAN_ONLY_DESIGNATE_ONE_FUNCTION_TO_BE_A_MODULE_INITIALIZE_FUNCTION()\
	{\
		ALLOCATE_TESTDATA_SECTION_METHOD\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodMetadata s_Metadata = {L"TestModuleInitializeInfo", L#methodName, reinterpret_cast<unsigned char*>(__FUNCTION__), reinterpret_cast<unsigned char*>(__FUNCDNAME__)};\
\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::GlobalMethodInfo s_Info = {&methodName, &s_Metadata};\
		return &s_Info;\
	}\
	void CALLING_CONVENTION methodName()

#define TEST_MODULE_CLEANUP(methodName)\
	void CALLING_CONVENTION methodName();\
	const EXPORT_METHOD ::Microsoft::VisualStudio::CppUnitTestFramework::GlobalMethodInfo* CALLING_CONVENTION YOU_CAN_ONLY_DESIGNATE_ONE_FUNCTION_TO_BE_A_MODULE_CLEANUP_FUNCTION()\
	{\
		ALLOCATE_TESTDATA_SECTION_METHOD\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodMetadata s_Metadata = {L"TestModuleCleanupInfo", L#methodName, reinterpret_cast<unsigned char*>(__FUNCTION__), reinterpret_cast<unsigned char*>(__FUNCDNAME__)};\
\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::GlobalMethodInfo s_Info = {&methodName, &s_Metadata};\
		return &s_Info;\
	}\
	void CALLING_CONVENTION methodName()

///////////////////////////////////////////////////////////////////////////////////////////
// Macros for creating the initialization/cleanup fixture methods for a test class.
#define TEST_CLASS_INITIALIZE(methodName)\
	public: static const EXPORT_METHOD ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo* CALLING_CONVENTION YOU_CAN_ONLY_DESIGNATE_ONE_CLASS_METHOD_TO_BE_A_TEST_CLASS_INITIALIZE_METHOD()\
	{\
		ALLOCATE_TESTDATA_SECTION_METHOD\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodMetadata s_Metadata = {L"TestClassInitializeInfo", L#methodName, reinterpret_cast<unsigned char*>(__FUNCTION__), reinterpret_cast<unsigned char*>(__FUNCDNAME__)};\
\
		static ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo s_Info = {::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo::TestClassSetup, NULL, &s_Metadata};\
		s_Info.method.pVoidStaticMethod = static_cast<::Microsoft::VisualStudio::CppUnitTestFramework::GlobalMethodInfo::voidFunc>(&methodName);\
		return &s_Info;\
	}\
	static void CALLING_CONVENTION methodName()

#define TEST_CLASS_CLEANUP(methodName)\
	public: static const EXPORT_METHOD ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo* CALLING_CONVENTION YOU_CAN_ONLY_DESIGNATE_ONE_CLASS_METHOD_TO_BE_A_TEST_CLASS_CLEANUP_METHOD()\
	{\
		ALLOCATE_TESTDATA_SECTION_METHOD\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodMetadata s_Metadata = {L"TestClassCleanupInfo", L#methodName, reinterpret_cast<unsigned char*>(__FUNCTION__), reinterpret_cast<unsigned char*>(__FUNCDNAME__)};\
\
		static ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo s_Info = {::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo::TestClassCleanup, NULL, &s_Metadata};\
		s_Info.method.pVoidStaticMethod = static_cast<::Microsoft::VisualStudio::CppUnitTestFramework::GlobalMethodInfo::voidFunc>(&methodName);\
		return &s_Info;\
	}\
	static void CALLING_CONVENTION methodName()

///////////////////////////////////////////////////////////////////////////////////////////
// Macros for creating the initialization/cleanup fixture methods for a test method.
#define TEST_METHOD_INITIALIZE(methodName)\
	public: static const EXPORT_METHOD ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo* CALLING_CONVENTION YOU_CAN_ONLY_DESIGNATE_ONE_CLASS_METHOD_TO_BE_A_TEST_METHOD_INITIALIZE_METHOD()\
	{\
		ALLOCATE_TESTDATA_SECTION_METHOD\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodMetadata s_Metadata = {L"TestMethodInitializeInfo", L#methodName, reinterpret_cast<unsigned char*>(__FUNCTION__), reinterpret_cast<unsigned char*>(__FUNCDNAME__)};\
\
		static ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo s_Info = {::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo::TestMethodSetup, NULL, &s_Metadata};\
		s_Info.method.pVoidMethod = static_cast<::Microsoft::VisualStudio::CppUnitTestFramework::TestClassImpl::__voidFunc>(&methodName);\
		return &s_Info;\
	}\
	void methodName()

#define TEST_METHOD_CLEANUP(methodName)\
	public: static const EXPORT_METHOD ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo* CALLING_CONVENTION YOU_CAN_ONLY_DESIGNATE_ONE_CLASS_METHOD_TO_BE_A_TEST_METHOD_CLEANTUP_METHOD()\
	{\
		ALLOCATE_TESTDATA_SECTION_METHOD\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodMetadata s_Metadata = {L"TestMethodCleanupInfo", L#methodName, reinterpret_cast<unsigned char*>(__FUNCTION__), reinterpret_cast<unsigned char*>(__FUNCDNAME__)};\
\
		static ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo s_Info = {::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo::TestMethodCleanup, NULL, &s_Metadata};\
		s_Info.method.pVoidMethod = static_cast<::Microsoft::VisualStudio::CppUnitTestFramework::TestClassImpl::__voidFunc>(&methodName);\
		return &s_Info;\
	}\
	void methodName()

///////////////////////////////////////////////////////////////////////////////////////////
// Macros for creating the attributes for tests. 
#define BEGIN_TEST_CLASS_ATTRIBUTE()\
	public: static const EXPORT_METHOD ::Microsoft::VisualStudio::CppUnitTestFramework::ClassAttributeMetadata* CALLING_CONVENTION __GetClassMetadata()\
	{\
		ALLOCATE_TESTDATA_SECTION_ATTRIBUTE\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::ClassAttributeMetadata s_Metadata[] = {\
			{L"TestClassAttributeStart", L"Name", __FUNCTION__, ::Microsoft::VisualStudio::CppUnitTestFramework::ClassAttributeMetadata::CLASS_ATTRIBUTE}, 

#define TEST_CLASS_ATTRIBUTE(attributeName, attributeValue)\
			{L"TestClassAttribute", attributeName, attributeValue, ::Microsoft::VisualStudio::CppUnitTestFramework::ClassAttributeMetadata::CLASS_ATTRIBUTE},

#define END_TEST_CLASS_ATTRIBUTE()\
			{L"TestClassAttributeEnd", NULL, NULL, ::Microsoft::VisualStudio::CppUnitTestFramework::ClassAttributeMetadata::CLASS_ATTRIBUTE}\
		};\
		return s_Metadata;\
	}

#define BEGIN_TEST_METHOD_ATTRIBUTE(methodName)\
	public: static const EXPORT_METHOD ::Microsoft::VisualStudio::CppUnitTestFramework::MethodAttributeMetadata* CALLING_CONVENTION CATNAME(__GetMethodMetadata_, methodName)()\
	{\
		CATNAME(__GetTestMethodInfo_, methodName)();\
		ALLOCATE_TESTDATA_SECTION_ATTRIBUTE\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodAttributeMetadata s_Metadata[] = {\
			{L"TestMethodAttributeStart", L"Name", __FUNCTION__, ::Microsoft::VisualStudio::CppUnitTestFramework::MethodAttributeMetadata::METHOD_ATTRIBUTE},

#define TEST_METHOD_ATTRIBUTE(attributeName, attributeValue)\
			{L"TestMethodAttribute", attributeName, attributeValue, ::Microsoft::VisualStudio::CppUnitTestFramework::MethodAttributeMetadata::METHOD_ATTRIBUTE},

#define END_TEST_METHOD_ATTRIBUTE()\
			{L"TestMethodAttributeEnd", NULL, NULL, ::Microsoft::VisualStudio::CppUnitTestFramework::MethodAttributeMetadata::METHOD_ATTRIBUTE}\
		};\
		return s_Metadata;\
	}

#define BEGIN_TEST_MODULE_ATTRIBUTE()\
	const EXPORT_METHOD ::Microsoft::VisualStudio::CppUnitTestFramework::ModuleAttributeMetadata* CALLING_CONVENTION __GetModuleMetadata()\
	{\
		ALLOCATE_TESTDATA_SECTION_ATTRIBUTE\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::ModuleAttributeMetadata s_Metadata[] = {\
			{L"TestModuleAttributeStart", L"Name", L"__FILE__", ::Microsoft::VisualStudio::CppUnitTestFramework::ModuleAttributeMetadata::MODULE_ATTRIBUTE},

#define TEST_MODULE_ATTRIBUTE(attributeName, attributeValue) \
			{L"TestModuleAttribute", attributeName, attributeValue, ::Microsoft::VisualStudio::CppUnitTestFramework::ModuleAttributeMetadata::MODULE_ATTRIBUTE},

#define END_TEST_MODULE_ATTRIBUTE()\
			{L"TestModuleAttributeEnd", NULL, NULL, ::Microsoft::VisualStudio::CppUnitTestFramework::ModuleAttributeMetadata::MODULE_ATTRIBUTE}\
		};\
		return s_Metadata;\
	}


///////////////////////////////////////////////////////////////////////////////////////////
// Pre-defined test attributes
#define TEST_OWNER(ownerAlias) TEST_METHOD_ATTRIBUTE(L"Owner", ownerAlias)
#define TEST_DESCRIPTION(description) TEST_METHOD_ATTRIBUTE(L"Description", description)
#define TEST_PRIORITY(priority) TEST_METHOD_ATTRIBUTE(L"Priority", L#priority)
#define TEST_WORKITEM(workitem) TEST_METHOD_ATTRIBUTE(L"WorkItem", L#workitem)
#define TEST_IGNORE() TEST_METHOD_ATTRIBUTE(L"Ignore", L"true")



///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

namespace Microsoft{ namespace VisualStudio {namespace CppUnitTestFramework 
{

	struct ClassMetadata
	{
		const wchar_t *tag;
		const unsigned char *helpMethodName;
		const unsigned char *helpMethodDecoratedName;
	};

	struct MethodMetadata
	{
		const wchar_t *tag;
		const wchar_t *methodName;
		const unsigned char *helpMethodName;
		const unsigned char *helpMethodDecoratedName;
		const wchar_t *sourceFile;
		int lineNo;
	};

	struct ModuleAttributeMetadata
	{
		enum AttributeType { MODULE_ATTRIBUTE };
		const wchar_t *tag;
		const wchar_t *attributeName;
		const wchar_t *attributeValue;
		AttributeType type;
	};

	struct ClassAttributeMetadata
	{
		enum AttributeType { CLASS_ATTRIBUTE };
		const wchar_t *tag;
		const wchar_t *attributeName;
		const void *attributeValue;
		AttributeType type;
	};

	struct MethodAttributeMetadata
	{
		enum AttributeType { METHOD_ATTRIBUTE };
		const wchar_t *tag;
		const wchar_t *attributeName;
		const void *attributeValue;
		AttributeType type;
	};

	struct MemberMethodInfo;
	template <typename T> class TestClass;


    ///////////////////////////////////////////////////////////////////////////////////////////
    // Exception code for CRT (C Run-Time Library) invalid parameter
    #define ERROR_CRT_INVALID_PARAMETER 0xE3530002
	class TestClassImpl
	{
	public:
		TestClassImpl() {}
		virtual ~TestClassImpl() {}

		typedef TestClassImpl* (CALLING_CONVENTION *__newFunc)();
		typedef void (CALLING_CONVENTION *__deleteFunc)(TestClassImpl *);

		typedef void (TestClassImpl::*__voidFunc)();

		virtual void __Invoke(__voidFunc method) = 0;

    protected:
        struct CrtHandlersSetter
        {
			typedef void (__cdecl *INVALID_PARAMETER_HANDLER)(const wchar_t* pExpression, const wchar_t* pFunction, const wchar_t* pFile, 
				unsigned int line, uintptr_t pReserved);

            CrtHandlersSetter()
            {
                if(IsDebuggerAttached())
                {
                    debuggerAttached = true;
                    return;
                }
            
                debuggerAttached = false;
                // Suppress the assert failure dialog.
                oldReportMode = _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
                oldReportFile = _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
                // Set the handler
                oldInvalidParameterHandler = _set_invalid_parameter_handler(reinterpret_cast<INVALID_PARAMETER_HANDLER>(InvalidParameterHandler));
            }
        
            ~CrtHandlersSetter()
            {
                if(debuggerAttached)
                {
                    return;
                }
            
                _CrtSetReportMode(_CRT_ASSERT, oldReportMode);
                _CrtSetReportFile(_CRT_ASSERT, oldReportFile);
                _set_invalid_parameter_handler(oldInvalidParameterHandler);
            }

        private:
            // Check if a debugger is attached.
            __declspec(dllexport) static bool __stdcall IsDebuggerAttached();
		    // The handler for invalid parameters
		    __declspec(dllexport) static void __cdecl InvalidParameterHandler(const unsigned short* pExpression, const unsigned short* pFunction, const unsigned short* pFile, 
				unsigned int line, uintptr_t pReserved);
    
        private:
            _invalid_parameter_handler oldInvalidParameterHandler;
            int oldReportMode;
            _HFILE oldReportFile;
            bool debuggerAttached;
        };
	};


#pragma pack(push, 8)
	struct TestClassInfo
	{
		TestClassImpl::__newFunc pNewMethod;
		TestClassImpl::__deleteFunc pDeleteMethod;

		const ClassMetadata *metadata;
	};
#pragma pack(pop)

	struct GlobalMethodInfo
	{
		typedef void (CALLING_CONVENTION *voidFunc)();
		voidFunc pVoidFunc;

		const MethodMetadata *metadata;
	};

   
	struct MemberMethodInfo
	{
		enum MemberMethodTypes
		{
			TestMethod,
			TestMethodSetup,
			TestMethodCleanup,
			TestObjectSetup,
			TestObjectCleanup,
			TestClassSetup,
			TestClassCleanup,
		} methodType;
		union
		{
			TestClassImpl::__voidFunc pVoidMethod;
			GlobalMethodInfo::voidFunc pVoidStaticMethod;
		} method;

		const MethodMetadata *metadata;
	};

   
	struct TestDataVersion
	{
		uint32_t version;
	};
    
   
	template <typename T>
	class TestClass : public TestClassImpl
	{
		typedef T ThisClass;

	public:
		static TestClassImpl* CALLING_CONVENTION __New()
		{
            CrtHandlersSetter setter;
			return new T();
		}

		static void CALLING_CONVENTION __Delete(TestClassImpl *p)
		{
            CrtHandlersSetter setter;
			delete p;
		}

		virtual ~TestClass()
		{
		}

		// assume method matches this pointer
		virtual void __Invoke(__voidFunc method)
		{
			typedef void (ThisClass::*voidFunc2)();
			voidFunc2 method2 = static_cast<voidFunc2>(method);

            CrtHandlersSetter setter;
			(static_cast<ThisClass *>(this)->*method2)();
		}
	 
		static EXPORT_METHOD const ::Microsoft::VisualStudio::CppUnitTestFramework::TestClassInfo* CALLING_CONVENTION __GetTestClassInfo()
		{
			ALLOCATE_TESTDATA_SECTION_CLASS
			static const ::Microsoft::VisualStudio::CppUnitTestFramework::ClassMetadata s_Metadata = {L"TestClassInfo", reinterpret_cast<unsigned char*>(__FUNCTION__), reinterpret_cast<unsigned char*>(__FUNCDNAME__)};

			static const ::Microsoft::VisualStudio::CppUnitTestFramework::TestClassInfo s_Info = {&__New, &__Delete, &s_Metadata};
			return &s_Info;
		}

		static EXPORT_METHOD const ::Microsoft::VisualStudio::CppUnitTestFramework::TestDataVersion* CALLING_CONVENTION __GetTestVersion() 
		{
			ALLOCATE_TESTDATA_SECTION_VERSION
			static ::Microsoft::VisualStudio::CppUnitTestFramework::TestDataVersion s_version = { __CPPUNITTEST_VERSION__ };

			return &s_version;
		}
	};
}}}

#endif /* MS_CPP_UNITTESTFRAMEWORK */