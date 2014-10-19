//
// Copyright (C) Microsoft Corporation
// All rights reserved.
//

#include "pch.h"
#pragma hdrstop

namespace Platform
{
	VCCORLIB_API Platform::String^ Delegate::ToString()
	{
		return ref new Platform::String(L"Platform.Delegate");
	}

	VCCORLIB_API Delegate::Delegate()
	{
	}

	VCCORLIB_API int32 Delegate::GetHashCode()
	{
		return reinterpret_cast<int32>(reinterpret_cast<void*>(this));
	}

	VCCORLIB_API bool Delegate::Equals(Platform::Object^ other)
	{
		return (void*)this == (void*)other;
	}
}
