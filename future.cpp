// future.cpp -- future static objects
#include <cstdlib>

 #if _HAS_CPP0X
 #include <future>
 #include <exception>
_STD_BEGIN

static const char *const _Future_messages[] =
	{	// messages for future errors
	"broken promise",
	"future already retrieved",
	"promise already satisfied",
	"no state"
	};

_CRTIMP2_PURE const char *__CLRCALL_PURE_OR_CDECL _Future_error_map(int _Errcode)
	{	// convert to name of future error
	if (0 <= _Errcode
		&& _Errcode < sizeof (_Future_messages)
			/ sizeof (_Future_messages[0]))
		return (_Future_messages[_Errcode]);
	else
		return (0);
	}

	 	// future_error::what()
_CRTIMP2_PURE const char *__CLRCALL_PURE_OR_CDECL _Get_future_error_what(int _Value) _THROW0()
	{	// return error message
	return (_Future_messages[_Value]);
	}

_CRTIMP2_PURE _NO_RETURN(__CLRCALL_PURE_OR_CDECL _Throw_future_error(const error_code& _Code))
	{	// throw an exception
	_THROW_NCEE(future_error, _Code);
	}

_CRTIMP2_PURE _NO_RETURN(__CLRCALL_PURE_OR_CDECL _Rethrow_future_exception(
	_XSTD exception_ptr _Ptr))
	{	// rethrow an exception
	_XSTD rethrow_exception(_Ptr);
	}

_STD_END
 #else /* _HAS_CPP0X */
 #endif /* _HAS_CPP0X */

/*
 * Copyright (c) 1992-2012 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.00:0009 */
