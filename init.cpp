//
// Copyright (C) Microsoft Corporation
// All rights reserved.
//

#include "pch.h"
#pragma warning( disable: 4073 )  // initializers put in library initialization area
#pragma init_seg( lib )

extern int __abi___threading_model;
__abi_Module* __abi_module = nullptr;

namespace Platform {
	namespace Details {

		class InProcModule :
			public Microsoft::WRL::Module<Microsoft::WRL::InProcDisableCaching, InProcModule>,
			public __abi_Module
		{
		public:
			InProcModule()
			{
				__abi_module = this;
			}

			virtual ~InProcModule()
			{
				__abi_module = nullptr;
			}

			virtual unsigned long __stdcall __abi_IncrementObjectCount()
			{
				return Module::IncrementObjectCount();
			}

			virtual unsigned long __stdcall __abi_DecrementObjectCount()
			{
				return Module::DecrementObjectCount();
			}
		};

		auto &module_ = InProcModule::Create();


		// Forward declarations from vccorlib DLL
		HRESULT InitializeData(int __threading_model);
		void UninitializeData(int __threading_model);

		//Initializaton forwarders
		void __cdecl Cleanup();

		// Initialize MoCOM data and clean up handlers
		int __cdecl Initialize()
		{
			//Global initialization
			HRESULT hr = InitializeData(__abi___threading_model);
			if (FAILED(hr))
			{
				Cleanup();
				return hr;
			}

			// Register cleaning handler
			atexit(Cleanup);
			return 0;
		}

		// Global clean up
		void __cdecl Cleanup()
		{
			UninitializeData(__abi___threading_model);
		}

	} } // namespace Platform::Details

//Put initialization data into the section that we can return failure
#pragma section(".CRT$XIY",long,read)
extern "C" __declspec(allocate(".CRT$XIY")) void* __abi__initialize = Platform::Details::Initialize;

// All required libraries must be pulled in in init.cpp file because it always referenced
// The librairies should not be pulled in vccorlib.h unless it's vccorlib*.lib
#pragma comment(lib, "runtimeobject.lib")
#ifndef _CORESYS
#pragma comment(lib, "ole32.lib")
#endif
