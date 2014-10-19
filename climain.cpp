//
// Copyright (C) Microsoft Corporation
// All rights reserved.
//

#include "pch.h"

int __cdecl main(Platform::Array<Platform::String^>^ arg); //User defined main function

namespace Platform {
	namespace Details {

		wchar_t** GetCmdArguments(_Out_ int* argc);

	} }

int __cdecl _main()
{
	int argc = 0;
	wchar_t **argv = Platform::Details::GetCmdArguments(&argc);
	auto arg = ref new Platform::Array<Platform::String^>(argc);

	for(int i = 0; i < argc; i++)
	{
		arg->set(i, ref new Platform::String(argv[i]));
	}

	return main(arg);
}
