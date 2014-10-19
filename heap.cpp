//
// Copyright (C) Microsoft Corporation
// All rights reserved.
//

#include "pch.h"
#pragma hdrstop

#pragma warning(disable: 4672 4673)

namespace Platform { namespace Details {

	volatile HANDLE __abi_heap = nullptr;
	volatile long __abi_heap_objectcount = 0;
	volatile long __abi_heap_object_counter = 0;
	volatile LPCRITICAL_SECTION __abi_heap_critsec = nullptr;

	::Platform::Details::HeapAllocationTrackingLevel __abi_heap_trackingLevel = ::Platform::Details::HeapAllocationTrackingLevel::NoTracking;

	size_t __abi_heap_break_on_id_new = 0;
	size_t __abi_heap_break_on_id_delete = 0;

	struct __abi_Mem_block 
	{
		__abi_Mem_block     *previous;
		__abi_Mem_block     *next;
		size_t        num_bytes;
		size_t        alloc_id;
		bool          allocated;
		union 
		{
			double      to_force_align;
#pragma warning(push)
#pragma warning(disable: 4200)
			char        start_of_alloc[];
#pragma warning(pop)
		};
	};

	__abi_Mem_block* __abi_heap_chain = nullptr;

	LPCRITICAL_SECTION __abi_heap_getcritsec()
	{
		if (__abi_heap_critsec)
		{
			return __abi_heap_critsec;
		}

		LPCRITICAL_SECTION critsec = new CRITICAL_SECTION();
		if (!critsec)
		{
			throw ref new OutOfMemoryException();
		}

		InitializeCriticalSection(critsec);

		void* previous = InterlockedCompareExchangePointer((void* volatile *)&__abi_heap_critsec, critsec, nullptr);
		if (previous)
		{
			DeleteCriticalSection(critsec);
			delete critsec;
			return (LPCRITICAL_SECTION)previous;
		}

		return critsec;
	}

	static void* HeapAllocateHelper(SizeT size, SizeT alignment, SizeT offset)
	{
		switch (__abi_heap_trackingLevel)
		{
		case ::Platform::Details::HeapAllocationTrackingLevel::NoTracking:
			{
				LPVOID pMem = (alignment == 0)
					? HeapAlloc(__abi_heap, 0, size)
					: _aligned_offset_malloc(size, alignment, offset);
				if (pMem == nullptr)
				{
					throw ref new OutOfMemoryException();
				}

				memset(pMem, 0, size);
				return pMem;
			}
			break;

		case ::Platform::Details::HeapAllocationTrackingLevel::ObjectCount:
			{
				LPVOID pMem = (alignment == 0)
					? HeapAlloc(__abi_heap, 0, size)
					: _aligned_offset_malloc(size, alignment, offset);
				if (pMem == nullptr)
				{
					throw ref new OutOfMemoryException();
				}

				memset(pMem, 0, size);
				InterlockedIncrement(&__abi_heap_objectcount);
				return pMem;
			}
			break;

		case ::Platform::Details::HeapAllocationTrackingLevel::ObjectInstances:
		case ::Platform::Details::HeapAllocationTrackingLevel::BreakOnErrors:
			{
				size_t memBlockSize = offsetof(__abi_Mem_block, start_of_alloc);
				size += memBlockSize;
				LPVOID pMem = (alignment == 0)
					? HeapAlloc(__abi_heap, 0, size)
					: _aligned_offset_malloc(size, alignment, offset + memBlockSize);
				__abi_Mem_block* ptr = reinterpret_cast<__abi_Mem_block*>(pMem);
				if (ptr == nullptr)
				{
					throw ref new OutOfMemoryException();
				}

				memset(pMem, 0, size);
				InterlockedIncrement(&__abi_heap_objectcount);

				ptr->alloc_id = InterlockedIncrement(&__abi_heap_object_counter);
				if (ptr->alloc_id == __abi_heap_break_on_id_new) 
				{
					OutputDebugStringW(L"Broken in from __abi_heap_break_on_id_new\r\n");
					__debugbreak();
				}

				ptr->allocated = true;

				LPCRITICAL_SECTION cs = __abi_heap_getcritsec();
				EnterCriticalSection(cs);

				if (__abi_heap_chain)
				{
					__abi_heap_chain->previous = ptr;
				}

				ptr->previous = nullptr;
				ptr->next = __abi_heap_chain;

				__abi_heap_chain = ptr;

				LeaveCriticalSection(cs);

				return &ptr->start_of_alloc[0];
			}
		}

		// Should never happen:
		return nullptr;
	}

	static void HeapFreeHelper(void* p, bool isAligned)
	{
		switch (__abi_heap_trackingLevel)
		{
		case ::Platform::Details::HeapAllocationTrackingLevel::NoTracking:
			{
				isAligned ? _aligned_free(p) : HeapFree(__abi_heap, 0, p);
			}
			break;

		case ::Platform::Details::HeapAllocationTrackingLevel::ObjectCount:
			{
				isAligned ? _aligned_free(p) : HeapFree(__abi_heap, 0, p);
				InterlockedDecrement(&__abi_heap_objectcount);
			}
			break;

		case ::Platform::Details::HeapAllocationTrackingLevel::ObjectInstances:
			{
				__abi_Mem_block *pBlock = reinterpret_cast<__abi_Mem_block*>( (char*)p - offsetof(__abi_Mem_block, start_of_alloc) );

				LPCRITICAL_SECTION cs = __abi_heap_getcritsec();
				EnterCriticalSection(cs);

				if (pBlock->next)
				{
					pBlock->next->previous = pBlock->previous;
				}

				if (pBlock->previous)
				{
					pBlock->previous->next = pBlock->next;
				}

				LeaveCriticalSection(cs);

				if (pBlock->alloc_id == __abi_heap_break_on_id_delete) 
				{
					OutputDebugStringW(L"Broken in from __abi_heap_break_on_id_delete\r\n");
					__debugbreak();
				}

				isAligned ? _aligned_free(p) : HeapFree(__abi_heap, 0, p);
				InterlockedDecrement(&__abi_heap_objectcount);
			}
			break;

		case ::Platform::Details::HeapAllocationTrackingLevel::BreakOnErrors:
			{
				__abi_Mem_block *pBlock = reinterpret_cast<__abi_Mem_block*>( (char*)p - offsetof(__abi_Mem_block, start_of_alloc) );

				LPCRITICAL_SECTION cs = __abi_heap_getcritsec();
				EnterCriticalSection(cs);

				if (!pBlock->allocated)
				{
					OutputDebugStringW(L"Attempted double-free of pointer\r\n");
					__debugbreak();
				}

				pBlock->allocated = false;

				LeaveCriticalSection(cs);

				InterlockedDecrement(&__abi_heap_objectcount);

				if (pBlock->alloc_id == __abi_heap_break_on_id_delete) 
				{
					OutputDebugStringW(L"Broken in from __abi_heap_break_on_id_delete\r\n");
					__debugbreak();
				}
			}
		}
	}

	VCCORLIB_API void* Heap::Allocate(SizeT size)
	{
		if (!__abi_heap)
		{
			HANDLE heap = HeapCreate(0, 0, 0);
			if (!heap)
			{
				throw ref new OutOfMemoryException();
			}

			HANDLE previous = InterlockedCompareExchangePointer(&__abi_heap, heap, nullptr);
			if (previous)
			{
				HeapDestroy(heap);
			}
		}

		return HeapAllocateHelper(size, 0, 0);
	}

	VCCORLIB_API void Heap::Free(void* p)
	{
		HeapFreeHelper(p, false);
	}

	VCCORLIB_API void* Heap::AlignedAllocate(SizeT size, SizeT alignment)
	{
		// Alignment must be nonzero so helper knows to use _aligned_offset_malloc

		if (alignment == 0)
		{
			alignment = 1;
		}

		return HeapAllocateHelper(size, alignment, 0);
	}

	VCCORLIB_API void Heap::AlignedFree(void * p)
	{
		HeapFreeHelper(p, true);
	}

	VCCORLIB_API void* Heap::AllocateException(SizeT size)
	{
		// Allocate space for two pointers before the actual exception object.
		// The 2nd pointer (immediately before the object) will be used to point
		// to ExceptionInformation associated with the exception.  The space for
		// the first pointer is unused, and there just to keep the exception
		// object double-pointer aligned.

		size += 2 * sizeof(void *);

		void * pMem = Heap::Allocate(size);

		return reinterpret_cast<void **>(pMem) + 2;
	}

	VCCORLIB_API void Heap::FreeException(void* p)
	{
		p = reinterpret_cast<void **>(p) - 2;
		HeapFreeHelper(p, false);
	}

	VCCORLIB_API void* Heap::AlignedAllocateException(SizeT size, SizeT alignment)
	{
		// Allocate space for a single pointer before the actual exception object.
		// The pointer will be used to point to ExceptionInformation associated
		// with the exception.

		size += sizeof(void *);

		// Alignment must be nonzero so helper knows to use _aligned_offset_malloc

		if (alignment == 0)
		{
			alignment = 1;
		}

		void * pMem = HeapAllocateHelper(size, alignment, sizeof(void *));

		return reinterpret_cast<void **>(pMem) + 1;
	}

	VCCORLIB_API void Heap::AlignedFreeException(void * p)
	{
		p = reinterpret_cast<void **>(p) - 1;
		HeapFreeHelper(p, true);
	}

	VCCORLIB_API ::Platform::Details::HeapAllocationTrackingLevel Heap::TrackingLevel::get()
	{
		return __abi_heap_trackingLevel;
	}

	VCCORLIB_API void Heap::TrackingLevel::set(::Platform::Details::HeapAllocationTrackingLevel level)
	{
		if (__abi_heap)
		{
			// Too late, we can't change it now, the objects will blow on on de-allocate.
			if ( (level == ::Platform::Details::HeapAllocationTrackingLevel::ObjectInstances) ||
				(level == ::Platform::Details::HeapAllocationTrackingLevel::BreakOnErrors) )
			{
				throw ref new FailureException();
			}
		}

		__abi_heap_trackingLevel = level;
	}

	VCCORLIB_API int Heap::CurrentAllocationId::get()
	{
		return __abi_heap_object_counter;
	}


	VCCORLIB_API int Heap::BreakOnAllocationId::get()
	{
		return static_cast<int>(__abi_heap_break_on_id_new);
	}

	VCCORLIB_API void Heap::BreakOnAllocationId::set(int id)
	{
		__abi_heap_break_on_id_new = id;
	}


	VCCORLIB_API int Heap::BreakOnFreeId::get()
	{
		return static_cast<int>(__abi_heap_break_on_id_delete);
	}

	VCCORLIB_API void Heap::BreakOnFreeId::set(int id)
	{
		__abi_heap_break_on_id_delete = id;
	}

	VCCORLIB_API int32 Heap::ObjectCount::get()
	{
		return __abi_heap_objectcount;
	}

	VCCORLIB_API void Heap::EnumerateAllocatedObjects(Platform::Details::HeapEntryHandler^ handler)
	{
		LPCRITICAL_SECTION cs = __abi_heap_getcritsec();
		EnterCriticalSection(cs);

		__abi_Mem_block *p;
		for (p = __abi_heap_chain; p != nullptr; p = p->next) 
		{
			if (p->allocated)
			{
				void* pObjStart = &p->start_of_alloc[0];
				Object^* ppObj = reinterpret_cast<Object^*>(&pObjStart);
				handler(*ppObj, static_cast<int>(p->alloc_id));
			}
		}

		LeaveCriticalSection(cs);
	}
} } // Platform::Details


