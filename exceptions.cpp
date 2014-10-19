//
// Copyright (C) Microsoft Corporation
// All rights reserved.
//

#include "pch.h"
#pragma hdrstop

#include <restrictederrorinfo.h>
#include <roerrorapi.h>

#pragma warning(disable:4483)

template <class _E> void *__GetExceptionInfo(_E); // This is a built-in c1xx template function to get the 
// ThrowInfo for a given struct (the structure passed by the compiler's 'throw' statement to the CRT.
// The ThrowInfo is statically compiled into the binary e.g. '__TI9P$AAVException@Platform@@' and
// GetException() returns the address of this structure.
// The CRT also uses this internally to transfer exceptions between threads.

namespace Platform
{
	typedef struct _WinRTExceptionInfo
	{		
		BSTR description;
		BSTR restrictedErrorString;
		BSTR restrictedErrorReference;
		BSTR capabilitySid;
		HRESULT hr;
		::Microsoft::WRL::ComPtr<IRestrictedErrorInfo> restrictedInfo;
		void* throwInfo;   // Do not need to free - this points to a static part of our binary.
		unsigned int size;
	} WinRTExceptionInfo;

	WinRTExceptionInfo* GetWinRTExceptionInfo(void* exceptionPtr)
	{
		ULONG_PTR *exceptionInfoPointer = reinterpret_cast<ULONG_PTR*>(exceptionPtr);
		exceptionInfoPointer--;
		return reinterpret_cast<WinRTExceptionInfo*>(*exceptionInfoPointer);
	}
	
	template <typename T>
	void UpdateThrowInfo(T ex)
	{
		auto exInfo = GetWinRTExceptionInfo(reinterpret_cast<void*>(const_cast< ::Platform::Object^>(ex)));
		_ASSERTE(exInfo != nullptr);
		exInfo->throwInfo = __GetExceptionInfo(ex);
	}

	void SetCppExceptionInformation(void* exceptionPtr, void* exInfoPtr, ::Platform::String^ message)
	{
		_ASSERTE(exceptionPtr != nullptr);
		_ASSERTE(exInfoPtr != nullptr);
		
		ULONG_PTR *exceptionInfoPointer = reinterpret_cast<ULONG_PTR*>(exceptionPtr);
		exceptionInfoPointer--;
		*exceptionInfoPointer = reinterpret_cast<ULONG_PTR>(exInfoPtr);

		::SetRestrictedErrorInfo(nullptr); //Clear IRestrictedErrorInfo

		if (!IsDebuggerPresent() || message == nullptr)
		{
			return; // Do nothing - no need to fill extra debugging information
		}

		BOOL hasEmbedNull;
		if (FAILED(::WindowsStringHasEmbeddedNull(reinterpret_cast<HSTRING>((message)), &hasEmbedNull)) || hasEmbedNull)
		{
			return; // Do nothing - cannot add message since it's incorrect
		}

		reinterpret_cast<WinRTExceptionInfo*>(exInfoPtr)->restrictedErrorString = ::SysAllocStringLen(message->Data(), message->Length());
	}

	namespace Details {

		VCCORLIB_API long __stdcall ReCreateFromException(::Platform::Exception^ ex)
		{
			auto exInfo = GetWinRTExceptionInfo(reinterpret_cast<void*>(const_cast< ::Platform::Object^>(ex)));
			_ASSERTE(exInfo != nullptr);

			if (exInfo->restrictedInfo != nullptr)
			{
				::SetRestrictedErrorInfo(exInfo->restrictedInfo.Get()); //Forward exception info if applies
			}
			else
			{
				const unsigned int length = (exInfo->restrictedErrorString == 0 ? 0 : ::SysStringLen(exInfo->restrictedErrorString));
				::Windows::Foundation::Diagnostics::OriginateError(exInfo->hr, length, exInfo->restrictedErrorString);
			}

			return ex->HResult;
		}

		void SetErrorInformation(void* exceptionPtr, IRestrictedErrorInfo* restrictedErrorInfo, int32 hresult)
		{
			_ASSERTE(restrictedErrorInfo != nullptr);

			auto exInfo = GetWinRTExceptionInfo(exceptionPtr);
			_ASSERTE(exInfo != nullptr);
			
			HRESULT hr = restrictedErrorInfo->GetErrorDetails(&exInfo->description, &exInfo->hr, &exInfo->restrictedErrorString, &exInfo->capabilitySid);
			if (SUCCEEDED(hr))
			{
				if (exInfo->restrictedErrorString == nullptr && 
					SUCCEEDED(restrictedErrorInfo->GetReference(&exInfo->restrictedErrorReference)))
				{
					exInfo->restrictedInfo = restrictedErrorInfo;
				}
			}

			if (exInfo->hr != hresult)
			{
				::Windows::Foundation::Diagnostics::TransformError(exInfo->hr, hresult, nullptr);
				exInfo->hr = hresult;
				::SetRestrictedErrorInfo(nullptr); // Clear error info created by transform
			}
		}

		template<typename T>
		class ReCreateHelper
		{
		public:
			static T^ ReCreateException()
			{
				::Microsoft::WRL::ComPtr<IRestrictedErrorInfo> restrictedErrorInfo;
				HRESULT hr = ::GetRestrictedErrorInfo(restrictedErrorInfo.GetAddressOf());				

				auto ex = ref new T;    
				if (hr == S_OK)
				{
					SetErrorInformation(reinterpret_cast<void*>(const_cast< ::Platform::Object^>(ex)), restrictedErrorInfo.Get(), ex->HResult);
				}
				return ex;
			}
		};

		template<>
		class ReCreateHelper< ::Platform::COMException>
		{
		public:
			static ::Platform::COMException^ ReCreateException(int32 hresult)
			{
				::Microsoft::WRL::ComPtr<IRestrictedErrorInfo> restrictedErrorInfo;
				HRESULT hr = ::GetRestrictedErrorInfo(restrictedErrorInfo.GetAddressOf());

				auto ex = ref new ::Platform::COMException(hresult);    
				if (hr == S_OK)
				{
					SetErrorInformation(reinterpret_cast<void*>(const_cast< ::Platform::Object^>(ex)), restrictedErrorInfo.Get(), hresult);
				}
				return ex;
			}
		};

		template<>
		class ReCreateHelper< ::Platform::Exception>
		{
		public:
			static ::Platform::Exception^ ReCreateException(int32 hresult)
			{
				::Microsoft::WRL::ComPtr<IRestrictedErrorInfo> restrictedErrorInfo;
				HRESULT hr = ::GetRestrictedErrorInfo(restrictedErrorInfo.GetAddressOf());

				auto ex = ::Platform::Exception::CreateException(hresult);    
				if (hr == S_OK)
				{
					SetErrorInformation(reinterpret_cast<void*>(const_cast< ::Platform::Object^>(ex)), restrictedErrorInfo.Get(), hresult);
				}
				return ex;
			}
		};
	}

	VCCORLIB_API Exception::Exception(int32 hresult)
	{
		__description = nullptr;
		__restrictedErrorString = nullptr;
		__restrictedErrorReference = nullptr;
		__capabilitySid = nullptr;
		__hresult = hresult;
		__restrictedInfo = nullptr;
		__throwInfo = nullptr;
		__size = sizeof(WinRTExceptionInfo);

		if (SUCCEEDED(hresult))
		{
			throw ref new ::Platform::InvalidArgumentException();
		}

		SetCppExceptionInformation(reinterpret_cast<void*>(this), &__description, nullptr);
		UpdateThrowInfo(this);
		// Context information where cleared by call to SetRestrictedErrorInfo in SetCppExceptionInformation
		::RoCaptureErrorContext(hresult);
	}

	VCCORLIB_API Exception::Exception(int32 hresult, ::Platform::String^ message)
	{
		__description = nullptr;
		__restrictedErrorString = nullptr;
		__restrictedErrorReference = nullptr;
		__capabilitySid = nullptr;
		__hresult = hresult;
		__restrictedInfo = nullptr;
		__throwInfo = nullptr;
		__size = sizeof(WinRTExceptionInfo);

		if (SUCCEEDED(hresult))
		{
			throw ref new ::Platform::InvalidArgumentException();
		}

		SetCppExceptionInformation(reinterpret_cast<void*>(this), &__description, message);
		UpdateThrowInfo(this);
		// Context information where cleared by call to SetRestrictedErrorInfo in SetCppExceptionInformation
		::RoCaptureErrorContext(hresult);
	}

	VCCORLIB_API void Exception::__identifier("<Dispose>")()
	{
		auto exInfo = GetWinRTExceptionInfo(reinterpret_cast<void*>(const_cast< ::Platform::Object^>(this)));

		if (exInfo != nullptr)
		{
			::SysFreeString(exInfo->description);
			::SysFreeString(exInfo->restrictedErrorString);
			::SysFreeString(exInfo->capabilitySid);
			::SysFreeString(exInfo->restrictedErrorReference);
			exInfo->restrictedInfo = nullptr;
		}
	}

	VCCORLIB_API Platform::String^ Exception::ToString()
	{
		return this->Message;
	}

	VCCORLIB_API bool Exception::Equals(Platform::Object^ other)
	{
		if (this == nullptr)
		{
			throw ref new ::Platform::NullReferenceException();
		}

		Exception ^ex = dynamic_cast<Exception^>(other);
		if (ex == nullptr)
		{
			return false;
		}

		return __hresult == ex->HResult;
	}

	VCCORLIB_API int32 Exception::GetHashCode()
	{
		return __hresult;
	}

	VCCORLIB_API Platform::String^ Exception::Message::get()
	{
		wchar_t buffer[4096];
		if (::FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM,
			nullptr, 
			__hresult,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
			buffer, 
			_countof(buffer), 
			nullptr))
		{
			return ref new Platform::String(buffer);
		}

		return nullptr;
	}

	VCCORLIB_API COMException::COMException(int32 hresult) : Exception(hresult)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API COMException::COMException(int32 hresult, ::Platform::String^ message) : Exception(hresult, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API OutOfMemoryException::OutOfMemoryException() : COMException(E_OUTOFMEMORY)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API OutOfMemoryException::OutOfMemoryException(::Platform::String^ message) : COMException(E_OUTOFMEMORY, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API InvalidArgumentException::InvalidArgumentException() : COMException(E_INVALIDARG)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API InvalidArgumentException::InvalidArgumentException(::Platform::String^ message) : COMException(E_INVALIDARG, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API InvalidCastException::InvalidCastException() : COMException(E_NOINTERFACE)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API InvalidCastException::InvalidCastException(::Platform::String^ message) : COMException(E_NOINTERFACE, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API NullReferenceException::NullReferenceException() : COMException(E_POINTER)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API NullReferenceException::NullReferenceException(::Platform::String^ message) : COMException(E_POINTER, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API NotImplementedException::NotImplementedException() : COMException(E_NOTIMPL)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API NotImplementedException::NotImplementedException(::Platform::String^ message) : COMException(E_NOTIMPL, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API AccessDeniedException::AccessDeniedException() : COMException(E_ACCESSDENIED)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API AccessDeniedException::AccessDeniedException(::Platform::String^ message) : COMException(E_ACCESSDENIED, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API FailureException::FailureException() : COMException(E_FAIL)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API FailureException::FailureException(::Platform::String^ message) : COMException(E_FAIL, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API OutOfBoundsException::OutOfBoundsException() : COMException(E_BOUNDS)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API OutOfBoundsException::OutOfBoundsException(::Platform::String^ message) : COMException(E_BOUNDS, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API ChangedStateException::ChangedStateException() : COMException(E_CHANGED_STATE)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API ChangedStateException::ChangedStateException(::Platform::String^ message) : COMException(E_CHANGED_STATE, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API OperationCanceledException::OperationCanceledException() : COMException(E_ABORT)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API OperationCanceledException::OperationCanceledException(::Platform::String^ message) : COMException(E_ABORT, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API ClassNotRegisteredException::ClassNotRegisteredException() : COMException(REGDB_E_CLASSNOTREG)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API ClassNotRegisteredException::ClassNotRegisteredException(::Platform::String^ message) : COMException(REGDB_E_CLASSNOTREG, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API DisconnectedException::DisconnectedException() : COMException(RPC_E_DISCONNECTED)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API DisconnectedException::DisconnectedException(::Platform::String^ message) : COMException(RPC_E_DISCONNECTED, message)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API WrongThreadException::WrongThreadException() : COMException(RPC_E_WRONG_THREAD)
	{
		UpdateThrowInfo(this);
	}

	VCCORLIB_API WrongThreadException::WrongThreadException(::Platform::String^ message) : COMException(RPC_E_WRONG_THREAD, message)
	{
		UpdateThrowInfo(this);
	}
	
	VCCORLIB_API ObjectDisposedException::ObjectDisposedException() : COMException(RO_E_CLOSED)
	{
		UpdateThrowInfo(this);
	}
	
	VCCORLIB_API ObjectDisposedException::ObjectDisposedException(::Platform::String^ message) : COMException(RO_E_CLOSED, message)
	{
		UpdateThrowInfo(this);
	}

} // namespace Platform

#pragma warning(push)
#pragma warning(disable: 4672 4673)
// The exceptions are split out explicitly in order to make them obvious from callstacks.
VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseNotImplementedException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::NotImplementedException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseInvalidCastException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::InvalidCastException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseNullReferenceException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::NullReferenceException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseOperationCanceledException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::OperationCanceledException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseFailureException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::FailureException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseAccessDeniedException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::AccessDeniedException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseOutOfMemoryException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::OutOfMemoryException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseInvalidArgumentException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::InvalidArgumentException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseOutOfBoundsException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::OutOfBoundsException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseChangedStateException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::ChangedStateException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseClassNotRegisteredException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::ClassNotRegisteredException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseWrongThreadException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::WrongThreadException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseDisconnectedException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::DisconnectedException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseObjectDisposedException()
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::ObjectDisposedException>::ReCreateException();
}

VCCORLIB_API __declspec(noreturn) inline void __stdcall __abi_WinRTraiseCOMException(long hr)
{
	throw ::Platform::Details::ReCreateHelper< ::Platform::COMException>::ReCreateException(hr);
}

#pragma warning(pop)

namespace Platform
{

	VCCORLIB_API Platform::Exception^ Exception::ReCreateException(int32 hresult)
	{
		return ::Platform::Details::ReCreateHelper< ::Platform::Exception>::ReCreateException(hresult);
	}

	VCCORLIB_API Platform::Exception^ Exception::CreateException(int32 hr)
	{
		Exception^ ex;

		switch (hr)
		{
		case E_NOTIMPL:
			ex = ref new NotImplementedException();
			break;
		case E_NOINTERFACE:
			ex = ref new InvalidCastException();
			break;
		case E_POINTER:
			ex = ref new NullReferenceException();
			break;
		case E_ABORT:
			ex = ref new OperationCanceledException();
			break;
		case E_FAIL:
			ex = ref new FailureException();
			break;
		case E_ACCESSDENIED:
			ex = ref new AccessDeniedException();
			break;
		case E_OUTOFMEMORY:
			ex = ref new OutOfMemoryException();
			break;
		case E_INVALIDARG:
			ex = ref new InvalidArgumentException();
			break;
		case E_BOUNDS:
			ex = ref new OutOfBoundsException();
			break;
		case E_CHANGED_STATE:
			ex = ref new ChangedStateException();
			break;
		case REGDB_E_CLASSNOTREG:
			ex = ref new ClassNotRegisteredException();
			break;
		case RPC_E_WRONG_THREAD:
			ex = ref new WrongThreadException();
			break;
		case RPC_E_DISCONNECTED:
			ex = ref new DisconnectedException();
			break;
		case RO_E_CLOSED:
			ex = ref new ObjectDisposedException();
			break;
		default:
			ex = ref new COMException(hr);
			break;
		}

		return ex;
	}

	VCCORLIB_API Platform::Exception^ Exception::CreateException(int32 hr, ::Platform::String^ message)
	{
		Exception^ ex;

		switch (hr)
		{
		case E_NOTIMPL:
			ex = ref new NotImplementedException(message);
			break;
		case E_NOINTERFACE:
			ex = ref new InvalidCastException(message);
			break;
		case E_POINTER:
			ex = ref new NullReferenceException(message);
			break;
		case E_ABORT:
			ex = ref new OperationCanceledException(message);
			break;
		case E_FAIL:
			ex = ref new FailureException(message);
			break;
		case E_ACCESSDENIED:
			ex = ref new AccessDeniedException(message);
			break;
		case E_OUTOFMEMORY:
			ex = ref new OutOfMemoryException(message);
			break;
		case E_INVALIDARG:
			ex = ref new InvalidArgumentException(message);
			break;
		case E_BOUNDS:
			ex = ref new OutOfBoundsException(message);
			break;
		case E_CHANGED_STATE:
			ex = ref new ChangedStateException(message);
			break;
		case REGDB_E_CLASSNOTREG:
			ex = ref new ClassNotRegisteredException(message);
			break;
		case RPC_E_WRONG_THREAD:
			ex = ref new WrongThreadException(message);
			break;
		case RPC_E_DISCONNECTED:
			ex = ref new DisconnectedException(message);
			break;
		case RO_E_CLOSED:
			ex = ref new ObjectDisposedException(message);
			break;
		default:
			ex = ref new COMException(hr, message);
			break;
		}

		return ex;
	}

} // namespace Platform
