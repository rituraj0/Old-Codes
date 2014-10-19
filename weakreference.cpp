//
// Copyright (C) Microsoft Corporation
// All rights reserved.
//

#include "pch.h"
#pragma hdrstop

namespace Platform { namespace Details {

#pragma warning(push)
#pragma warning(disable: 4400)
	VCCORLIB_API __abi_IUnknown* __stdcall GetWeakReference(const volatile Platform::Object^ const other)
#pragma warning(pop)
	{
		if (other == nullptr)
		{
			throw ref new ::Platform::InvalidArgumentException();
		}

		Microsoft::WRL::WeakRef ref;
		HRESULT hr = Microsoft::WRL::AsWeak(reinterpret_cast<IUnknown*>(const_cast<Platform::Object^>(other)), &ref);
		__abi_ThrowIfFailed(hr);

		return reinterpret_cast<__abi_IUnknown*>(ref.Detach());
	}

	VCCORLIB_API
		__declspec(no_refcount)
		::Platform::Object^ __stdcall ResolveWeakReference(const ::_GUID& guid, __abi_IUnknown** weakRef)
	{
		::Platform::Object ^strongRef = nullptr;

		if (*weakRef != nullptr)
		{        
			Microsoft::WRL::WeakRef *ref = reinterpret_cast<Microsoft::WRL::WeakRef*>(weakRef);
			HRESULT hr = ref->CopyTo(guid, reinterpret_cast<IInspectable**>(&strongRef));
			__abi_ThrowIfFailed(hr);
		}

		return strongRef;
	}

} } // namesapce Platform::Details
