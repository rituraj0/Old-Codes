//
// Copyright (C) Microsoft Corporation
// All rights reserved.
//

#include "pch.h"
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include "activation.h"
#pragma hdrstop
#include <Strsafe.h>

CPPCLI_FUNC HRESULT __stdcall __getActivationFactoryByHSTRING(HSTRING str, ::Platform::Guid& riid, PVOID * ppActivationFactory)
{
    HRESULT hr = S_OK;
    IActivationFactory* pActivationFactory;
    hr = Windows::Foundation::GetActivationFactory(str, &pActivationFactory);
    if (SUCCEEDED(hr))
    {
        hr = pActivationFactory->QueryInterface(reinterpret_cast<REFIID>(riid), ppActivationFactory);
        pActivationFactory->Release();
    }

    return hr;
}

using namespace Microsoft::WRL;
using namespace std;

class PerApartmentFactoryCache;
class FactoryCache;

class PerApartmentFactoryCache : public RuntimeClass<RuntimeClassFlags<ClassicCom>, IInitializeSpy>
{
    unordered_map<std::wstring, ComPtr<IUnknown>> _factoryCache;
    ULARGE_INTEGER _ulCoInitSpyCookie;
    ULONG_PTR _apartmentID;
    Wrappers::CriticalSection _criticalSection;
    bool _apartmentIsSTA;

public:
    HRESULT RuntimeClassInitialize(ULONG_PTR apartmentID)
    {
        _ulCoInitSpyCookie.QuadPart = 0;
        _apartmentID = apartmentID;
        APTTYPE AptType;
        APTTYPEQUALIFIER AptQualifier;
        HRESULT hr = CoGetApartmentType(&AptType, &AptQualifier);
        if (SUCCEEDED(hr) && (AptType == APTTYPE::APTTYPE_MTA || AptType == APTTYPE::APTTYPE_NA))
        {
            _apartmentIsSTA = false;
        }
        else
        {
            _apartmentIsSTA = true;
        }
        return S_OK;
    }

    HRESULT SetCookie(ULARGE_INTEGER cookie)
    {
        _ulCoInitSpyCookie = cookie;
        return S_OK;
    }
    
    HRESULT AddFactory(LPCWSTR acid, IUnknown *factory)
    {
        try
        {
            wstring activatableID(acid);

            auto lock  = _criticalSection.Lock();
            auto ret = _factoryCache.insert(pair<wstring, ComPtr<IUnknown>>(activatableID, factory));
            if (ret.second == false)
            {
                return S_FALSE;
            }
            return S_OK;
        }
        catch (bad_alloc e)
        {
            return E_OUTOFMEMORY;
        }
        catch (exception e)
        {
            return E_FAIL;
        }
    }
    
    HRESULT GetFactory(LPCWSTR acid, Platform::Guid& iid, void** pFactory)
    {
        *pFactory = nullptr;
        try
        {
            wstring activatableID(acid);
            decltype(_factoryCache.find(activatableID)) it;

            if (!_apartmentIsSTA)
            {
                auto lock  = _criticalSection.Lock();
                it = _factoryCache.find(activatableID);
                if (it == _factoryCache.end())
                {
                    return E_FAIL;
                }
            }
            else
            {
                it = _factoryCache.find(activatableID);
                if (it == _factoryCache.end())
                {
                    return E_FAIL;
                }
            }
            return it->second.CopyTo(iid, pFactory);
        }
        catch (bad_alloc e)
        {
            return E_OUTOFMEMORY;
        }
        catch (exception e)
        {
            return E_FAIL;
        }
    }

    IFACEMETHODIMP PreInitialize(DWORD /*dwCoInit*/, DWORD /*cCurThreadAptRefs*/) 
    {
        return S_OK; 
    }

    IFACEMETHODIMP PostInitialize(HRESULT hrCoInit, DWORD /*dwCoInit*/, DWORD /*cNewThreadAptRefs*/) 
    { 
        return hrCoInit; 
    }

    IFACEMETHODIMP PreUninitialize(DWORD cCurThreadAptRefs);
    IFACEMETHODIMP PostUninitialize(DWORD /*cNewThreadAptRefs*/) 
    { 
        return S_OK; 
    }    
};

class FactoryCache
{
    vector<pair<ULONG_PTR, pair<ULARGE_INTEGER, ComPtr<PerApartmentFactoryCache>>>> perApartmentCache;
    Wrappers::CriticalSection _criticalSection;
    static volatile long _cacheEnabled;
    static volatile long _cacheDestroyed;
public:
    static void Enable()
    {
        ::_InterlockedCompareExchange(&_cacheEnabled, 1, 0);
    }
    static void Disable()
    {
        ::_InterlockedCompareExchange(&_cacheEnabled, 0, 1);
    }
    static bool IsEnabled()
    {
        return (_cacheEnabled == 1);
    }
    static bool IsDestroyed()
    {
        return (_cacheDestroyed != 0);
    }

    ~FactoryCache()
    {
        Disable();
        ::_InterlockedIncrement(&_cacheDestroyed);
        Flush();
    }
    void Flush()
    {
        auto lock  = _criticalSection.Lock();
        for(auto it = perApartmentCache.begin(); it != perApartmentCache.end(); it++)
        {
            CoRevokeInitializeSpy(it->second.first);
        }
        perApartmentCache.clear();
    }
    HRESULT GetFactory(LPCWSTR acid, Platform::Guid& iid, void** pFactory)
    {
        ComPtr<PerApartmentFactoryCache> apartmentCache;
        ULONG_PTR apartmentID;
        HRESULT hr = CoGetContextToken(&apartmentID);            
        if (SUCCEEDED(hr) && IsEnabled())
        {
            auto lock  = _criticalSection.Lock();         
                
            for(auto it = perApartmentCache.begin(); it != perApartmentCache.end(); it++)
            {
                if (it->first == apartmentID)
                {
                    lock.Unlock();
                    hr = it->second.second->GetFactory(acid, iid, pFactory);
                    if (SUCCEEDED(hr))
                    {
                        return hr;
                    }
                    apartmentCache = it->second.second;
                    break;
                }
            }
            if (apartmentCache == nullptr)
            {
                hr = MakeAndInitialize<PerApartmentFactoryCache, PerApartmentFactoryCache>(&apartmentCache, apartmentID);
                if (SUCCEEDED(hr))
                {
                    ULARGE_INTEGER cookie;
                    hr = CoRegisterInitializeSpy(apartmentCache.Get(), &cookie);
                    if (SUCCEEDED(hr))
                    {
                        apartmentCache->SetCookie(cookie);
                        perApartmentCache.push_back(pair<ULONG_PTR, pair<ULARGE_INTEGER, ComPtr<PerApartmentFactoryCache>>>(apartmentID, pair<ULARGE_INTEGER, ComPtr<PerApartmentFactoryCache>>(cookie, apartmentCache.Get())));
                    }
                }
            }
        }

        // Create Factory
        HSTRING className;
        HSTRING_HEADER classNameHeader;
        hr = ::WindowsCreateStringReference(acid, static_cast<UINT32>(wcslen(acid)), &classNameHeader, &className); 
        if (FAILED(hr))
        {
            return hr;
        }

        ComPtr<IUnknown> factory;
        Platform::Guid riidUnknown(__uuidof(IUnknown));
        hr = __getActivationFactoryByHSTRING(className, riidUnknown, &factory);

        ::WindowsDeleteString(className);

        if (FAILED(hr))
        {
            return hr;
        }
            
        if (apartmentCache != nullptr)
        {
            apartmentCache->AddFactory(acid, factory.Get());
        }
    
        return factory.CopyTo(iid, pFactory);
    }
    
    HRESULT RemoveApartmentCache(ULARGE_INTEGER cookie)
    {
        CoRevokeInitializeSpy(cookie);

        auto lock  = _criticalSection.Lock();

        for(auto it = perApartmentCache.begin(); it != perApartmentCache.end(); it++)
        {
            if (it->second.first.QuadPart == cookie.QuadPart)
            {
                perApartmentCache.erase(it);
                return S_OK;
            }
        }
        return E_FAIL;
    }
};

volatile long FactoryCache::_cacheEnabled = 0;
volatile long FactoryCache::_cacheDestroyed = 0;
FactoryCache g_FactoryCache;

IFACEMETHODIMP PerApartmentFactoryCache::PreUninitialize(DWORD cCurThreadAptRefs)
{
    if (cCurThreadAptRefs == 1) // equals one since this is "Pre" Uninitialize 
    {
        g_FactoryCache.RemoveApartmentCache(_ulCoInitSpyCookie);
    }
    return S_OK;
}

CPPCLI_FUNC void EnableFactoryCache()
{
    FactoryCache::Enable();
}

void DisableFactoryCache()
{
    FactoryCache::Disable();
}

CPPCLI_FUNC void __stdcall FlushFactoryCache()
{
    if (!FactoryCache::IsDestroyed())
    {
        g_FactoryCache.Flush();
    }
}

CPPCLI_FUNC HRESULT __stdcall GetActivationFactoryByPCWSTR(void* str, ::Platform::Guid& riid, void** ppActivationFactory)
{
    wchar_t* acid =  static_cast<wchar_t*>(str);
    if (!FactoryCache::IsEnabled())
    {
        HSTRING className;
        HSTRING_HEADER classNameHeader;
        HRESULT hr = ::WindowsCreateStringReference(acid, static_cast<UINT32>(wcslen(acid)), &classNameHeader, &className); 
        if (SUCCEEDED(hr))
        {
            hr = __getActivationFactoryByHSTRING(className, riid, ppActivationFactory);
            ::WindowsDeleteString(className);
        }
        return hr;
    }
    return g_FactoryCache.GetFactory(acid, riid, ppActivationFactory);
}

CPPCLI_FUNC HRESULT __stdcall GetIidsFn(int nIids, unsigned long* iidCount, const __s_GUID* pIids, ::Platform::Guid** ppDuplicated)
{
    int nBytes = nIids * sizeof(::Platform::Guid);

    *ppDuplicated = (::Platform::Guid*)CoTaskMemAlloc(nBytes);
    if (*ppDuplicated)
    {
        memcpy(*ppDuplicated, pIids, nBytes);
        *iidCount = nIids;
        return S_OK;
    }

    *iidCount = 0;
    return E_OUTOFMEMORY;
}

#include "compiler.cpp"
#include "activation.cpp"
