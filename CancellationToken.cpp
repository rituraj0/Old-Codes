// ==++==
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// ==--==
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//
// CancellationToken.cpp
//
// Cancellation token implementation
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "concrtinternal.h"

namespace Concurrency
{
namespace details
{
    _CRTIMP _CancellationTokenState * _CancellationTokenState::_NewTokenState()
    {
        return new _CancellationTokenState();
    }

    _CRTIMP void _CancellationTokenState::_Destroy()
    {
        delete this;
    }

    _CRTIMP _CancellationTokenState::_CancellationTokenState() :
        _M_stateFlag(0)
    {
        static_assert(sizeof(SafeRWList<ListEntry>) <= sizeof(_M_registrations), "size of _M_registrations too small for list entry");
        new(_M_registrations) SafeRWList<ListEntry>();
    }

    _CRTIMP _CancellationTokenState::~_CancellationTokenState()
    {
        List<ListEntry> rundownList;

        SafeRWList<ListEntry> *pList = reinterpret_cast<SafeRWList<ListEntry> *>(_M_registrations);
        pList->Swap(&rundownList);

        ListEntry *pNext = NULL;
        for(ListEntry *pLE = rundownList.First(); pLE != NULL; pLE = pNext)
        {
            pNext = rundownList.Next(pLE);
            _CancellationTokenRegistration *pRegistration = CONTAINING_RECORD(pLE, _CancellationTokenRegistration, _M_listEntry);
            pRegistration->_M_state = ::_CancellationTokenRegistration::_STATE_SYNCHRONIZE;
            pRegistration->_Release();
        }
    }
    
    _CRTIMP void _CancellationTokenState::_Cancel()
    {
        if (InterlockedCompareExchange(&_M_stateFlag, 1, 0) == 0)
        {
            List<ListEntry> rundownList;
            SafeRWList<ListEntry> *pList = reinterpret_cast<SafeRWList<ListEntry> *>(_M_registrations);
            pList->Swap(&rundownList);

            ListEntry *pNext = NULL;
            for(ListEntry *pLE = rundownList.First(); pLE != NULL; pLE = pNext)
            {
                pNext = rundownList.Next(pLE);
                _CancellationTokenRegistration *pRegistration = CONTAINING_RECORD(pLE, _CancellationTokenRegistration, _M_listEntry);
                pRegistration->_Invoke();
            }

            _M_stateFlag = 2;
            _M_cancelComplete.set();
        }
    }

    _CRTIMP void _CancellationTokenState::_RegisterCallback(_CancellationTokenRegistration *_PRegistration)
    {
        _PRegistration->_M_state = _CancellationTokenRegistration::_STATE_CLEAR;
        _PRegistration->_Reference();
        _PRegistration->_M_pTokenState = this;

        bool invoke = true;

        if (!_IsCanceled())
        {
            SafeRWList<ListEntry> *pList = reinterpret_cast<SafeRWList<ListEntry> *>(_M_registrations);
            SafeRWList<ListEntry>::_Scoped_lock _lock(*pList);
            if (!_IsCanceled())
            {
                invoke = false;
                pList->UnlockedAddTail(reinterpret_cast<ListEntry *>(&_PRegistration->_M_listEntry));
            }
        }

        if (invoke)
        {
            _PRegistration->_Invoke();
        }
    }

    _CRTIMP _CancellationTokenRegistration * _CancellationTokenState::_RegisterCallback(TaskProc _Proc, void *_PData, int _InitialRefs)
    {
        _CancellationTokenRegistration *pRegistration = new CancellationTokenRegistration_TaskProc(_Proc, _PData, _InitialRefs);
        _RegisterCallback(pRegistration);
        return pRegistration;
    }

    _CRTIMP void _CancellationTokenState::_DeregisterCallback(_CancellationTokenRegistration *_PRegistration)
    {
        bool synchronize = false;

        {
            SafeRWList<ListEntry> *pList = reinterpret_cast<SafeRWList<ListEntry> *>(_M_registrations);
            SafeRWList<ListEntry>::_Scoped_lock _lock(*pList);

            //
            // If a cancellation has occurred, the registration list is guaranteed to be empty if we've observed it under the auspices of the
            // lock.  In this case, we must synchronize with the cancelling thread to guarantee that the cancellation is finished by the time
            // we return from this method.
            //
            if (!pList->Empty())
            {
                pList->UnlockedRemove(reinterpret_cast<ListEntry *>(&_PRegistration->_M_listEntry));
                _PRegistration->_M_state = ::_CancellationTokenRegistration::_STATE_SYNCHRONIZE;
                _PRegistration->_Release();
            }
            else
            {
                synchronize = true;
            }
        }

        // 
        // If the list is empty, we are in one of several situations:
        //
        // - The callback has already been made         --> do nothing
        // - The callback is about to be made           --> flag it so it doesn't happen and return
        // - The callback is in progress elsewhere      --> synchronize with it
        // - The callback is in progress on this thread --> do nothing
        //
        if (synchronize)
        {
            long result = InterlockedCompareExchange(
                &_PRegistration->_M_state, 
                _CancellationTokenRegistration::_STATE_DEFER_DELETE, 
                _CancellationTokenRegistration::_STATE_CLEAR
                );

            switch(result)
            {
                case _CancellationTokenRegistration::_STATE_CLEAR:
                case _CancellationTokenRegistration::_STATE_CALLED:
                    break;
                case _CancellationTokenRegistration::_STATE_DEFER_DELETE:
                case _CancellationTokenRegistration::_STATE_SYNCHRONIZE:
                    ASSERT(false);
                    break;
                default:
                {
                    DWORD tid = (long)result;
                    if (tid == GetCurrentThreadId())
                    {
                        //
                        // It is entirely legal for a caller to Deregister during a callback instead of having to provide their own synchronization
                        // mechanism between the two.  In this case, we do *NOT* need to explicitly synchronize with the callback as doing so would
                        // deadlock.  If the call happens during, skip any extra synchronization.
                        //
                        break;
                    }

                    event e;
                    _PRegistration->_M_pSyncBlock = &e;

                    long result = InterlockedExchange(&_PRegistration->_M_state, _CancellationTokenRegistration::_STATE_SYNCHRONIZE);
                    if (result != _CancellationTokenRegistration::_STATE_CALLED)
                    {
                        e.wait();
                    }

                    break;
                }
            }
        }

    }

    _CRTIMP void _CancellationTokenRegistration::_Invoke()
    {
        DWORD tid = GetCurrentThreadId();
        ASSERT(tid > 3); // If this ever fires, we need a different encoding for this.

        long result = InterlockedCompareExchange(&_M_state, (long)tid, _STATE_CLEAR);
        if (result == _STATE_CLEAR)
        {
            _Exec();

            result = InterlockedCompareExchange(&_M_state, _STATE_CALLED, (long)tid);
            if (result == _STATE_SYNCHRONIZE)
            {
                _M_pSyncBlock->set();
            }
        }
        _Release();
    }

} // namespace details
} // namespace Concurrency
