//
// Copyright (C) Microsoft Corporation
// All rights reserved.
//

#include "pch.h"

#include <wrl/wrappers/corewrappers.h>

#pragma warning(disable: 4672 4673)

namespace Platform {
	namespace Details {

		class OutOfProcModule :
			public Microsoft::WRL::RuntimeClass< 
				Microsoft::WRL::RuntimeClassFlags< ::Microsoft::WRL::WinRt | ::Microsoft::WRL::InhibitWeakReference>, 
				IInspectable>,
			public Microsoft::WRL::Module<Microsoft::WRL::OutOfProcDisableCaching, OutOfProcModule>,
			public __abi_Module
		{
			InspectableClass(nullptr, BaseTrust)

			::Microsoft::WRL::Details::ModuleBase **__baseModulePtr;
			__abi_Module **__abiModulePtr;
			//Store old values of module pointers
			::Microsoft::WRL::Details::ModuleBase *__baseModule;			
			__abi_Module *__abiModule;
			
			__wchar_t* __serverName;
			void* __unregisterCallback;
			bool __isEventCallback;
		public:
			OutOfProcModule() :
				__baseModulePtr(nullptr),
				__abiModulePtr(nullptr),
				__baseModule(nullptr),
				__abiModule(nullptr),
				__serverName(nullptr),
				__unregisterCallback(nullptr)
			{			
			}
		
			virtual ~OutOfProcModule()
			{
				HRESULT hr = UnregisterObjects(__serverName);
				if (FAILED(hr))
				{
#ifdef _DEBUG
					OutputDebugStringW(L"WinRt object unregistration failed");
#endif
				}
				
				if (__serverName != nullptr)
				{
					::Platform::Details::Heap::Free(__serverName);
				}
				
				void* oldPtr = ::InterlockedCompareExchangePointer(reinterpret_cast<void* volatile*>(__baseModulePtr), __baseModule, static_cast<ModuleBase*>(this));
				if (oldPtr != static_cast<ModuleBase*>(this))
				{
					throw ref new ::Platform::FailureException();
				}

				oldPtr = ::InterlockedCompareExchangePointer(reinterpret_cast<void* volatile*>(__abiModulePtr), __abiModule, static_cast<__abi_Module*>(this));
				if (oldPtr != static_cast<__abi_Module*>(this))
				{
					throw ref new ::Platform::FailureException();
				}
			}
			
			void Callback()
			{
				if (__isEventCallback)
				{
					if(__unregisterCallback != nullptr)
					{
						if (!::SetEvent(reinterpret_cast<HANDLE>(__unregisterCallback)))
						{
							throw ::Platform::Exception::CreateException(HRESULT_FROM_WIN32(GetLastError()));
						}
					}
				}
				else {
					reinterpret_cast<::Platform::Module::UnregisterCallback>(__unregisterCallback)();
				}
			}

			HRESULT RuntimeClassInitialize(
				_In_ Microsoft::WRL::Details::ModuleBase** base, 
				__abi_Module** abi,
				_In_opt_ void* callback,
				_In_opt_z_ const ::default::char16* serverName,
				bool isEventCallback)
			{
				__unregisterCallback = callback;
				__isEventCallback = isEventCallback;
				__baseModulePtr = base;
				__abiModulePtr = abi;
				__baseModule = *base;
				__abiModule = *abi;
			
				void* oldPtr = ::InterlockedCompareExchangePointer(reinterpret_cast<void* volatile*>(__baseModulePtr), static_cast<ModuleBase*>(this), __baseModule);        
				if (oldPtr != __baseModule)
				{
					throw ref new ::Platform::FailureException();
				}

				oldPtr = ::InterlockedCompareExchangePointer(reinterpret_cast<void* volatile*>(__abiModulePtr), static_cast<__abi_Module*>(this), __abiModule);
				if (oldPtr != __abiModule)
				{
					throw ref new ::Platform::FailureException();
				}

				if (serverName != nullptr)
				{
					auto len = ::wcslen(serverName) + 1;					
					__serverName = reinterpret_cast<__wchar_t*>(::Platform::Details::Heap::Allocate(SafeMultiply(len, 2)));
				}
			
				HRESULT hr = Initialize(this, &OutOfProcModule::Callback);
				if (FAILED(hr))
				{
					return hr;
				}

				return RegisterObjects(__serverName);
			}			

			virtual unsigned long __stdcall __abi_IncrementObjectCount()
			{
				return Module::IncrementObjectCount();
			}

			virtual unsigned long __stdcall __abi_DecrementObjectCount()
			{
				return Module::DecrementObjectCount();
			}

			STDMETHOD_(const Microsoft::WRL::Details::CreatorMap**, GetFirstEntryPointer)() const
			{
				return __baseModule->GetFirstEntryPointer();
			}

			STDMETHOD_(const Microsoft::WRL::Details::CreatorMap**, GetMidEntryPointer)() const
			{
				return __baseModule->GetMidEntryPointer();
			}

			STDMETHOD_(const Microsoft::WRL::Details::CreatorMap**, GetLastEntryPointer)() const
			{
				return __baseModule->GetLastEntryPointer();
			}

			STDMETHOD_(SRWLOCK*, GetLock)() const
			{
				return __baseModule->GetLock();
			}
		};
		
		VCCORLIB_API __declspec(no_refcount) ::Platform::Object^ STDMETHODCALLTYPE RegisterFactories(
			_In_ Microsoft::WRL::Details::ModuleBase** module, 
			__abi_Module** abiModule,
			_In_opt_ ::Platform::Module::UnregisterCallback callback)
		{
			Microsoft::WRL::ComPtr<IInspectable> registar;
			HRESULT hr = Microsoft::WRL::MakeAndInitialize<OutOfProcModule>(
				registar.GetAddressOf(), 
				module,
				abiModule, 
				callback,
				nullptr,
				false);

			if (FAILED(hr))
			{
				throw ::Platform::Exception::CreateException(hr);
			}

			return reinterpret_cast< ::Platform::Object^>(registar.Detach());
		}
		
		VCCORLIB_API void STDMETHODCALLTYPE RunServer(
			_In_ Microsoft::WRL::Details::ModuleBase** module, 
			__abi_Module** abiModule, 
			_In_opt_z_ const ::default::char16* serverName)
		{
			::Microsoft::WRL::Wrappers::Event event(::CreateEventEx(nullptr, nullptr, 0, EVENT_ALL_ACCESS));
			if (!event.IsValid())
			{
				throw ::Platform::Exception::CreateException(HRESULT_FROM_WIN32(GetLastError()));
			}

			HANDLE eventHandle = event.Get();			
			::Microsoft::WRL::ComPtr<IInspectable> registar;
			HRESULT hr = Microsoft::WRL::MakeAndInitialize<OutOfProcModule>(
				registar.GetAddressOf(), 
				module, 
				abiModule, 
				eventHandle, 
				serverName, 
				true);

			if (FAILED(hr))
			{
				throw ::Platform::Exception::CreateException(hr);
			}
			
			auto status = ::WaitForMultipleObjectsEx(1, &eventHandle, true, INFINITE, true);
			if (status != WAIT_OBJECT_0)
			{
				throw ::Platform::Exception::CreateException(HRESULT_FROM_WIN32(GetLastError()));
			}		
		}

		VCCORLIB_API void STDMETHODCALLTYPE RunApplicationServer(_In_ Microsoft::WRL::Details::ModuleBase**, __abi_Module**, _In_opt_z_ const ::default::char16*)
		{
			throw ref new ::Platform::NotImplementedException();
		}

	} }  // namespace Platform::Details
