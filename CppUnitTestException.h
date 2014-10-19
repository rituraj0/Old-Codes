// This is a part of the VSCppUnit C++ Unit Testing Framework.
// Copyright (C) Microsoft Corporation
// All rights reserved.

#pragma once

namespace Microsoft{ namespace VisualStudio {namespace CppUnitTestFramework  
{

    class Exception
    {
    protected:
        virtual ~Exception() {}
    private:
        Exception& operator=(const Exception&);
    };
}}}
